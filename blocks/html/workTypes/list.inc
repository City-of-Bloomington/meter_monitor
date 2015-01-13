<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->workTypes
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h1><?php
        echo $this->_(['workType', 'workTypes', 2]);

        if (Person::isAllowed('workTypes', 'edit')) {
            $helper = $this->template->getHelper('buttonLink');
            echo $helper->buttonLink(
                BASE_URI.'/workTypes/update',
                $this->_('add'),
                'add'
            );
        }
    ?>
</h1>
<table class="output-tabular">
    <?php
        foreach ($this->workTypes as $type) {
            $name        = View::escape($type->getName());
            $description = View::escape($type->getDescription());

            $editButton = '';
            if (Person::isAllowed('workTypes', 'edit')) {
                $editButton = $helper->buttonLink(
                    BASE_URI.'/workTypes/update?workType_id='.$type->getId(),
                    $this->_('edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
                );
            }
            echo "
            <tr><td>$editButton</td>
                <td>$name</td>
                <td>$description</td>
            </tr>
            ";
        }
    ?>
</table>
