<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class MetersTable extends TableGateway
{
    protected $columns = ['id', 'name', 'zone'];

    public function __construct() { parent::__construct('meters', __namespace__.'\Meter'); }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function find($fields=null, $order='name', $paginated=false, $limit=null)
    {
        return parent::find($fields, $order, $paginated, $limit);
    }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function search($fields=null, $order='name', $paginated=false, $limit=null)
    {
        $select = new Select('meters');
        if (count($fields)) {
            foreach ($fields as $key=>$value) {
                if (!empty($value)) {
                    switch ($key) {
                        case 'name':
                            $select->where->like($key, "$value%");
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
