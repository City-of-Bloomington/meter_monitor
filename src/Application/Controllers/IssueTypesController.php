<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\IssueType;
use Application\Models\IssueTypesTable;
use Application\Models\IssueTypeGroupsTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class IssueTypesController extends Controller
{
    private function loadType($id)
    {
        try {
            return new IssueType($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/issueTypes');
            exit();
        }
    }

    public function index()
    {
        if (!empty($_GET['print'])) {
            $this->template->setFilename('print');
        }
        
        $table = new IssueTypeGroupsTable();
        $list = $table->find();
        $this->template->blocks[] = new Block('issueTypes/list.inc', ['issueTypeGroups'=>$list]);
    }

    public function update()
    {
        $type = !empty($_REQUEST['issueType_id'])
            ? $this->loadType($_REQUEST['issueType_id'])
            : new IssueType();

        if (!empty($_REQUEST['issueTypeGroup_id'])) {
            try {
                $type->setGroup_id($_REQUEST['issueTypeGroup_id']);
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        if (isset($_POST['name'])) {
            $type->handleUpdate($_POST);

            try {
                $type->save();
                header('Location: '.BASE_URL.'/issueTypes');
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        $this->template->blocks[] = new Block('issueTypes/updateForm.inc', ['issueType'=>$type]);
    }
}
