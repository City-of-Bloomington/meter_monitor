<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Meter $this->meter
 */
use Blossom\Classes\Block;
use Blossom\Classes\View;
?>
<h2><?php echo View::escape($this->meter->getName()); ?></h2>
<table>
    <tr><th><?php echo $this->_('zone'); ?></th>
        <td><?php echo $this->meter->getZone(); ?></td>
    </tr>
</table>

<h3><?php echo $this->_(['issue', 'issues', 2]); ?></h3>
<?php
    $block = new Block('issues/list.inc', ['meter'=>$this->meter, 'issues'=>$this->meter->getIssues()]);
    echo $block->render('html', $this->template);
?>

<h3><?php echo $this->_(['workOrder', 'workOrders', 2]); ?></h3>
<?php
    $block = new Block('workOrders/list.inc', ['meter'=>$this->meter, 'workOrders'=>$this->meter->getWorkOrders()]);
    echo $block->render('html', $this->template);
?>
