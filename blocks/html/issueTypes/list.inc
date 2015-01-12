<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issueTypeGroups
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;

$userCanEdit = Person::isAllowed('issueTypes', 'update');
$helper = $this->template->getHelper('buttonLink');
?>
<h2><?php
        echo $this->_(['issueTypeGroup', 'issueTypeGroups', 2]);
        if ($userCanEdit) {
            echo $helper->buttonLink(
                BASE_URI.'/issueTypeGroups/update',
                $this->_('issueTypeGroup_add'),
                'add'
            );
        }
    ?>
</h2>
<?php
foreach ($this->issueTypeGroups as $group) {
    $editGroupButton = '';
    $addTypeButton   = '';
    if ($userCanEdit) {
        $editGroupButton = $helper->buttonLink(
            BASE_URI.'/issueTypeGroups/update?issueTypeGroup_id='.$group->getId(),
            $this->_('issueTypeGroup_edit'),
            'edit'
        );
        $addTypeButton   = $helper->buttonLink(
            BASE_URI.'/issueTypes/update?issueTypeGroup_id='.$group->getId(),
            $this->_('issueType_add'),
            'add'
        );
    }
    $groupName = View::escape($group->getName());
    $data      = $group->getIssueTypeStats();

    $table_rows = '';
    $total = 0;
    foreach ($data as $row) {
        $id    = (int)$row['id'];
        $name  = View::escape($row['name']);
        $count = (int)$row['count'];
        $total += $count;

        $editButton = '';
        if ($userCanEdit) {
            $editButton = $helper->buttonLink(
                BASE_URI."/issueTypes/update?issueType_id=$id",
                $this->_('edit'),
                'edit',
                ButtonLink::SIZE_ICON
            );
        }
        $table_rows.= "
        <tr><td>$editButton</td>
            <td>$name</td>
            <td>$count</td>
        </tr>
        ";
    }

    echo "
    <section>
        <h1>$groupName ($total) $editGroupButton $addTypeButton</h1>
        <table class=\"data\">
        $table_rows
        </table>
    </section>
    ";
}
