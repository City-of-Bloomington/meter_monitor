<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
	$this->layout = 'three-column';
	$this->_include('partials/header.inc');
?>
<body>
    <div class="layout-container">
	<?php
		$this->_include('partials/banner.inc');
	?>
	<div id="panel-container">
		<?php
			$this->_include('partials/panel-one.inc');
			$this->_include('partials/panel-two.inc');
		?>
		<div id="content-panel">
			<?php
                $this->_include('errorMessages.inc');
				echo $this->includeBlocks();
			?>
		</div>
	</div>
	<?php
		$this->_include('partials/footer.inc');
	?>
    </div>
</body>
</html>
<?php
	$this->_include('partials/garbageCollection.inc');
?>
