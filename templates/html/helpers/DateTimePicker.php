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
        $value = $timestamp ? date(DATE_FORMAT, $timestamp) : '';

        $input = "<input name=\"$fieldname\" id=\"$fieldname\" value=\"$value\" />";
        $help  = View::translateDateString(DATE_FORMAT);

        return "$input $help";
    }
}
