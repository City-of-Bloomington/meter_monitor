<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class WorkTypesTable extends TableGateway
{
    protected $columns = ['id', 'name'];

    public function __construct() { parent::__construct('workTypes', __namespace__.'\WorkType'); }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function find($fields=null, $order='name', $paginated=false, $limit=null)
    {
        $select = new Select('workTypes');
        if (count($fields)) {
            foreach ($fields as $key=>$value) {
                if (!empty($value)) {
                    switch ($key) {
                        case 'issue_id':
                            $select->join(['t'=>'issue_workTypes'], 't.workType_id=workTypes.id', []);
                            $select->where(["t.$key"=>$value]);
                            break;
                        default:
                            if (in_array($key, $this->columns)) {
                                $select->where([$key=>$value]);
                            }
                    }
                }
            }
        }
        return parent::performSelect($select, $order, $paginated, $limit);
    }
}
