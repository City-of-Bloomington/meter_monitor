<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\WorkType;
use Application\Models\WorkTypesTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class WorkTypesController extends Controller
{
    private function loadType($id)
    {
        try {
            return new WorkType($id);
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/workTypes');
            exit();
        }
    }

    public function index()
    {
        $table = new WorkTypesTable();
        $list = $table->find();
        $this->template->blocks[] = new Block('workTypes/list.inc', ['workTypes'=>$list]);
    }

    public function update()
    {
        $type = !empty($_REQUEST['workType_id'])
            ? $this->loadType($_REQUEST['workType_id'])
            : new WorkType();

        if (isset($_POST['name'])) {
            $type->handleUpdate($_POST);

            try {
                $type->save();
                header('Location: '.BASE_URL.'/workTypes');
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }

        $this->template->blocks[] = new Block('workTypes/updateForm.inc', ['workType'=>$type]);
    }
}
