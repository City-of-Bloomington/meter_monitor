<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;

use Application\Models\Issue;
use Application\Models\IssuesTable;
use Application\Models\Meter;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class IssuesController extends Controller
{
    private function loadIssue($id)
    {
        try {
            return new Issue($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/issues');
            exit();
        }
    }

    public function index()
    {
        $sort = !empty($_GET['sort']) ? $_GET['sort'] : null;
        $table = new IssuesTable();

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
            $this->template->blocks[] = new Block('issues/panel.inc', ['issues'=>$list]);
        }
        else {
            $list = $table->search($_GET, $sort);
            $this->template->blocks[] = new Block('issues/list.inc',  ['issues'=>$list]);
        }

    }

    public function update()
    {
        $issue =        !empty($_REQUEST['issue_id'])
            ? $this->loadIssue($_REQUEST['issue_id'])
            : new Issue();

        if (!empty($_GET['meter_id'])) {
            try {
                $meter = new Meter($_GET['meter_id']);
                $issue->setMeter($meter);
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
                $issue->handleUpdate($_POST);
                $issue->save();
                if (!$return_url) { $return_url = $issue->getMeter()->getUrl(); }
                header("Location: $return_url");
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        $this->template->blocks[] = new Block('issues/updateForm.inc', ['issue'=>$issue, 'return_url'=>$return_url]);
    }

    public function delete()
    {
        $issue = $this->loadIssue($_GET['issue_id']);
        try {
            $issue->delete();
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
        }

        header('Location: '.BASE_URL.'/issues');
        exit();
    }
}
