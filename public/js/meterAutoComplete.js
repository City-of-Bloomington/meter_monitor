"use strict";
jQuery('#meter_id').autocomplete({
    source: METERS.BASE_URI + '/meters?format=json'
});
jQuery('#meter').autocomplete({
    source: METERS.BASE_URI + '/meters?format=json'
});
