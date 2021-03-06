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
        $sort = !empty($_GET['sort']) ? $_GET['sort'] : null;
        $table = new WorkOrdersTable();

        if (!empty($_GET['print'])) {
            $pagination = false;
            $this->template->setFilename('print');
        }
        else {
            $pagination = true;
        }

        if ($this->template->outputFormat == 'html') {
            $list = $table->search($_GET, $sort, $pagination);

            if ($pagination) {
                $page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
                $list->setCurrentPageNumber($page);
                $list->setItemCountPerPage(20);
            }
            $this->template->blocks[] = new Block('workOrders/panel.inc', ['workOrders' => $list]);
        }
        else {
            $list = $table->search($_GET, $sort);
            $this->template->blocks[] = new Block('workOrders/list.inc',  ['workOrders' => $list]);
        }
    }

    public function view()
    {
        $workOrder = $this->loadWorkOrder($_GET['workOrder_id']);

        $this->template->blocks[] = new Block('workOrders/info.inc', ['workOrder'=>$workOrder]);
        $this->template->blocks[] = new Block('workTypes/list.inc', [
            'disableButtons' => true,
            'workTypes'      => $workOrder->getWorkTypes()
        ]);

        $_GET['print'] = true; // This should disable the csv download buttons in issues/list
        $this->template->blocks[] = new Block('issues/list.inc', [
            'disableButtons' => true,
            'issues'         => $workOrder->getIssues()
        ]);
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
