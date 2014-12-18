<?php
/**
 * Helper for rendering links to sort data by certain columns
 *
 * These links are usually placed in the TH of tables.
 * This helper only supports sorting on a single column at a
 * time.  Mult-column sort will require a different implementation.
 *
 * This uses a GET[sort] parameter. The sort parameter is a string
 * that will be passed to the TableGateway::find() method.  It is
 * usually "database_field asc|desc"
 *
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Templates\Helpers;

use Blossom\Classes\Helper;
use Blossom\Classes\Url;

class SortableLabel extends Helper
{
    private function getSortArray($sortString)
    {
        $sortArray = [];
        foreach (explode(',', $sortString) as $term) {
            $term = trim($term);
            $m = explode(' ', $term);
            $m[1] = !empty($m[1]) ? $m[1]: 'asc';

            $sortArray[$m[0]] = $m[1];
        }
        return $sortArray;
    }

    private function getSortString($sortArray)
    {
        $sort = [];
        foreach ($sortArray as $field=>$dir) {
            $sort[] = "$field $dir";
        }
        return implode(',', $sort);
    }

    /**
     * Renders the link for sorting data based on a single column
     *
     * @param GET sort
     * @param string $label
     * @param string $currentSort
     */
    public function sortableLabel($field, $label, $currentSort)
    {
        $sortArray = $this->getSortArray($currentSort);
        $sortArray[$field] = $sortArray[$field]=='desc' ? 'asc' : 'desc';

        $url = new Url(Url::current_url());
        $url->sort = $this->getSortString($sortArray);

        $icon = $sortArray[$field] == 'desc'
            ? '<i class="fa fa-angle-up"></i>'
            : '<i class="fa fa-angle-down"></i>';
        return "<a href=\"$url\">$label $icon</a>";
    }
}