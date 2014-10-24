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
