<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Blossom\Classes\View;

$meter = !empty($_GET['meter']) ? View::escape($_GET['meter']) : '';
$zone  = !empty($_GET['zone'])  ? View::escape($_GET['zone'])  : '';
?>
<form method="get" action="<?php echo BASE_URI; ?>/meters">
    <fieldset><legend><?php echo $this->_('search'); ?></legend>
        <table>
            <tr><td><label for="name"><?php echo $this->_('name'); ?></label></td>
                <td><input name="name" id="name" value="<?php echo $meter; ?>" /></td>
            </tr>
            <tr><td><label for="zone"><?php echo $this->_('zone'); ?></label></td>
                <td><input name="zone" id="zone" value="<?php echo $zone; ?>" /></td>
            </tr>
        </table>

        <button type="submit"><i class="fa fa-search"></i> <?php echo $this->_('search'); ?></button>
        <a href="<?php echo BASE_URI; ?>/meters"><?php echo $this->_('clear'); ?></a>
    </fieldset>
</form>
