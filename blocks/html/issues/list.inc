<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issues
 * @param Meter $this->meter (optional)
 */
use Application\Models\Person;
use Application\Models\Issue;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<div>
<?php
    if (Person::isAllowed('issues', 'update')) {
        $helper = $this->template->getHelper('buttonLink');
        $return_url = Url::current_url();

        if (isset($this->meter)) {
            echo $helper->buttonLink(
                BASE_URI."/issues/update?meter_id={$this->meter->getId()};return_url=$return_url",
                $this->_('issue_add'),
                'add'
            );
        }
    }
?>
</div>
<?php if (count($this->issues)): ?>
<h2>
<?php
    $c = is_a($this->issues, 'Zend\Paginator\Paginator')
        ? $this->issues->getTotalItemCount()
        : count($this->issues);
    echo "$c {$this->_(['issue', 'issues', $c])}";
?>
</h2>
<table class="output-tabular">
    <thead>
        <tr><th></th>
            <th></th>
            <th><?php echo $this->_(['issue', 'issues', 1]); ?></th>
            <th><?php echo $this->_('reportedByPerson'); ?></th>
            <th><?php echo $this->_('reportedDate'); ?></th>
            <th><?php echo $this->_('dateCompleted'); ?></th>
            <?php if (isset($this->meter)) { echo "<th>{$this->_('comments')}</th>"; } ?>
        </tr>
    </thead>
    <tbody>
    <?php
        foreach ($this->issues as $issue) {
            $meter = $issue->getMeter();
            $meterName = View::escape($meter->getName());
            $comments  = View::escape($issue->getComments());
            $issueType = View::escape($issue->getIssueType());
            $reported  = $issue->getReportedDate(DATE_FORMAT);
            $completed = $issue->getDateCompleted(DATE_FORMAT);
            $status    = $meter->hasOpenIssue() ? 'status_problem' : 'status_okay';

            $reportedByPerson = $issue->getReportedByPerson_id()
                ? $issue->getReportedByPerson()->getFullname()
                : '';

            $editButton   = '';
            if (Person::isAllowed('issues', 'update')) {
                $editButton = $helper->buttonLink(
                    BASE_URI."/issues/update?issue_id={$issue->getId()};return_url=$return_url",
                    $this->_('edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
                );
            }
            if (isset($this->meter)) { $comments = "<td>$comments</td>"; }
            echo "
            <tr><th>$editButton</th>
                <th class=\"$status\">
                    <a href=\"{$meter->getUri()}\">$meterName</a>
                </th>
                <td>$issueType</td>
                <td>$reportedByPerson</td>
                <td>$reported</td>
                <td>$completed</td>
                $comments
            </tr>
            ";
        }
    ?>
    </tbody>
</table>
<?php endif ?>
