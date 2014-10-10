<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\Meter;
use Application\Models\MetersTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class MetersController extends Controller
{
    public function index()
    {
        $table = new MetersTable();

        $pagination = $this->template->outputFormat == 'html';

        $list = (!empty($_GET['name']) || !empty($_GET['zone']))
            ? $table->search($_GET, null, $pagination)
            : $table->find  (null,  null, $pagination);

        if ($pagination) {
            $page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
            $list->setCurrentPageNumber($page);
            $list->setItemCountPerPage(20);

            $this->template->blocks[] = new Block('meters/searchForm.inc');
            $this->template->blocks[] = new Block('meters/list.inc',    ['meters'    => $list]);
            $this->template->blocks[] = new Block('pageNavigation.inc', ['paginator' => $list]);
        }
        else {
            $this->template->blocks[] = new Block('meters/list.inc', ['meters' => $list]);
        }
    }
}
