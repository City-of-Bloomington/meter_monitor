<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\IssueTypeGroup;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class IssueTypeGroupsController extends Controller
{
    private function loadGroup($id)
    {
        try {
            return new IssueTypeGroup($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/issueTypes');
            exit();
        }
    }

    public function index()
    {
    }

    public function update()
    {
        $group = !empty($_REQUEST['issueTypeGroup_id'])
            ? $this->loadGroup($_REQUEST['issueTypeGroup_id'])
            : new IssueTypeGroup();

        if (isset($_POST['name'])) {
            $group->handleUpdate($_POST);
            try {
                $group->save();
                header('Location: '.BASE_URL.'/issueTypes');
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        $this->template->blocks[] = new Block('issueTypeGroups/updateForm.inc', ['issueTypeGroup'=>$group]);
    }
}