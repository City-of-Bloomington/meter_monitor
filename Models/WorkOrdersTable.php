<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class WorkOrdersTable extends TableGateway
{
    protected $columns = ['id', 'meter_id', 'completedByPerson_id'];
    const DEFAULT_ORDER = 'dateCompleted desc';

    public function __construct() { parent::__construct('workOrders', __namespace__.'\WorkOrder'); }

    private function handleJoins($fields, &$select)
    {
        if (   (array_key_exists('issue_id',            $fields) && !empty($fields['issue_id']))
            || (array_key_exists('reportedByPerson_id', $fields) && !empty($fields['reportedByPerson_id']))) {
            $select->join(['i'=>'issues'], 'workOrders.id=i.workOrder_id', []);
        }
        if (   (array_key_exists('meter', $fields) && !empty($fields['meter']))
            || (array_key_exists('zone',  $fields) && !empty($fields['zone']))) {
            $select->join(['m'=>'meters'], 'workOrders.meter_id=m.id', []);
        }
    }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function find($fields=null, $order=self::DEFAULT_ORDER, $paginated=false, $limit=null)
    {
        $select = new Select('workOrders');
        if (count($fields)) {
            $this->handleJoins($fields, $select);

            foreach ($fields as $key=>$value) {
                if ($value) {
                    switch ($key) {
                        case 'issue_id':
                        case 'reportedByPerson_id':
                            $select->where(["i.$key"=>$value]);
                            break;

                        case 'meter':
                        case 'zone':
                            $select->where(["m.$key"=>$value]);
                            break;

                        default:
                            if (in_array($key, $this->columns)) {
                                $select->where([$key=>$value]);
                            }
                    }
                }
            }
        }
        $order = $order ?: self::DEFAULT_ORDER;
        return parent::performSelect($select, $order, $paginated, $limit);
    }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function search($fields=null, $order=self::DEFAULT_ORDER, $paginated=false, $limit=null)
    {
        $select = new Select('workOrders');
        if (count($fields)) {
            $this->handleJoins($fields, $select);

            foreach ($fields as $key=>$value) {
                if ($value) {
                    switch ($key) {
                        case 'issue_id':
                        case 'reportedByPerson_id':
                            $select->where(["i.$key"=>$value]);
                            break;

                        case 'meter':
                            $select->where->like('m.name', "$value%");
                            break;
                        case 'zone':
                            $select->where(["m.$key"=>$value]);
                            break;

                        default:
                            if (in_array($key, $this->columns)) {
                                $select->where([$key=>$value]);
                            }
                    }
                }
            }
        }
        $order = $order ?: self::DEFAULT_ORDER;
        return parent::performSelect($select, $order, $paginated, $limit);
    }
}
