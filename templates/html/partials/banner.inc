<?php
use Blossom\Classes\View;
?>
<header class="header-row">
	<div class="header-container">
		<div class="header-title">
			<h1><a href="<?php echo BASE_URL; ?>/"><?php echo APPLICATION_NAME; ?></a></h1>
			<div id="location_name" class="header-location">
				<a href="<?php echo BASE_URL; ?>">City of Bloomington, Mark Kruzan, Mayor</a>
			</div>
		</div>
		<div id="utilityBar" class="header-utilityBar">
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
	<?php
		$this->_include('partials/menubar.inc');
	?>
</header>
