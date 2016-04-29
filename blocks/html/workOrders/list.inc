<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->workOrders
 * @param Meter $this->meter (optional)
 */
use Application\Models\Person;
use Application\Models\WorkOrdersTable;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;

$userCanEdit = Person::isAllowed('workOrders', 'update') && empty($_GET['print']);
$buttonHelper = $this->template->getHelper('buttonLink');

if ($userCanEdit) { $return_url = Url::current_url(); }

if (count($this->workOrders)) {
?>
<section>
    <header>
    <?php
        $c = is_a($this->workOrders, 'Zend\Paginator\Paginator')
            ? $this->workOrders->getTotalItemCount()
            : count($this->workOrders);
        echo "<h2>$c {$this->_(['workOrder', 'workOrders', $c])}</h2>";

        $sort = !empty($_GET['sort']) ? $_GET['sort'] : WorkOrdersTable::DEFAULT_ORDER;
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
            <th><?php echo $this->_(['meter', 'meters', 1]); ?></th>
            <th class="column-status"><?php echo $this->_(['workOrder', 'workOrders', 1]); ?></th>
            <th><?php echo $sortHelper->sortableLabel('dateCompleted', $this->_('dateCompleted'), $sort); ?></th>
            <th><?php echo $this->_('completedByPerson'); ?></th>
            <th><?php echo $this->_('workOrder_workTypes'); ?></th>
            <?php if (isset($this->meter)) { echo "<th>{$this->_('comments')}</th>"; } ?>
        </tr>
    </thead>
    <tbody>
    <?php
        foreach ($this->workOrders as $work) {
            $meter = $work->getMeter();
            $meterName = View::escape($meter->getName());
            $completed = $work->getDateCompleted(DATE_FORMAT);
            $status = $meter->hasOpenIssue() ? 'status_problem' : 'status_okay';

            $completedByPerson = $work->getCompletedByPerson_id()
                ? View::escape($work->getCompletedByPerson()->getFullname())
                : '';

            $workType = [];
            foreach ($work->getWorkTypes() as $type) {
                $workType[] = View::escape($type);
            }
            $workType = implode(', ', $workType);

            $editButton   = '';
            if ($userCanEdit) {
                $editButton = $buttonHelper->buttonLink(
                    BASE_URI."/workOrders/update?workOrder_id={$work->getId()};return_url=$return_url",
                    $this->_('edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
                );
            }

            if (isset($this->meter)) {
                $comments = View::escape($work->getComments());
                $comments = "<td>$comments</td>";
            }
            else { $comments = ''; }

            $workOrderUri = BASE_URI.'/workOrders/view?workOrder_id='.$work->getId();

            echo "
            <tr><th>$editButton</th>
                <th class=\"$status\">
                    <a href=\"{$meter->getUri()}\">$meterName</a>
                </th>
                <td><a href=\"$workOrderUri\">{$work->getId()}</a></td>
                <td>$completed</td>
                <td>$completedByPerson</td>
                <td>$workType</td>
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
    echo '<section><header>';
    include APPLICATION_HOME.'/blocks/html/noResultsFound.inc';
    echo '</header></section>';
}
