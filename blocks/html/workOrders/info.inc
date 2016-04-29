<?php
/**
 * @copyright 2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param WorkOrder $this->workOrder
 */
$meter     = $this->workOrder->getMeter();
$meterName = self::escape($meter->getName());
$completed = $this->workOrder->getDateCompleted(DATE_FORMAT);

$completedByPerson = $this->workOrder->getCompletedByPerson_id()
    ? self::escape($this->workOrder->getCompletedByPerson()->getFullname())
    : '';
?>
<section>
    <header>
        <h1><?= "{$this->_('workOrder')} #{$this->workOrder->getId()}"; ?></h1>
    </header>

    <table>
        <tr><th><?= $this->_('meter'); ?></th><td><?= $meterName; ?></td></tr>
        <tr><th><?= $this->_('workOrder'); ?></th><td><?= $this->workOrder->getId(); ?></td></tr>
        <tr><th><?= $this->_('dateCompleted'); ?></th><td><?= $completed; ?></td></tr>
        <tr><th><?= $this->_('completedByPerson'); ?></th><td><?= $completedByPerson; ?></td></tr>
    </table>
</section>