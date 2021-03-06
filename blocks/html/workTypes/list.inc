<?php
/**
 * @copyright 2014-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Zend\Db\Result $this->workTypes
 * @param boolean $this->disableButtons (optional)
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<section>
    <header>
        <h1><?= $this->_(['workType', 'workTypes', 2]); ?></h1>
        <?php
            if (!$this->disableButtons && Person::isAllowed('workTypes', 'edit')) {
                $helper = $this->template->getHelper('buttonLink');
                echo '<div class="tools">';
                echo $helper->buttonLink(
                    BASE_URI.'/workTypes/update',
                    $this->_('add'),
                    'add'
                );
                echo '</div>';
            }
        ?>
    </header>
    <table class="output-tabular">
        <?php
            foreach ($this->workTypes as $type) {
                $name        = View::escape($type->getName());
                $description = View::escape($type->getDescription());

                $editButton = '';
                if (!$this->disableButtons && Person::isAllowed('workTypes', 'edit')) {
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
</section>