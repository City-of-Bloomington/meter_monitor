<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->issue
 * @param string $this->return_url
 */
use Application\Models\IssueTypesTable;
use Application\Models\Person;
use Blossom\Classes\View;

$meter    = View::escape($this->issue->getMeter());
$comments = View::escape($this->issue->getComments());

$title = $this->issue->getId() ? $this->_('issue_edit') : $this->_('issue_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/issues/update">
    <fieldset>
        <input name="issue_id" type="hidden" value="<?php echo $this->issue->getId(); ?>" />
        <input name="return_url" type="hidden" value="<?php echo $this->return_url; ?>" />

        <table>
            <tr><td><label for="meter_id" class="required"><?php echo $this->_('meter'); ?></label></td>
                <td><input name="meter_id" id="meter_id" value="<?php echo $meter; ?>" class="meterAutoComplete" /></td>
            </tr>
            <tr><td><label for="reportedDate"><?php echo $this->_('reportedDate'); ?></label></td>
                <td><?php
                        $picker = $this->template->getHelper('datePicker');
                        echo $picker->datePicker('reportedDate', $this->issue->getReportedDate('U'));
                    ?>
                </td>
            </tr>
            <tr><td><label for="issueType_id"><?php echo $this->_(['issueType', 'issueTypes', 1]); ?></label></td>
                <td><select name="issueType_id"><option value=""></option>
                    <?php
                        $table = new IssueTypesTable();
                        $list = $table->find();
                        foreach ($list as $type) {
                            $selected = $this->issue->getIssueType_id() == $type->getId()
                                ? 'selected="selected"'
                                : '';
                            $name = View::escape($type);
                            echo "<option value=\"{$type->getId()}\" $selected>$name</option>";
                        }
                    ?>
                    </select>
                </td>
            </tr>
        </table>
    </fieldset>

    <fieldset>
        <div>
            <div><label for="comments"><?php echo $this->_('comments'); ?></label></div>
            <textarea name="comments" id="comments"><?php echo $comments; ?></textarea>
        </div>

        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons($this->return_url);

            if ($this->issue->getId() && Person::isAllowed('issues', 'delete')) {
                $h = $this->template->getHelper('buttonLink');
                echo $h->buttonLink(
                    BASE_URI.'/issues/delete?issue_id='.$this->issue->getId(),
                    $this->_('issue_delete'),
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
