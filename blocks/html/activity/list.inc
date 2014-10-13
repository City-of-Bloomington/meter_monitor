<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->activity
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h2><?php
        echo $this->_('activity');

        if (Person::isAllowed('activity', 'edit')) {
            $helper = $this->template->getHelper('buttonLink');
            echo $helper->buttonLink(
                BASE_URI.'/activity/update',
                $this->_('activity_add'),
                'add'
            );
        }
    ?>
</h2>
<table>
    <thead>
        <tr><th></th>
            <th><?php echo $this->_('meter'); ?></th>
            <th><?php echo $this->_('zone'); ?></th>
            <th><?php echo $this->_('reportedDate'); ?></th>
            <th><?php echo $this->_(['issue', 'issues', 2]); ?></th>
            <th><?php echo $this->_('resolvedDate'); ?></th>
            <th></th>
    </thead>
    <tbody>
    <?php
        foreach ($this->activity as $a) {
            $zone     = View::escape($a->getZone());
            $meter    = View::escape($a->getMeter());
            $comments = View::escape($a->getComments());
            $issues   = View::escape(implode(', ', $a->getIssueTypes()));
            $reported = $a->getReportedDate(DATE_FORMAT);
            $resolved = $a->getResolvedDate(DATE_FORMAT);


            $editButton   = '';
            $deleteButton = '';
            if (Person::isAllowed('activity', 'edit')) {
                $editButton = $helper->buttonLink(
                    BASE_URI.'/activity/update?activity_id='.$a->getId(),
                    $this->_('edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
                );

                $deleteButton = $helper->buttonLink(
                    BASE_URI.'/activity/delete?activity_id='.$a->getId(),
                    $this->_('delete'),
                    'delete',
                    ButtonLink::SIZE_ICON
                );
            }
            echo "
            <tr><td>$editButton</td>
                <td>$meter</td>
                <td>$zone</td>
                <td>$reported</td>
                <td>$issues</td>
                <td>$resolved</td>
                <td>$deleteButton</td>
            </tr>
            ";
        }
    ?>
    </tbody>
</table>
