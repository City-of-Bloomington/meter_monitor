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
            <th><?php echo $this->_(['issue', 'issues', 2]); ?></th>
        </tr>
    </thead>
    <tbody>
    <?php
        foreach ($this->meters as $m) {
            $name   = View::escape($m->getName());
            $issues = [];
            foreach ($m->getIssues() as $i) {
                $issues[] = View::escape($i->getIssueType());
            }
            $status = count($issues)
                ? 'status_problem'
                : 'status_okay';
            $issues = implode(', ', $issues);
            echo "
            <tr><th class=\"$status\">
                    <a href=\"".BASE_URI."/meters/view?meter_id={$m->getId()}\">$name</a>
                </th>
                <td>{$m->getZone()}</td>
                <td>$issues</td>
            </tr>
            ";
        }
    ?>
    </tbody>
</table>
