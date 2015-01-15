<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issues
 * @param Meter $this->meter (optional)
 */
use Application\Models\Person;
use Application\Models\Issue;
use Application\Models\IssuesTable;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;

$userCanEdit = Person::isAllowed('issues', 'update') && empty($_GET['print']);
$buttonHelper = $this->template->getHelper('buttonLink');

if ($userCanEdit) { $return_url = Url::current_url(); }

if (count($this->issues)) {
?>
<section>
    <header>
    <?php
        $c = is_a($this->issues, 'Zend\Paginator\Paginator')
            ? $this->issues->getTotalItemCount()
            : count($this->issues);
        echo "<h2>$c {$this->_(['issue', 'issues', $c])}</h2>";

        $sort = !empty($_GET['sort']) ? $_GET['sort'] : IssuesTable::DEFAULT_ORDER;
        $sortHelper = $this->template->getHelper('sortableLabel');

        if (empty($_GET['print'])) {
            echo '<div class="tools">';
            $downloadUrl = new Url(Url::current_url());
            $downloadUrl->format = 'csv';
            echo $buttonHelper->buttonLink($downloadUrl, 'csv', 'download');

            $p = $this->template->getHelper('printButton');
            echo $p->printButton();
            echo '</div>';
        }
    ?>
    </header>
    <table class="output-tabular">
        <thead>
            <tr><th></th>
                <th></th>
                <th><?php echo $this->_(['issue', 'issues', 1]); ?></th>
                <th><?php echo $this->_('reportedByPerson'); ?></th>
                <th><?php echo $sortHelper->sortableLabel('reportedDate', $this->_('reportedDate'), $sort); ?></th>
                <th><?php echo $this->_('dateCompleted'); ?></th>
                <?php if (isset($this->meter)) { echo "<th>{$this->_('comments')}</th>"; } ?>
            </tr>
        </thead>
        <tbody>
        <?php
            foreach ($this->issues as $issue) {
                $meter = $issue->getMeter();
                $meterName = View::escape($meter->getName());
                $issueType = View::escape($issue->getIssueType());
                $reported  = $issue->getReportedDate(DATE_FORMAT);
                $completed = $issue->getDateCompleted(DATE_FORMAT);
                $status    = $meter->hasOpenIssue() ? 'status_problem' : 'status_okay';

                $reportedByPerson = $issue->getReportedByPerson_id()
                    ? $issue->getReportedByPerson()->getFullname()
                    : '';

                $editButton   = '';
                if ($userCanEdit) {
                    $editButton = $buttonHelper->buttonLink(
                        BASE_URI."/issues/update?issue_id={$issue->getId()};return_url=$return_url",
                        $this->_('edit'),
                        'edit',
                        ButtonLink::SIZE_ICON
                    );
                }

                $comments = isset($this->meter)
                    ? '<td>'.View::escape($issue->getComments()).'</td>'
                    : '';
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
</section>
<?php
}
else {
    include APPLICATION_HOME.'/blocks/html/noResultsFound.inc';
}
?>
