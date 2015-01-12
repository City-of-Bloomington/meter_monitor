<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param IssueTypeGroup $this->issueTypeGroup
 */
use Blossom\Classes\View;

$name        = View::escape($this->issueTypeGroup->getName());

$title = $this->issueTypeGroup->getId() ? $this->_('edit') : $this->_('add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/issueTypeGroups/update">
    <fieldset><legend><?php echo $this->_(['issueTypeGroup', 'issueTypeGroups', 1]); ?></legend>
        <input name="issueTypeGroup_id" type="hidden" value="<?php echo $this->issueTypeGroup->getId(); ?>" />

        <table>
            <tr><td><label for="name"><?php echo $this->_('name'); ?></label></td>
                <td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
            </tr>
        </table>

        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons(BASE_URI.'/issueTypes');
        ?>
    </fieldset>
</form>
