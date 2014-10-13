<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->activity
 */
use Application\Models\IssueTypesTable;
use Blossom\Classes\View;

$meter    = View::escape($this->activity->getMeter());
$comments = View::escape($this->activity->getComments());
$reportedDate = $this->activity->getReportedDate(DATETIME_FORMAT);
$resolvedDate = $this->activity->getResolvedDate(DATETIME_FORMAT);

$title = $this->activity->getId() ? $this->_('activity_edit') : $this->_('activity_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/activity/update">
    <fieldset>
        <input name="activity_id" type="hidden" value="<?php echo $this->activity->getId(); ?>" />

        <table>
            <tr><th><label for="meter_id" class="required"><?php echo $this->_('meter'); ?></label></th>
                <td><input name="meter_id" id="meter_id" value="<?php echo $meter; ?>" /></td>
            </tr>
            <?php if ($this->activity->getId()): ?>
            <tr><th><label for="reportedDate"><?php echo $this->_('reportedDate'); ?></label></th>
                <td><?php
                        $picker = $this->template->getHelper('datePicker');
                        echo $picker->datePicker('reportedDate', $this->activity->getReportedDate('U'));
                    ?>
                </td>
            </tr>
            <tr><th><label for="resolvedDate"><?php echo $this->_('resolvedDate'); ?></label></th>
                <td><?php
                        echo $picker->datePicker('resolvedDate', $this->activity->getResolvedDate('U'));
                    ?>
                </td>
            </tr>
            <?php endif ?>
        </table>
    </fieldset>

    <fieldset id="issueType_picker">
        <legend><?php echo $this->_(['issue', 'issues', 2]); ?></legend>
        <ul><?php
                $table = new IssueTypesTable();
                $list = $table->find();
                foreach ($list as $type) {
                    $checked = $this->activity->hasIssueType($type)
                        ? 'checked="checked"'
                        : '';
                    $name = View::escape($type);
                    echo "
                    <li><label>
                            <input name=\"issueTypes[]\" value=\"{$type->getId()}\" type=\"checkbox\" $checked />
                            $type
                        </label>
                    </li>
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

        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons(BASE_URI.'/activity');
        ?>
    </fieldset>
</form>
<?php
    $this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
    $this->template->addToAsset('scripts', JQUERY_UI.'/jquery-ui.min.js');
    $this->template->addToAsset('scripts', BASE_URI.'/js/meterAutoComplete.js');
    $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
?>
