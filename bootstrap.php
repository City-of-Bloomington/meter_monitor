<?php
/**
 * Where on the filesystem this application is installed
 */
define('APPLICATION_HOME', __DIR__);
define('VERSION', trim(file_get_contents(APPLICATION_HOME.'/VERSION')));

/**
 * Multi-Site support
 *
 * To allow multiple sites to use this same install base,
 * define the SITE_HOME variable in the Apache config for each
 * site you want to host.
 *
 * SITE_HOME is the directory where all site-specific data and
 * configuration are stored.  For backup purposes, backing up this
 * directory would be sufficient for an easy full restore.
 */
define('SITE_HOME', !empty($_SERVER['SITE_HOME']) ? $_SERVER['SITE_HOME'] : __DIR__.'/data');

/**
 * Enable autoloading for the PHP libraries
 */
$loader = require APPLICATION_HOME.'/vendor/autoload.php';
$loader->addPsr4('Site\\', SITE_HOME.'/src');

include SITE_HOME.'/site_config.inc';
include APPLICATION_HOME.'/access_control.inc';

/**
 * Session Startup
 * Don't start a session for CLI usage.
 * We only want sessions when PHP code is executed from the webserver
 */
if (!defined('STDIN')) {
	ini_set('session.save_path', SITE_HOME.'/sessions');
	session_start();
}

if (ERROR_REPORTING != 'PHP_DEFAULT') {
    set_error_handler         ('Blossom\Classes\Error::customErrorHandler');
    set_exception_handler     ('Blossom\Classes\Error::customExceptionHandler');
    register_shutdown_function('Blossom\Classes\Error::shutdownHandler');
}

