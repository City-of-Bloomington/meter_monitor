<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Application\Models\IssueTypesTable;
use Blossom\Classes\View;

$meter = !empty($_GET['meter']) ? View::escape($_GET['meter']) : '';
$zone  = !empty($_GET['zone'])  ? View::escape($_GET['zone'])  : '';
?>
<table>
    <tr><td><label for="meter"><?php echo $this->_('meter'); ?></label></td>
        <td><input name="meter" id="meter" value="<?php echo $meter; ?>" class="meterAutoComplete" /></td>
    </tr>
    <tr><td><label for="zone"><?php echo $this->_('zone'); ?></label></td>
        <td><?php
                $z = $this->template->getHelper('zoneSelector');
                echo $z->zoneSelector($zone, 'zone');
            ?>
        </td>
    </tr>
    <tr><td><label for="issueType_id"><?php echo $this->_(['issueType', 'issueTypes', 1]); ?></label></td>
        <td><select name="issueType_id"><option value=""></option>
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
        </td>
    </tr>
</table>
<?php
    $this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
    $this->template->addToAsset('scripts', JQUERY_UI.'/jquery-ui.min.js');
    $this->template->addToAsset('scripts', BASE_URI.'/js/meterAutoComplete.js');
    $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
?>