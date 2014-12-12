<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->workOrders
 * @param Meter $this->meter (optional)
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<div>
<?php
    if (Person::isAllowed('workOrders', 'update')) {
        $helper = $this->template->getHelper('buttonLink');
        $return_url = Url::current_url();

        if (isset($this->meter)) {
            echo $helper->buttonLink(
                BASE_URI."/workOrders/update?meter_id={$this->meter->getId()};return_url=$return_url",
                $this->_('workOrder_add'),
                'add'
            );
        }
    }
?>
</div>
<?php if (count($this->workOrders)): ?>
<h3>
<?php
    $c = is_a($this->workOrders, 'Zend\Paginator\Paginator')
        ? $this->workOrders->getTotalItemCount()
        : count($this->workOrders);
    echo "$c {$this->_(['workOrder', 'workOrders', $c])}";
?>
</h3>
<table class="output-tabular">
    <thead>
        <tr><th></th>
            <th class="column-status"><?php echo $this->_(['meter', 'meters', 1]); ?></th>
            <th><?php echo $this->_(['workOrder', 'workOrders', 1]); ?></th>
            <th><?php echo $this->_('dateCompleted'); ?></th>
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
            $comments  = View::escape($work->getComments());
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
                $editButton = $helper->buttonLink(
                    BASE_URI."/workOrders/update?workOrder_id={$work->getId()};return_url=$return_url",
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
