<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Templates\Helpers;

use Blossom\Classes\Helper;
use Blossom\Classes\View;

class DateTimePicker extends Helper
{
    public function dateTimePicker($fieldname, $timestamp=null)
    {
        $this->template->addToAsset('scripts',     JQUERY   .'/jquery.min.js');
        $this->template->addToAsset('scripts',     JQUERY_UI.'/jquery-ui.min.js');
        $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
        $this->template->addToAsset('scripts',     JQUERY_TIMEPICKER.'/jquery.timepicker.min.js');
        $this->template->addToAsset('stylesheets', JQUERY_TIMEPICKER.'/jquery.timepicker.css');
        $this->template->addToAsset('scripts',     BASE_URI.'/js/dateTimePicker.js');

        $date = '';
        $time = '';
        if ($timestamp) {
            $date = date(DATE_FORMAT, $timestamp);
            $time = date(TIME_FORMAT, $timestamp);
        }

        $input = "
        <input name=\"{$fieldname}[date]\" id=\"$fieldname\"        value=\"$date\" size=\"10\" class=\"date\"/>
        <input name=\"{$fieldname}[time]\" id=\"{$fieldname}-time\" value=\"$time\" size=\"10\" class=\"time\" />
        ";
        return $input;
    }
}
