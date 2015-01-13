<?php
use Blossom\Classes\View;
use Application\Models\Person;
?>
<header>
	<div class="container">
		<div class="site-title">
			<h1><a href="<?php echo BASE_URL; ?>/"><?php echo APPLICATION_NAME; ?></a></h1>
			<div id="location_name" class="ext-location">
				<a href="<?php echo BASE_URL; ?>">City of Bloomington, Mark Kruzan, Mayor</a>
			</div>
		</div>
		<div id="utilityBar" class="site-utilityBar">

			<?php $a = '<a href="%s">%s</a>'; ?>
			<?php if (isset($_SESSION['USER'])) { ?>
				<div id="userDropdownLauncher" class="ext-launcher" aria-haspopup="true" aria-expanded="false"><i class="fa fa-chevron-down"></i> <?php echo View::escape($_SESSION['USER']->getFullname()); ?></div>
	
				<div class="ext-links closed" aria-hidden="true" id="userDropdown">

					<?php echo sprintf($a, BASE_URI.'/login/logout', $this->translate('logout')); ?>
				</div>			
			<?php } else {
					$return_url = View::escape($_SERVER['REQUEST_URI']);
					echo sprintf($a, BASE_URI.'/login?return_url='.$return_url, $this->_('login'));
			}
			?>
		</div>
		<div class="site-utilityBar">
			<div class="ext-launcher" id="siteSettingsLauncher" aria-haspopup="true" aria-expanded="false"><i class="fa fa-gear"></i> Settings</div>
			<div class="ext-links closed" id="siteSettingsDropdown">

				<?php
	
	
					$routes = [
						'people'     => 'person',
						'users'      => 'user'
					];
					foreach ($routes as $plural=>$singular) {
						$requiredAction = ($plural=='workTypes' || $plural=='issueTypes')
							? 'update'
							: 'index';
						if (Person::isAllowed($plural, $requiredAction)) {
							echo sprintf($a, BASE_URI.'/'.$plural, $this->_([$singular, $plural, 2]));
						}
					}
				?>
			</div>
		</div>
	</div>
	<?php $this->_include('partials/nav1.inc'); ?>
</header>
