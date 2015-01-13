<?php
/**
 * @copyright 2009-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\ResultSet $people
 */
use Application\Models\Person;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<div class="interfaceBox">
	<h1><?php
			echo $this->translate(['person','people',2]);

			$return_url = Url::current_url();
			$helper = $this->template->getHelper('buttonLink');

			if (Person::isAllowed('people')) {
				echo $helper->buttonLink(
					BASE_URI."/people/update?return_url=$return_url",
					$this->_('add_person'),
					'add'
				);
			}
		?>
	</h1>
	<table class="output-tabular">
		<thead>
			<tr><th></th>
				<th><?php echo $this->_('username'); ?></th>
				<th><?php echo $this->_('name'); ?></th>
				<th><?php echo $this->_(['email','emails',1]); ?></th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->people as $person) {
				$editButton = '';
				if (Person::isAllowed('people')) {
					$editButton = $helper->buttonLink(
						BASE_URI."/people/update?person_id={$person->getId()};return_url=$return_url",
						$this->_('edit'),
						'edit'
					);
				}

				$name = View::escape($person->getFullname());
				echo "
				<tr><td>$editButton</td>
					<td>{$person->getUsername()}</td>
					<td><a href=\"{$person->getURL()}\">$name</a></td>
					<td>{$person->getEmail()}</td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</div>
