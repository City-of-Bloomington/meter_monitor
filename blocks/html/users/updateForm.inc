<?php
/**
 * @copyright 2006-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param User $this->user
 */
use Application\Models\Person;
use Blossom\Classes\View;

?>
<div class="updateUserForm">
    <form method="post" action="<?php echo BASE_URI; ?>/users/update">
        <fieldset><legend><?php echo $this->_(['user','users',2]); ?></legend>
            <input name="user_id" type="hidden" value="<?php echo $this->user->getId(); ?>" />
                <dl class="input-field mod-select"><dt><label for="authenticationMethod"><?php echo $this->_('authenticationMethod'); ?></label></dt>
                        <dd><select name="authenticationMethod" id="authenticationMethod">
                                <?php
                                        foreach (Person::getAuthenticationMethods() as $method) {
                                                $selected = $this->user->getAuthenticationMethod()==$method
                                                        ? 'selected="selected"'
                                                        : '';
                                                echo "<option $selected>$method</option>";
                                        }
                                ?>
                                </select>
                        </dd>
                </dl>
                <dl class="input-field mod-text"><dt><label for="username"><?php echo $this->_('username'); ?></label></dt>
                        <dd><input name="username" id="username" value="<?php echo View::escape($this->user->getUsername()); ?>" />
                        </dd>
                </dl>
                <dl class="input-field mod-text"><dt><label for="password"><?php echo $this->_('password'); ?></label></dt>
                        <dd><input name="password" id="password" /></dd>
                </dl>
                <dl class="input-field mod-select"><dt><label for="role"><?php echo $this->_('role'); ?></label></dt>
                        <dd><select name="role" id="role"><option></option>
                                <?php
                                        global $ZEND_ACL;
                                        foreach (array_reverse($ZEND_ACL->getRoles()) as $role) {
                                                $selected = $this->user->getRole()==$role
                                                        ? 'selected="selected"'
                                                        : '';
                                                echo "<option $selected>$role</option>";
                                        }
                                ?>
                                </select>
                        </dd>
                </dl>
            <?php
                    $helper = $this->template->getHelper('saveAndCancelButtons');
                    echo $helper->saveAndCancelButtons(BASE_URI.'/users');
            ?>
        </fieldset>
    </form>
</div>
