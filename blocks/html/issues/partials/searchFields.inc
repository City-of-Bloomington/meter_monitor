<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Application\Models\IssueTypesTable;
use Application\Models\PeopleTable;
use Blossom\Classes\View;

$meter = !empty($_GET['meter']) ? View::escape($_GET['meter']) : '';
$zone  = !empty($_GET['zone'])  ? View::escape($_GET['zone'])  : '';
$inputHelper = $this->template->getHelper('Input');
?>

<?php echo $inputHelper->text('meter', $this->_('meter'), $meter, 'meterAutoComplete') ?>
<dl class="input-field mod-select"><dt><label for="zone"><?php echo $this->_('zone'); ?></label></dt>
    <dd><?php
            $z = $this->template->getHelper('zoneSelector');
            echo $z->zoneSelector($zone, 'zone');
        ?>
    </dd>
</dl>
<dl class="input-field mod-select"><dt><label for="reportedByPerson_id"><?php echo $this->_('reportedByPerson'); ?></label></dd>
    <dd><select name="reportedByPerson_id" id="reportedByPerson_id"><option value=""></option>
        <?php
            $table = new PeopleTable();
            $list = $table->find();
            foreach ($list as $p) {
                $selected = (!empty($_GET['reportedByPerson_id']) && $p->getId()==$_GET['reportedByPerson_id'])
                    ? 'selected="selected"'
                    : '';
                $name = View::escape($p->getFullname());
                echo "<option value=\"{$p->getId()}\" $selected>$name</option>";
            }
        ?>
        </select>
    </dd>
</dl>
<dl class="input-field mod-select"><dt><label for="issueType_id"><?php echo $this->_(['issueType', 'issueTypes', 1]); ?></label></dt>
    <dd><select name="issueType_id"><option value=""></option>
        <?php
            $table = new IssueTypesTable();
            $list = $table->find();
            foreach ($list as $t) {
                $name = View::escape($t);
                $selected = (!empty($_GET['issueType_id']) && $t->getId()==$_GET['issueType_id'])
                    ? 'selected="selected"'
                    : '';
                echo "<option value=\"{$t->getId()}\" $selected>$name</option>";
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
