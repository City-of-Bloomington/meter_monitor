<?php
/**
 * @copyright 2014-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Issue $this->issue
 * @param string $this->return_url
 */
use Application\Models\IssueType;
use Application\Models\Person;
use Application\Models\PeopleTable;

$meter    = self::escape($this->issue->getMeter());
$comments = self::escape($this->issue->getComments());

$title = $this->issue->getId() ? $this->_('issue_edit') : $this->_('issue_add');
$inputHelper = $this->template->getHelper('field');
?>
<h2><?= $title; ?></h2>
<form method="post" action="<?= BASE_URI; ?>/issues/update">
    <fieldset>
        <input name="issue_id"   type="hidden" value="<?= $this->issue->getId(); ?>" />
        <input name="return_url" type="hidden" value="<?= $this->return_url; ?>" />

        <?php
            echo $inputHelper->input([
                'name'=>'meter_id', 'id'=>'meter_id', 'label'=>$this->_('meter'), 'value'=>$meter, 'attr'=>['class'=>'meterAutoComplete']
            ]);
        ?>

        <dl class="input-field mod-text"><dt><label for="reportedDate"><?= $this->_('reportedDate'); ?></label></dt>
            <dd><?php
                    $picker = $this->template->getHelper('datePicker');
                    echo $picker->datePicker('reportedDate', $this->issue->getReportedDate('U'));
                ?>
            </dd>
        </dl>
        <dl class="input-field"><dt><label for="reportedByPerson_id"><?= $this->_('reportedByPerson'); ?></label></dt>
            <dd><select name="reportedByPerson_id" id="reportedByPerson_id"><option value=""></option>
                <?php
                    $table = new PeopleTable();
                    $list = $table->find();
                    foreach ($list as $p) {
                        $selected = $p->getId()==$this->issue->getReportedByPerson_id()
                            ? 'selected="selected"'
                            : '';
                        $name = self::escape($p->getFullname());
                        echo "<option value=\"{$p->getId()}\" $selected>$name</option>";
                    }
                ?>
                </select>
            </dd>
        </dl>
        <dl class="input-field"><dt><label for="issueType_id"><?= $this->_(['issueType', 'issueTypes', 1]); ?></label></dt>
            <dd><select name="issueType_id"><option value=""></option>
                <?php
                    $options = IssueType::selectOptions();
                    foreach ($options as $t) {
                        $selected = $this->issue->getIssueType_id() == $t['id']
                            ? 'selected="selected"'
                            : '';
                        $name  = self::escape($t['name' ]);
                        $group = self::escape($t['group']);
                        echo "<option value=\"$t[id]\" $selected>$group: $name</option>";
                    }
                ?>
                </select>
            </dd>
        </dl>
        <dl class="input-field mod-text">
            <dt><label for="comments"><?= $this->_('comments'); ?></label></dt>
            <dd><textarea name="comments" id="comments"><?= $comments; ?></textarea></dd>
        </dl>

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
