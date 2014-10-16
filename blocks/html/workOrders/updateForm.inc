<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->workOrder
 * @param string $this->return_url
 */
use Application\Models\WorkTypesTable;
use Application\Models\Person;
use Blossom\Classes\View;

$meter    = View::escape($this->workOrder->getMeter());
$comments = View::escape($this->workOrder->getComments());

$title = $this->workOrder->getId() ? $this->_('workOrder_edit') : $this->_('workOrder_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/workOrders/update">
    <fieldset>
        <input name="workOrder_id" type="hidden" value="<?php echo $this->workOrder->getId(); ?>" />
        <input name="meter_id"     type="hidden" value="<?php echo $this->workOrder->getMeter_id(); ?>" />
        <input name="return_url"   type="hidden" value="<?php echo $this->return_url; ?>" />

        <table>
            <tr><td><label for="dateCompleted"><?php echo $this->_('dateCompleted'); ?></label></td>
                <td><?php
                        $picker = $this->template->getHelper('datePicker');
                        echo $picker->datePicker('dateCompleted', $this->workOrder->getDateCompleted('U'));
                    ?>
                </td>
            </tr>
        </table>
    </fieldset>

    <fieldset><legend><?php echo $this->_('workOrder_workTypes'); ?></legend>
        <ul>
        <?php
            $table = new WorkTypesTable();
            $list = $table->find();
            foreach ($list as $type) {
                $checked = $this->workOrder->hasWorkType($type)
                    ? 'checked="checked"'
                    : '';
                $label = View::escape($type);
                echo "
                <label>
                    <input name=\"workTypes[]\" value=\"{$type->getId()}\" type=\"checkbox\" $checked />
                    $label
                </label>
                ";
            }
        ?>
        </ul>
    </fieldset>


    <fieldset>
        <div>
            <div><label for="comments"><?php echo $this->_('comments'); ?></label></div>
            <textarea name="comments" id="comments"><?php echo $comments; ?></textarea>
        </div>
    </fieldset>

    <?php
        $issues = $this->workOrder->getMeter()->getIssues();
        if (count($issues)) {
            echo "<fieldset><legend>{$this->_('workOrder_issues')}</legend><ul>";
                foreach ($issues as $issue) {
                    $checked = $this->workOrder->hasIssue($issue)
                        ? 'checked="checked"'
                        : '';
                    $label = View::escape($issue->getIssueType());
                    echo "
                    <label>
                        <input name=\"issues[]\" value=\"{$issue->getId()}\" type=\"checkbox\" $checked />
                        $label
                    </label>
                    ";
                }
            echo "</ul></fieldset>";
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
