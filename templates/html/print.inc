<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<?php
    $this->layout = 'full-width';
    $this->_include('partials/head.inc');
?>
<body>
    <div id="panel-container">
        <div id="content-panel">
            <?php
                $this->_include('errorMessages.inc');
                echo $this->includeBlocks();
            ?>
        </div>
    </div>
    <?php
        $this-> _include('partials/footer.inc');
    ?>
</body>
</html>
<?php
    $this->_include('partials/garbageCollection.inc');
?>
