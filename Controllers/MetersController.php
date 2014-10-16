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
    private function loadMeter($id)
    {
        try {
            return new Meter($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/meters');
            exit();
        }
    }

    public function index()
    {
        $table = new MetersTable();

        $pagination = $this->template->outputFormat == 'html';

        // Translate jQuery autocomplete searches
        if (!empty($_GET['term'])) {
            $_GET['name'] = $_GET['term'];
            unset($_GET['term']);
        }

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

    public function view()
    {
        if (empty($_GET['meter_id'])) {
            $_SESSION['errorMessages'][] = new \Exception('meters/unknownMeter');
            header('Location: '.BASE_URL.'/meters');
            exit();
        }

        $meter = $this->loadMeter($_GET['meter_id']);
        $issues = $meter->getIssues();
        $work   = $meter->getWorkOrders();

        $this->template->blocks[] = new Block('meters/view.inc',     ['meter'=>$meter]);
        $this->template->blocks[] = new Block(    'issues/list.inc', ['meter'=>$meter, 'issues'    =>$issues]);
        $this->template->blocks[] = new Block('workOrders/list.inc', ['meter'=>$meter, 'workOrders'=>$work]);
    }
}
