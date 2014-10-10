<?php
use Blossom\Classes\View;
?>
<header>
	<ul id="utilityBar">
		<?php
			$li = '<li><a href="%s">%s</a></li>';

			if (isset($_SESSION['USER'])) {
				echo sprintf($li, BASE_URI.'/login/logout', $this->translate('logout'));
			}
			else {
				$return_url = View::escape($_SERVER['REQUEST_URI']);
				echo sprintf($li, BASE_URI.'/login?return_url='.$return_url, $this->_('login'));
			}
		?>
	</ul>
	<h1><a href="<?php echo BASE_URL; ?>/"><?php echo APPLICATION_NAME; ?></a></h1>
	<div id="location_name">
		<a href="<?php echo BASE_URL; ?>">City of Bloomington, Mark Kruzan, Mayor</a>
	</div>
	<?php
		$this->_include('partials/menubar.inc');
	?>
</header>
