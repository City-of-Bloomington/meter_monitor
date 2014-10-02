<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->issue
 */
use Application\Models\IssueTypesTable;
use Blossom\Classes\View;

$zone     = View::escape($this->issue->getZone());
$meter    = View::escape($this->issue->getMeter());
$comments = View::escape($this->issue->getComments());
$reportedDate = $this->issue->getReportedDate(DATETIME_FORMAT);
$resolvedDate = $this->issue->getResolvedDate(DATETIME_FORMAT);

$title = $this->issue->getId() ? $this->_('issue_edit') : $this->_('issue_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/issues/update">
    <fieldset><legend><?php echo $this->_('issue_info'); ?></legend>
        <input name="issue_id" type="hidden" value="<?php echo $this->issue->getId(); ?>" />

        <table>
            <tr><th><label for="meter" class="required"><?php echo $this->_('meter'); ?></label></th>
                <td><input name="meter" id="meter" value="<?php echo $meter; ?>" /></td>
            </tr>
            <tr><th><label for="zone"><?php echo $this->_('zone'); ?></label></th>
                <td><input name="zone" id="zone" value="<?php echo $zone; ?>" /></td>
            </tr>
            <tr><th><label for="issueType_id"><?php echo $this->_(['issueType', 'issueTypes', 1]); ?></label></th>
                <td><select name="issueType_id"><option value=""></option>
                    <?php
                        $table = new IssueTypesTable();
                        $list = $table->find();
                        foreach ($list as $t) {
                            $name = View::escape($t);
                            $selected = $t->getId()==$this->issue->getIssueType_id()
                                ? 'selected="selected"'
                                : '';
                            echo "<option value=\"{$t->getId()}\" $selected>$name</option>";
                        }
                    ?>
                    </select>
                </td>
            </tr>
            <tr><th><label for="reportedDate"><?php echo $this->_('reportedDate'); ?></label></th>
                <td><?php
                        $picker = $this->template->getHelper('dateTimePicker');
                        echo $picker->dateTimePicker('reportedDate', $this->issue->getReportedDate('U'));
                    ?>
                </td>
            </tr>
            <tr><th><label for="resolvedDate"><?php echo $this->_('resolvedDate'); ?></label></th>
                <td><?php
                        echo $picker->dateTimePicker('resolvedDate', $this->issue->getResolvedDate('U'));
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
            echo $h->saveAndCancelButtons(BASE_URI.'/issues');
        ?>
    </fieldset>
</form>
