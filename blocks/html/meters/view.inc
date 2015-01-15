<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Meter $this->meter
 */
use Application\Models\Person;
use Blossom\Classes\Block;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h2><?php echo View::escape($this->meter->getName()); ?></h2>
<table>
    <tr><th><?php echo $this->_('zone'); ?></th>
        <td><?php echo $this->meter->getZone(); ?></td>
    </tr>
</table>

<section>
    <header>
        <h3><?php echo $this->_(['issue', 'issues', 2]); ?></h3>
        <?php
            $helper     = $this->template->getHelper('buttonLink');
            $return_url = Url::current_url();

            if (Person::isAllowed('issues', 'update')) {
                echo '<div class="tools">';
                echo $helper->buttonLink(
                    BASE_URI."/issues/update?meter_id={$this->meter->getId()};return_url=$return_url",
                    $this->_('issue_add'),
                    'add'
                );
                echo '</div>';
            }
        ?>
    </header>
    <?php
        $block = new Block('issues/list.inc', ['meter'=>$this->meter, 'issues'=>$this->meter->getIssues()]);
        echo $block->render('html', $this->template);
    ?>
</section>

<section>
    <header>
        <h3><?php echo $this->_(['workOrder', 'workOrders', 2]); ?></h3>
        <?php
            if (Person::isAllowed('workOrders', 'update')) {
                echo '<div class="tools">';
                echo $helper->buttonLink(
                    BASE_URI."/workOrders/update?meter_id={$this->meter->getId()};return_url=$return_url",
                    $this->_('workOrder_add'),
                    'add'
                );
                echo '</div>';
            }
        ?>
    </header>
    <?php
        $block = new Block('workOrders/list.inc', ['meter'=>$this->meter, 'workOrders'=>$this->meter->getWorkOrders()]);
        echo $block->render('html', $this->template);
    ?>
</section>
