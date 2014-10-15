<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Meter $this->meter
 */
use Blossom\Classes\View;
?>
<h2><?php echo View::escape($this->meter->getName()); ?></h2>
<table>
    <tr><th><?php echo $this->_('zone'); ?></th>
        <td><?php echo $this->meter->getZone(); ?></td>
    </tr>
</table>
