<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\Issue;
use Application\Models\IssuesTable;
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
        $table = new IssuesTable();

        $list = (!empty($_GET['meter']) || !empty($_GET['zone']) || !empty($_GET['issueType_id']))
            ? $table->search($_GET, null, true)
            : $table->find  (null,  null, true);

        $page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
        $list->setCurrentPageNumber($page);
        $list->setItemCountPerPage(20);

        $this->template->blocks[] = new Block('issues/searchForm.inc');
        $this->template->blocks[] = new Block('issues/list.inc',    ['issues'    => $list]);
        $this->template->blocks[] = new Block('pageNavigation.inc', ['paginator' => $list]);
    }

    public function update()
    {
        $issue =        !empty($_REQUEST['issue_id'])
            ? $this->loadIssue($_REQUEST['issue_id'])
            : new Issue();

        if (isset($_POST['meter_id'])) {
            $issue->handleUpdate($_POST);
            try {
                $issue->save();
                header('Location: '.BASE_URL.'/issues');
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        $this->template->blocks[] = new Block('issues/updateForm.inc', ['issue'=>$issue]);
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
