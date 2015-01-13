<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
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
?>
<div>
<?php
    $buttonHelper = $this->template->getHelper('buttonLink');

    if (Person::isAllowed('workOrders', 'update')) {
        $return_url = Url::current_url();

        if (isset($this->meter)) {
            echo $buttonHelper->buttonLink(
                BASE_URI."/workOrders/update?meter_id={$this->meter->getId()};return_url=$return_url",
                $this->_('workOrder_add'),
                'add'
            );
        }
    }
?>
</div>
<?php if (count($this->workOrders)): ?>
<h2>
<?php
    $c = is_a($this->workOrders, 'Zend\Paginator\Paginator')
        ? $this->workOrders->getTotalItemCount()
        : count($this->workOrders);
    echo "$c {$this->_(['workOrder', 'workOrders', $c])}";

    $sort = !empty($_GET['sort']) ? $_GET['sort'] : WorkOrdersTable::DEFAULT_ORDER;
    $sortHelper = $this->template->getHelper('sortableLabel');

    $downloadUrl = new Url(Url::current_url());
    $downloadUrl->format = 'csv';
    echo $buttonHelper->buttonLink($downloadUrl, 'csv', 'download');
?>
</h2>
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
            if (Person::isAllowed('issues', 'update')) {
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

            echo "
            <tr><th>$editButton</th>
                <th class=\"$status\">
                    <a href=\"{$meter->getUri()}\">$meterName</a>
                </th>
                <td>{$work->getId()}</td>
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
<?php endif ?>
