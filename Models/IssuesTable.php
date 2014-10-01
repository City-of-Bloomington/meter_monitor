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
    protected $columns = ['id', 'zone', 'meter', 'issueType_id'];
    
    public function __construct() { parent::__construct('issues', __namespace__.'\Issue'); }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function find($fields=null, $order='reportedDate desc', $paginated=false, $limit=null)
    {
        return parent::find($select, $order, $paginated, $limit);
    }
}
