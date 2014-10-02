"use strict";
jQuery(function ($) {
    $('.date').datepicker({
        dateFormat: METERS.DATE_FORMAT,
        showAnim: ''
    });
    $('.time').timepicker({
        timeFormat: METERS.TIME_FORMAT
    });
});
