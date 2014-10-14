<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class IssuesTable extends TableGateway
{
    protected $columns = ['id', 'meter'];

    public function __construct() { parent::__construct('issues', __namespace__.'\Issue'); }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function find($fields=null, $order='reportedDate desc', $paginated=false, $limit=null)
    {
        return parent::find($fields, $order, $paginated, $limit);
    }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function search($fields=null, $order='reportedDate desc', $paginated=false, $limit=null)
    {
        $select = new Select('issues');
        if (count($fields)) {
            $this->handleJoins($fields, $select);

            foreach ($fields as $key=>$value) {
                if (!empty($value)) {
                    switch ($key) {
                        case 'meter':
                            $select->where->like('m.name', "$value%");
                            break;

                        case 'zone':
                            $select->where(["m.$key"=>$value]);
                            break;

                        case 'issueType_id':
                            $select->where(["i.$key"=>$value]);
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

    private function handleJoins($fields, &$select)
    {
        if (count(array_intersect(['meter', 'zone'], array_keys($fields)))) {
            $select->join(['m'=>'meters'], 'issues.meter_id=m.id', []);
        }
        if (in_array('issueType_id', array_keys($fields))) {
            $select->join(['i'=>'issue_issueTypes'], 'issues.id=i.issue_id', []);
        }
    }
}
