<?php
use Blossom\Classes\View;
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
			<?php
				$li = '<a href="%s">%s</a>';

				if (isset($_SESSION['USER'])) {
					echo sprintf($li, BASE_URI.'/login/logout', $this->translate('logout'));
				}
				else {
					$return_url = View::escape($_SERVER['REQUEST_URI']);
					echo sprintf($li, BASE_URI.'/login?return_url='.$return_url, $this->_('login'));
				}
			?>
		</div>
	</div>
	<?php $this->_include('partials/nav1.inc'); ?>
</header>
