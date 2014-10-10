<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->meters
 */
use Blossom\Classes\View;
?>
<h2><?php
        echo $this->_(['meter', 'meters', 2]);
    ?>
</h2>
<table>
    <thead>
        <tr><th><?php echo $this->_(['meter', 'meters', 1]); ?></th>
            <th><?php echo $this->_('zone'); ?></th>
        </tr>
    </thead>
    <tbody>
    <?php
        foreach ($this->meters as $m) {
            $name = View::escape($m->getName());
            echo "
            <tr><td>$name</td>
                <td>{$m->getZone()}</td>
            </tr>
            ";
        }
    ?>
    </tbody>
</table>
