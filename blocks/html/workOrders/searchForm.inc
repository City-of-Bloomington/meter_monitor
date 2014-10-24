<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Application\Models\PeopleTable;
use Blossom\Classes\View;
?>
<form method="get" action="<?php echo BASE_URI; ?>/workOrders">
    <fieldset><legend><?php echo $this->_('search'); ?></legend>

        <table>
        <?php include APPLICATION_HOME.'/blocks/html/issues/partials/searchFields.inc'; ?>
            <tr><td><label for="completedByPerson_id"><?php echo $this->_('completedByPerson'); ?></label></td>
                <td><select name="completedByPerson_id" id="completedByPerson_id"><option value=""></option>
                    <?php
                        $t = new PeopleTable();
                        $l = $t->find();
                        foreach ($l as $p) {
                            $selected = (!empty($_GET['completedByPerson_id']) && $p->getId()==$_GET['completedByPerson_id'])
                                ? 'selected="selected"'
                                : '';
                            $name = View::escape($p->getFullname());
                            echo "<option value=\"{$p->getId()}\" $selected>$name</option>";
                        }
                    ?>
                    </select>
                </td>
            </tr>
        </table>

        <button type="submit"><i class="fa fa-search"></i> <?php echo $this->_('search'); ?></button>
        <a href="<?php echo BASE_URI; ?>/workOrders"><?php echo $this->_('clear'); ?></a>
    </fieldset>
</form>
