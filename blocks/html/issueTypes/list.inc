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

$userCanEdit = Person::isAllowed('issueTypes', 'update') && empty($_GET['print']);
$helper = $this->template->getHelper('buttonLink');
?>
<section id="issueTypes_list">
    <header>
        <h1><?php echo $this->_(['issueTypeGroup', 'issueTypeGroups', 2]); ?></h1>
        <div class="tools">
            <?php
                if ($userCanEdit) {
                    echo $helper->buttonLink(
                        BASE_URI.'/issueTypeGroups/update',
                        $this->_('issueTypeGroup_add'),
                        'add'
                    );
                }

                if (empty($_GET['print'])) {
                    $p = $this->template->getHelper('printButton');
                    echo $p->printButton();
                }
            ?>
        </div>
    </header>
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
            $total = ['total'=>0, 'open'=>0, 'closed'=>0];
            foreach ($data as $row) {
                $id     = (int)$row['id'];
                $name   = View::escape($row['name']);

                $count  = (int)$row['count'];
                $closed = (int)$row['closed'];
                $open   = $count - $closed;

                $total['total' ] += $count;
                $total['open'  ] += $open;
                $total['closed'] += $closed;

                $editButton = '';
                if ($userCanEdit) {
                    $editButton = $helper->buttonLink(
                        BASE_URI."/issueTypes/update?issueType_id=$id",
                        $this->_('edit'),
                        'edit',
                        ButtonLink::SIZE_ICON
                    );
                }
                $searchUrl = BASE_URI.'/issues?issueType_id='.$id;
                $table_rows.= "
                <tr><td>$editButton</td>
                    <td><a href=\"$searchUrl\">$name</a></td>
                    <td class=\"ext-number\">$count</td>
                    <td class=\"ext-number\">$open</td>
                    <td class=\"ext-number\">$closed</td>
                </tr>
                ";
            }

            echo "
            <section>
                <header>
                    <h2>$groupName <span class=\"count\">($total[total])</span></h2>
                    <div class=\"tools\">$editGroupButton $addTypeButton</div>
                </header>
                <table class=\"output-tabular\">
                    <thead>
                        <tr><th></th>
                            <th>{$this->_(['issueType', 'issueTypes', 1])}</th>
                            <th>{$this->_('total')}</th>
                            <th>{$this->_('open')}</th>
                            <th>{$this->_('closed')}</th>
                        </tr>
                    </thead>
                    <tbody>
                        $table_rows
                        <tr class=\"total\">
                            <td colspan=\"2\">{$this->_('total')}</td>
                            <td class=\"ext-number\">$total[total]</td>
                            <td class=\"ext-number\">$total[open]</td>
                            <td class=\"ext-number\">$total[closed]</td>
                        </tr>
                    </tbody>
                </table>
            </section>
            ";
        }
    ?>
</section>