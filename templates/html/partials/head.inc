<?php
use Blossom\Classes\View;
?>
<head>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="stylesheet" type="text/css" href="<?php echo BASE_URI; ?>/css/local/reset.css" />
    <link rel="stylesheet" type="text/css" href="<?php echo BASE_URI; ?>/css/local/layouts/<?php echo $this->layout; ?>.css" />
    <link rel="stylesheet" type="text/css" href="<?php echo BASE_URI; ?>/css/local/screen.css" />
    <link rel="stylesheet" type="text/css" href="<?php echo BASE_URI; ?>/css/Font-Awesome/css/font-awesome.css" />
    <link href='http://fonts.googleapis.com/css?family=Open+Sans:400italic,700italic,300,400,700,600' rel='stylesheet' type='text/css'>
    <title><?php echo isset($this->title) ? self::escape($this->title) : APPLICATION_NAME; ?></title>

    <script type="text/javascript">
    var METERS = {
           BASE_URI: '<?php echo BASE_URI; ?>',
        DATE_FORMAT: '<?php echo View::jQueryDateFormat(DATE_FORMAT); ?>',
        TIME_FORMAT: '<?php echo TIME_FORMAT; ?>'
    };
    </script>
</head>
