<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;

use Application\Models\WorkOrder;
use Application\Models\WorkOrdersTable;
use Application\Models\Meter;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class WorkOrdersController extends Controller
{
    private function loadWorkOrder($id)
    {
        try {
            return new WorkOrder($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/workOrders');
            exit();
        }
    }

    public function index()
    {
        $table = new WorkOrdersTable();

        $list = (!empty($_GET['meter']) || !empty($_GET['zone']) || !empty($_GET['issueType_id']))
            ? $table->search($_GET, null, true)
            : $table->find  (null,  null, true);

        $page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
        $list->setCurrentPageNumber($page);
        $list->setItemCountPerPage(20);

        $this->template->blocks[] = new Block('workOrders/panel.inc', ['workOrders'=> $list]);
    }

    public function update()
    {
        $workOrder =    !empty($_REQUEST['workOrder_id'])
            ? $this->loadWorkOrder($_REQUEST['workOrder_id'])
            : new WorkOrder();

        if (!empty($_GET['meter_id'])) {
            try {
                $meter = new Meter($_GET['meter_id']);
                $workOrder->setMeter($meter);
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
                header('Location: '.BASE_URL.'/meters');
                exit();
            }
        }

        $return_url = !empty($_REQUEST['return_url'])
            ? $_REQUEST['return_url']
            : null;

        if (isset($_POST['meter_id'])) {
            try {
                $workOrder->handleUpdate($_POST);
                $workOrder->save();
                if (!$return_url) { $return_url = $workOrder->getMeter()->getUrl(); }
                header("Location: $return_url");
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
                print_r($e);
            }
        }

        $meter = $workOrder->getMeter();
        if ($meter) {
            $this->template->blocks[] = new Block('meters/view.inc', ['meter'=>$meter]);
        }

        $this->template->blocks[] = new Block('workOrders/updateForm.inc', ['workOrder'=>$workOrder, 'return_url'=>$return_url]);
    }

    public function delete()
    {
        $workOrder = $this->loadWorkOrder($_GET['workOrder_id']);

        $meter = $workOrder->getMeter();
        try {
            $workOrder->delete();
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
        }
        header('Location: '.$meter->getUrl());
        exit();
    }
}
