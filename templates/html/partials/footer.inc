<div id="footer">
	<p>
		<?php
			global $startTime;

			# Calculate the process time
			$endTime = microtime(1);
			$processTime = $endTime - $startTime;
			echo "<!-- Process Time: $processTime -->";
		?>
	</p>
</div>
<?php
	if (isset($this->assets['scripts'])) {
		foreach ($this->assets['scripts'] as $url) {
			echo "<script type=\"text/javascript\" src=\"$url\"></script>\n";
		}
	}
	if (isset($this->assets['stylesheets'])) {
		foreach ($this->assets['stylesheets'] as $url) {
			echo "<link rel=\"stylesheet\" href=\"$url\" />\n";
		}
	}
?>
<script type="text/javascript" src="<?php echo BASE_URI ?>/js/dropdown.js"></script>
<script type="text/javascript">
	$(function(){
		var menu = new rpdm($('#userDropdownLauncher'), $('#userDropdown'));
		menu.buttonClick().documentClick();

		var settingsMenu = new rpdm($('#siteSettingsLauncher'), $('#siteSettingsDropdown'));
		settingsMenu.buttonClick().documentClick();
	});
</script>