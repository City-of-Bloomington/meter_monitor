<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->meters
 */
use Blossom\Classes\Block;

echo "<h1>{$this->_(['meter', 'meters', 2])}</h1>";
include __DIR__.'/searchForm.inc';

if ($this->meters) {
    include __DIR__.'/list.inc';

    if (is_a($this->meters, 'Zend\Paginator\Paginator')) {
            $block = new Block('pageNavigation.inc', ['paginator' => $this->meters]);
            echo $block->render('html', $this->template);
    }
}
