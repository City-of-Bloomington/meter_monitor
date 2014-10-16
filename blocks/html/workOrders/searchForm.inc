<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<form method="get" action="<?php echo BASE_URI; ?>/workOrders">
    <fieldset><legend><?php echo $this->_('search'); ?></legend>

        <?php include APPLICATION_HOME.'/blocks/html/issues/partials/searchFields.inc'; ?>

        <button type="submit"><i class="fa fa-search"></i> <?php echo $this->_('search'); ?></button>
        <a href="<?php echo BASE_URI; ?>/workOrders"><?php echo $this->_('clear'); ?></a>
    </fieldset>
</form>
