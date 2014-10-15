<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Blossom\Classes\View;

$name = !empty($_GET['name']) ? View::escape($_GET['name']) : '';
$zone = !empty($_GET['zone']) ? View::escape($_GET['zone']) : '';
?>
<form method="get" action="<?php echo BASE_URI; ?>/meters">
    <fieldset><legend><?php echo $this->_('search'); ?></legend>
        <table>
            <tr><td><label for="name"><?php echo $this->_('name'); ?></label></td>
                <td><input name="name" id="name" value="<?php echo $name; ?>" class="meterAutoComplete" /></td>
            </tr>
            <tr><td><label for="zone"><?php echo $this->_('zone'); ?></label></td>
                <td><?php
                        $z = $this->template->getHelper('zoneSelector');
                        echo $z->zoneSelector($zone, 'zone');
                    ?>
                </td>
            </tr>
        </table>

        <button type="submit"><i class="fa fa-search"></i> <?php echo $this->_('search'); ?></button>
        <a href="<?php echo BASE_URI; ?>/meters"><?php echo $this->_('clear'); ?></a>
    </fieldset>
</form>
<?php
    $this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
    $this->template->addToAsset('scripts', JQUERY_UI.'/jquery-ui.min.js');
    $this->template->addToAsset('scripts', BASE_URI.'/js/meterAutoComplete.js');
    $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
?>
