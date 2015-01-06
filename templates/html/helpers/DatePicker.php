<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Templates\Helpers;

use Blossom\Classes\Helper;
use Blossom\Classes\View;

class DatePicker extends Helper
{
    public function datePicker($fieldname, $timestamp=null)
    {
        $this->template->addToAsset('scripts',     JQUERY   .'/jquery.min.js');
        $this->template->addToAsset('scripts',     JQUERY_UI.'/jquery-ui.min.js');
        $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
        $this->template->addToAsset('scripts',     JQUERY_TIMEPICKER.'/jquery.timepicker.min.js');
        $this->template->addToAsset('stylesheets', JQUERY_TIMEPICKER.'/jquery.timepicker.css');
        $this->template->addToAsset('scripts',     BASE_URI.'/js/dateTimePicker.js');

        $date = '';
        if ($timestamp) {
            $date = date(DATE_FORMAT, $timestamp);
        }

        $help = View::translateDateString(DATE_FORMAT);

        return "
        <input name=\"{$fieldname}\" id=\"$fieldname\" value=\"$date\"
               size=\"10\" class=\"date\" placeholder=\"$help\" type=\"text\" />
        ";
    }
}
