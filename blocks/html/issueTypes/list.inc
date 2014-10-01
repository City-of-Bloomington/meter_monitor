<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issueTypes
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h2><?php
        echo $this->_(['issueType', 'issueTypes', 2]);

        if (Person::isAllowed('issueTypes', 'edit')) {
            $helper = $this->template->getHelper('buttonLink');
            echo $helper->buttonLink(
                BASE_URI.'/issueTypes/update',
                $this->_('add'),
                'add'
            );
        }
    ?>
</h2>
<table>
    <?php
        foreach ($this->issueTypes as $type) {
            $name = View::escape($type->getName());

            $editButton = '';
            if (Person::isAllowed('issueTypes', 'edit')) {
                $editButton = $helper->buttonLink(
                    BASE_URI.'/issueTypes/update?issueType_id='.$type->getId(),
                    $this->_('edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
                );
            }
            echo "
            <tr><td>$editButton</td>
                <td>$name</td>
            </tr>
            ";
        }
    ?>
</table>
