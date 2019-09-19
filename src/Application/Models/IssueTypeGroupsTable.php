<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class IssueTypeGroupsTable extends TableGateway
{
    protected $columns = ['id', 'name'];

    public function __construct() { parent::__construct('issueTypeGroups', __namespace__.'\IssueTypeGroup'); }
}
