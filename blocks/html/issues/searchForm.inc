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
<form method="get" action="<?php echo BASE_URI; ?>/issues">
    <fieldset><legend><?php echo $this->_('search'); ?></legend>
        <table>
            <tr><td><label for="meter"><?php echo $this->_('meter'); ?></label></td>
                <td><input name="meter" id="meter" value="<?php echo $meter; ?>" /></td>
            </tr>
            <tr><td><label for="zone"><?php echo $this->_('zone'); ?></label></td>
                <td><input name="zone" id="zone" value="<?php echo $zone; ?>" /></td>
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

        <button type="submit"><i class="fa fa-search"></i> <?php echo $this->_('search'); ?></button>
        <a href="<?php echo BASE_URI; ?>/issues"><?php echo $this->_('clear'); ?></a>
    </fieldset>
</form>
