<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Issue $this->issue
 */
use Application\Models\IssueTypesTable;
use Application\Models\Person;
use Blossom\Classes\View;

$meter    = View::escape($this->issue->getMeter());
$comments = View::escape($this->issue->getComments());
$reportedDate = $this->issue->getReportedDate(DATE_FORMAT);
$resolvedDate = $this->issue->getResolvedDate(DATE_FORMAT);

$title = $this->issue->getId() ? $this->_('issue_edit') : $this->_('issue_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/issues/update">
    <fieldset>
        <input name="issue_id" type="hidden" value="<?php echo $this->issue->getId(); ?>" />

        <table>
            <tr><th><label for="meter_id" class="required"><?php echo $this->_('meter'); ?></label></th>
                <td><input name="meter_id" id="meter_id" value="<?php echo $meter; ?>" /></td>
            </tr>
            <tr><th><label for="reportedDate"><?php echo $this->_('reportedDate'); ?></label></th>
                <td><?php
                        $picker = $this->template->getHelper('datePicker');
                        echo $picker->datePicker('reportedDate', $this->issue->getReportedDate('U'));
                    ?>
                </td>
            </tr>
            <tr><th><label for="resolvedDate"><?php echo $this->_('resolvedDate'); ?></label></th>
                <td><?php
                        echo $picker->datePicker('resolvedDate', $this->issue->getResolvedDate('U'));
                    ?>
                </td>
            </tr>
        </table>
    </fieldset>

    <fieldset id="issueType_picker">
        <legend><?php echo $this->_(['issue', 'issues', 2]); ?></legend>
        <ul><?php
                $table = new IssueTypesTable();
                $list = $table->find();
                foreach ($list as $type) {
                    $checked = $this->issue->hasIssueType($type)
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
            echo $h->saveAndCancelButtons(BASE_URI.'/issues');

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
