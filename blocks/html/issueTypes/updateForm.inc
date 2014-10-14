<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param IssueType $this->issueType
 */
use Blossom\Classes\View;

$name        = View::escape($this->issueType->getName());
$description = View::escape($this->issueType->getDescription());

$title = $this->issueType->getId() ? $this->_('edit') : $this->_('add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/issueTypes/update">
    <fieldset><legend><?php echo $this->_(['issueType', 'issueTypes', 1]); ?></legend>
        <input name="issueType_id" type="hidden" value="<?php echo $this->issueType->getId(); ?>" />

        <table>
            <tr><td><label for="name"><?php echo $this->_('name'); ?></label></td>
                <td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
            </tr>
        </table>
        <div>
            <div><label for="description"><?php echo $this->_('description'); ?></label></div>
            <textarea name="description" id="description"><?php echo $description; ?></textarea>
        </div>

        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons(BASE_URI.'/issueTypes');
        ?>
    </fieldset>
</form>
