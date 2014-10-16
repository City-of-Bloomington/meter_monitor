<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issues
 * @param Meter $this->meter (optional)
 */
use Blossom\Classes\Block;

echo "<h2>{$this->_(['issue', 'issues', 2])}</h2>";
include __DIR__.'/searchForm.inc';
include __DIR__.'/list.inc';

if (is_a($this->issues, 'Zend\Paginator\Paginator')) {
        $block = new Block('pageNavigation.inc', ['paginator' => $this->issues]);
        echo $block->render('html', $this->template);
}
