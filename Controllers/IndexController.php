<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\Person;
use Blossom\Classes\Controller;

class IndexController extends Controller
{
	public function index()
	{
        if (Person::isAllowed('issues', 'add')) {
            header('Location: '.BASE_URL.'/issues');
        }
        else {
            header('Location: '.BASE_URL.'/login?return_url='.BASE_URL.'/issues');
        }
        exit();
	}
}
