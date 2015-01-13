<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->workOrder
 * @param string $this->return_url
 */
use Application\Models\Issue;
use Application\Models\WorkTypesTable;
use Application\Models\Person;
use Application\Models\PeopleTable;
use Blossom\Classes\View;

$meter    = View::escape($this->workOrder->getMeter());
$comments = View::escape($this->workOrder->getComments());

$title = $this->workOrder->getId() ? $this->_('workOrder_edit') : $this->_('workOrder_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/workOrders/update">
    <fieldset>
        <legend>Basic Information</legend>
        <input name="workOrder_id" type="hidden" value="<?php echo $this->workOrder->getId(); ?>" />
        <input name="meter_id"     type="hidden" value="<?php echo $this->workOrder->getMeter_id(); ?>" />
        <input name="return_url"   type="hidden" value="<?php echo $this->return_url; ?>" />

        <dl class="input-field"><dt><label for="dateCompleted"><?php echo $this->_('dateCompleted'); ?></label></dt>
            <dd><?php
                    $picker = $this->template->getHelper('datePicker');
                    echo $picker->datePicker('dateCompleted', $this->workOrder->getDateCompleted('U'));
                ?>
            </dd>
        </dl>
        <dl class="input-field mod-select"><dt><label for="completedByPerson_id"><?php echo $this->_('completedByPerson'); ?></label></dt>
            <dd><select name="completedByPerson_id" id="completedByPerson_id"><option value=""></option>
                <?php
                    $t = new PeopleTable();
                    $l = $t->find();
                    foreach ($l as $p) {
                        $selected = $p->getId()==$this->workOrder->getCompletedByPerson_id()
                            ? 'selected="selected"'
                            : '';
                        $name = View::escape($p->getFullname());
                        echo "<option value=\"{$p->getId()}\" $selected>$name</option>";
                    }
                ?>
                </select>
            </dd>
        </dl>
        <dl class="input-field mod-checkbox">
            <dt><?php echo $this->_('workOrder_workTypes'); ?></dt>
        <?php
            $table = new WorkTypesTable();
            $list = $table->find();
            foreach ($list as $type) {
                $checked = $this->workOrder->hasWorkType($type)
                    ? 'checked="checked"'
                    : '';
                $label = View::escape($type);
                echo "
                <dd><label>
                    <input name=\"workTypes[]\" value=\"{$type->getId()}\" type=\"checkbox\" $checked />
                    <span>$label</span>
                </label></dd>
                ";
            }
        ?>
        </dl>
        <dl class="input-field mod-text">
            <dt><label for="comments"><?php echo $this->_('comments'); ?></label></dt>
            <dd><textarea name="comments" id="comments"><?php echo $comments; ?></textarea></dd>
        </dl>

    <?php
        $issues = $this->workOrder->getMeter()->getIssues(['status'=>Issue::STATUS_OPEN]);
        if (count($issues)) {
            echo "<dl class=\"input-field mod-checkbox\"><dt>{$this->_('workOrder_issues')}</dt>";
            foreach ($issues as $issue) {
                $checked = $this->workOrder->hasIssue($issue)
                    ? 'checked="checked"'
                    : '';
                $label = View::escape($issue->getIssueType());
                echo "
                <dd><label>
                    <input name=\"issues[]\" value=\"{$issue->getId()}\" type=\"checkbox\" $checked />
                    <span>$label</span>
                </label></dd>
                ";
            }
            echo "</dl>";
        }
    ?>

    <fieldset>
        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons($this->return_url);

            if ($this->workOrder->getId() && Person::isAllowed('workOrders', 'delete')) {
                $h = $this->template->getHelper('buttonLink');
                echo $h->buttonLink(
                    BASE_URI.'/workOrders/delete?workOrder_id='.$this->workOrder->getId(),
                    $this->_('workOrder_delete'),
                    'delete'
                );
            }
        ?>
    </fieldset>
</form>
<?php
    $this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
    $this->template->addToAsset('scripts', JQUERY_UI.'/jquery-ui.min.js');
    $this->template->addToAsset('scripts', BASE_URI.'/js/meterAutoComplete.js');
    $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
?>
