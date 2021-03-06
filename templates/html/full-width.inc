<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
	$this->layout = 'full-width';
	$this->_include('partials/head.inc');
?>
<body>
	<?php
		$this->_include('partials/header.inc');
	?>
	<main>
		<div class="container">
			<?php
                $this->_include('errorMessages.inc');
				echo $this->includeBlocks();
			?>
		</div>
	</main>
	<?php
		$this->_include('partials/footer.inc');
	?>
</body>
</html>
<?php
	$this->_include('partials/garbageCollection.inc');
?>
