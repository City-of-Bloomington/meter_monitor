<?php
/**
 * @copyright 2009-2017 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Person $this->person
 */
use Application\Models\Person;
use Blossom\Classes\View;
use Blossom\Classes\Url;

$return_url = Url::current_url(BASE_HOST);
$h = $this->template->getHelper('buttonLink');

$username = $this->person->getUsername();
if (!$username && Person::isAllowed('users')) {
	$username = $h->buttonLink(
		BASE_URI."/users/update?user_id={$this->person->getId()};return_url=$return_url",
		$this->_('create_account'),
		'add'
	);
}

$editButton = '';
if (Person::isAllowed('people', 'edit')) {
    $editButton = $h->buttonLink(
        BASE_URI."/people/update?person_id={$this->person->getId()};return_url=$return_url",
        $this->_('edit'),
        'edit'
    );
}
$name = View::escape($this->person->getFullname());
echo <<<EOT
<div class="personInfo">
	<h2>$name $editButton</h2>
	<table>
		<tr><th>Email</th>
			<td>{$this->person->getEmail()}</td>
		</tr>
		<tr><th>Username</th>
			<td>$username</td>
		</tr>
	</table>
</div>
EOT;
