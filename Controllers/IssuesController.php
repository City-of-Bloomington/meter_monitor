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

        $issues = (!empty($_GET['meter']) || !empty($_GET['zone']) || !empty($_GET['issueType_id']))
            ? $table->search($_GET, null, true)
            : $table->find  (null,  null, true);

        $page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
        $issues->setCurrentPageNumber($page);
        $issues->setItemCountPerPage(20);

        $this->template->blocks[] = new Block('issues/searchForm.inc');
        $this->template->blocks[] = new Block('issues/list.inc',    ['issues'   =>$issues]);
        $this->template->blocks[] = new Block('pageNavigation.inc', ['paginator'=>$issues]);
    }

    public function update()
    {
        $issue = !empty($_REQUEST['issue_id'])
            ? $this->loadIssue($_REQUEST['issue_id'])
            : new Issue();

        if (isset($_POST['meter'])) {
            $_POST['reportedDate'] = implode(' ', [$_POST['reportedDate']['date'], $_POST['reportedDate']['time']]);
            $_POST['resolvedDate'] = implode(' ', [$_POST['resolvedDate']['date'], $_POST['resolvedDate']['time']]);

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
}
