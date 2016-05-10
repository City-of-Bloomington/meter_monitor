<?php
/**
 * @copyright 2014-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
use Application\Models\IssueType;
use Application\Models\PeopleTable;

$meter = !empty($_GET['meter']) ? self::escape($_GET['meter']) : '';
$zone  = !empty($_GET['zone'])  ? self::escape($_GET['zone'])  : '';

$field = $this->template->getHelper('field');
echo $field->input([
    'name'=>'meter', 'id'=>'meter', 'label'=>$this->_('meter'), 'value'=>$meter, 'attr'=>['class'=>'meterAutoComplete']
]);
?>
<dl class="input-field mod-select">
    <dt><label for="zone"><?= $this->_('zone'); ?></label></dt>
    <dd><?php
            $z = $this->template->getHelper('zoneSelector');
            echo $z->zoneSelector($zone, 'zone');
        ?>
    </dd>
</dl>
<dl class="input-field mod-select">
    <dt><label   for="reportedByPerson_id"><?= $this->_('reportedByPerson'); ?></label></dd>
    <dd><select name="reportedByPerson_id" id="reportedByPerson_id"><option value=""></option>
        <?php
            $table = new PeopleTable();
            $list = $table->find();
            foreach ($list as $p) {
                $selected = (!empty($_GET['reportedByPerson_id']) && $p->getId()==$_GET['reportedByPerson_id'])
                    ? 'selected="selected"'
                    : '';
                $name = self::escape($p->getFullname());
                echo "<option value=\"{$p->getId()}\" $selected>$name</option>";
            }
        ?>
        </select>
    </dd>
</dl>
<dl class="input-field mod-select">
    <dt><label   for="issueType_id"><?= $this->_('issueType'); ?></label></dt>
    <dd><select name="issueType_id"><option value=""></option>
        <?php
            $options = IssueType::selectOptions();
            foreach ($options as $t) {
                $group = self::escape($t['group']);
                $name  = self::escape($t['name' ]);
                $selected = (!empty($_GET['issueType_id']) && $t['id']==$_GET['issueType_id'])
                    ? 'selected="selected"'
                    : '';
                echo "<option value=\"$t[id]\" $selected>$group: $name</option>";
            }
        ?>
        </select>
    </dd>
</dl>
<?php
    $this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
    $this->template->addToAsset('scripts', JQUERY_UI.'/jquery-ui.min.js');
    $this->template->addToAsset('scripts', BASE_URI.'/js/meterAutoComplete.js');
    $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
?>
