<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->activity
 */
use Application\Models\IssueTypesTable;
use Blossom\Classes\View;

$zone     = View::escape($this->activity->getZone());
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
            <tr><th><label for="meter" class="required"><?php echo $this->_('meter'); ?></label></th>
                <td><input name="meter" id="meter" value="<?php echo $meter; ?>" /></td>
            </tr>
            <tr><th><label for="zone"><?php echo $this->_('zone'); ?></label></th>
                <td><input name="zone" id="zone" value="<?php echo $zone; ?>" /></td>
            </tr>
            <tr><th><label for="reportedDate"><?php echo $this->_('reportedDate'); ?></label></th>
                <td><?php
                        $picker = $this->template->getHelper('dateTimePicker');
                        echo $picker->dateTimePicker('reportedDate', $this->activity->getReportedDate('U'));
                    ?>
                </td>
            </tr>
            <tr><th><label for="resolvedDate"><?php echo $this->_('resolvedDate'); ?></label></th>
                <td><?php
                        echo $picker->dateTimePicker('resolvedDate', $this->activity->getResolvedDate('U'));
                    ?>
                </td>
            </tr>
        </table>

        <div>
            <div><label for="comments"><?php echo $this->_('comments'); ?></label></div>
            <textarea name="comments" id="comments" rows="6" cols="60"><?php echo $comments; ?></textarea>
        </div>

        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons(BASE_URI.'/activity');
        ?>
    </fieldset>
</form>
