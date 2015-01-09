<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Application\Models\Issue;
?>
<form method="get" action="<?php echo BASE_URI; ?>/issues">
    <fieldset><legend><?php echo $this->_('search'); ?></legend>

        <table>
        <?php include APPLICATION_HOME.'/blocks/html/issues/partials/searchFields.inc'; ?>
        </table>

        <div>
            <label><?php echo $this->_('reportedDate'); ?></label>
            <label for="reportedDate-start"><?php echo $this->_('start'); ?></label>
            <?php
                $h = $this->template->getHelper('datePicker');
                $d = !empty($_GET['reportedDate-start']) ? strtotime($_GET['reportedDate-start']) : null;
                echo $h->datePicker('reportedDate-start', $d);
            ?>
            <label for="reportedDate-end"><?php echo $this->_('end'); ?></label>
            <?php
                $d = !empty($_GET['reportedDate-end']) ? strtotime($_GET['reportedDate-end']) : null;
                echo $h->datePicker('reportedDate-end', $d);
            ?>
        </div>

        <div>
            <label><?php echo $this->_('status'); ?></label>
            <label>
            <?php
                $value = Issue::STATUS_OPEN;
                $checked = (!empty($_GET['status']) && $_GET['status']==$value)
                    ? 'checked="checked"'
                    : '';
                echo "<input name=\"status\" type=\"radio\" value=\"$value\" $checked /> ";
                echo $this->_($value);
            ?>
            </label>
            <label>
            <?php
                $value = Issue::STATUS_CLOSED;
                $checked = (!empty($_GET['status']) && $_GET['status']==$value)
                    ? 'checked="checked"'
                    : '';
                echo "<input name=\"status\" type=\"radio\" value=\"$value\" $checked /> ";
                echo $this->_($value);
            ?>
            </label>
        </div>

        <button type="submit"><i class="fa fa-search"></i> <?php echo $this->_('search'); ?></button>
        <a href="<?php echo BASE_URI; ?>/issues"><?php echo $this->_('clear'); ?></a>
    </fieldset>
</form>
