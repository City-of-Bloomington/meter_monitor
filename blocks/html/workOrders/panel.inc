<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->workOrders
 * @param Meter $this->meter (optional)
 */
use Blossom\Classes\Block;

echo "<h1>{$this->_(['workOrder', 'workOrders', 2])}</h1>";
include __DIR__.'/searchForm.inc';
include __DIR__.'/list.inc';

if (is_a($this->workOrders, 'Zend\Paginator\Paginator')) {
        $block = new Block('pageNavigation.inc', ['paginator' => $this->workOrders]);
        echo $block->render('html', $this->template);
}
