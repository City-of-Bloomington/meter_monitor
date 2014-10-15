<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Templates\Helpers;

use Application\Models\Meter;
use Blossom\Classes\Helper;
use Blossom\Classes\View;

class ZoneSelector extends Helper
{
    public function zoneSelector($selectedZone, $id='zone')
    {
        $html = "<select name=\"$id\" id=\"$id\"><option value=\"\"></option>";
        $zones = Meter::getDistinct('zone');
        foreach ($zones as $z) {
            $selected = $z==$selectedZone
                ? 'selected="selected"'
                : '';
            $html.= "<option $selected>$z</option>";
        }
        $html.= '</select>';
        return $html;
    }
}
