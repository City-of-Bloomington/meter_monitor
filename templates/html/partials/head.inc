<?php
use Blossom\Classes\View;

$jQueryDateFormat = str_replace(['m',  'n', 'd',  'j', 'Y' ],
                                ['mm', 'm', 'dd', 'd', 'yy'],
                                DATE_FORMAT);
?>
<head>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="stylesheet" type="text/css" href="<?= BASE_URI; ?>/css/local/reset.css" />
    <link rel="stylesheet" type="text/css" href="<?= BASE_URI; ?>/css/local/layouts/<?= $this->layout; ?>.css" />
    <link rel="stylesheet" type="text/css" href="<?= BASE_URI; ?>/css/local/screen.css" />
    <link rel="stylesheet" type="text/css" href="<?= BASE_URI; ?>/css/Font-Awesome/css/font-awesome.css" />
    <link rel="stylesheet" type="text/css" href="<?= BASE_URI; ?>/css/open-sans/open-sans.css" />
    <title><?= isset($this->title) ? self::escape($this->title) : APPLICATION_NAME; ?></title>

    <script type="text/javascript">
    var METERS = {
           BASE_URI: '<?= BASE_URI; ?>',
        DATE_FORMAT: '<?= $jQueryDateFormat; ?>',
        TIME_FORMAT: '<?= TIME_FORMAT; ?>'
    };
    </script>
</head>
