<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issues
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h2><?php
        echo $this->_(['issue', 'issues', 2]);

        if (Person::isAllowed('issues', 'update')) {
            $helper = $this->template->getHelper('buttonLink');
            echo $helper->buttonLink(
                BASE_URI.'/issues/update',
                $this->_('issue_add'),
                'add'
            );
        }
    ?>
</h2>
<table class="data">
    <thead>
        <tr><th></th>
            <th><?php echo $this->_('meter'); ?></th>
            <th><?php echo $this->_('zone'); ?></th>
            <th><?php echo $this->_('reportedDate'); ?></th>
            <th><?php echo $this->_(['issue', 'issues', 1]); ?></th>
    </thead>
    <tbody>
    <?php
        foreach ($this->issues as $issue) {
            $zone      = View::escape($issue->getZone());
            $meter     = View::escape($issue->getMeter());
            $comments  = View::escape($issue->getComments());
            $issueType = View::escape($issue->getIssueType());
            $reported  = $issue->getReportedDate(DATE_FORMAT);

            $editButton   = '';
            if (Person::isAllowed('issues', 'update')) {
                $editButton = $helper->buttonLink(
                    BASE_URI.'/issues/update?issue_id='.$issue->getId(),
                    $this->_('edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
                );
            }
            echo "
            <tr><td>$editButton</td>
                <td>$meter</td>
                <td>$zone</td>
                <td>$reported</td>
                <td>$issueType</td>
            </tr>
            ";
        }
    ?>
    </tbody>
</table>
