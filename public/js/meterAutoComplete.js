"use strict";
jQuery('input.meterAutoComplete').autocomplete({
    source: METERS.BASE_URI + '/meters?format=json'

});
