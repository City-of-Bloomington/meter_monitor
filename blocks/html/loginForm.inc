<?php
/**
 * @copyright 2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param string $this->return_url
 */
declare (strict_types=1);
?>
<form method="post" action="<?= BASE_URI; ?>/login/login">
	<fieldset><legend><?= $this->_('login'); ?></legend>
		<input name="return_url" type="hidden" value="<?= parent::escape($this->return_url); ?>" />
		<table>
			<tr><th><label for="username"><?= $this->_('username'); ?></label></th>
				<td><input name="username" id="username" /></td><td></td>
			</tr>
			<tr><th><label for="password"><?= $this->_('password'); ?></label></th>
				<td><input type="password" name="password" id="password" /></td>
			</tr>
		</table>
		<button type="submit" class="login"><?= $this->_('login'); ?></button>
	</fieldset>
</form>
