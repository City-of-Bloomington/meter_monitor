<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\Activity;
use Application\Models\ActivityTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class ActivityController extends Controller
{
    private function loadActivity($id)
    {
        try {
            return new Activity($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/activity');
            exit();
        }
    }

    public function index()
    {
        $table = new ActivityTable();

        $a = (!empty($_GET['meter']) || !empty($_GET['zone']) || !empty($_GET['issueType_id']))
            ? $table->search($_GET, null, true)
            : $table->find  (null,  null, true);

        $page = !empty($_GET['page']) ? (int)$_GET['page'] : 1;
        $a->setCurrentPageNumber($page);
        $a->setItemCountPerPage(20);

        $this->template->blocks[] = new Block('activity/searchForm.inc');
        $this->template->blocks[] = new Block('activity/list.inc',  ['activity'   => $a]);
        $this->template->blocks[] = new Block('pageNavigation.inc', ['paginator'  => $a]);
    }

    public function update()
    {
        $activity = !empty($_REQUEST['activity_id'])
            ? $this->loadActivity($_REQUEST['activity_id'])
            : new Activity();

        if (isset($_POST['meter'])) {
            $_POST['reportedDate'] = implode(' ', [$_POST['reportedDate']['date'], $_POST['reportedDate']['time']]);
            $_POST['resolvedDate'] = implode(' ', [$_POST['resolvedDate']['date'], $_POST['resolvedDate']['time']]);

            $activity->handleUpdate($_POST);
            try {
                $activity->save();
                header('Location: '.BASE_URL.'/activity');
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        $this->template->blocks[] = new Block('activity/updateForm.inc', ['activity'=>$activity]);
    }
}
