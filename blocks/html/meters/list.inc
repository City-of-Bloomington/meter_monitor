<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->meters
 */
use Application\Models\Issue;
use Blossom\Classes\View;

$c = is_a($this->meters, 'Zend\Paginator\Paginator')
    ? $this->meters->getTotalItemCount()
    : count($c);
echo "<h2>$c {$this->_(['meter', 'meters', $c])}</h2>";
?>
<table class="output-tabular">
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
            $status = $m->hasOpenIssue() ? 'status_problem' : 'status_okay';

            $issues = [];
            foreach ($m->getIssues(['status'=>Issue::STATUS_OPEN]) as $i) {
                $issues[] = View::escape($i->getIssueType());
            }
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
