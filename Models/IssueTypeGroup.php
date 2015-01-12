<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;
use Blossom\Classes\ActiveRecord;
use Blossom\Classes\Database;

class IssueTypeGroup extends ActiveRecord
{
    protected $tablename = 'issueTypeGroups';

    /**
     * Populates the object with data
     *
     * Passing in an associative array of data will populate this object without
     * hitting the database.
     *
     * Passing in a scalar will load the data from the database.
     * This will load all fields in the table as properties of this class.
     * You may want to replace this with, or add your own extra, custom loading
     *
     * @param int|string|array $id (ID, email, username)
     */
    public function __construct($id=null)
    {
        if ($id) {
            if (is_array($id)) {
                $this->exchangeArray($id);
            }
            else {
                $zend_db = Database::getConnection();
                if (ActiveRecord::isId($id)) {
                    $sql = 'select * from issueTypeGroups where id=?';
                }
                else {
                    $sql = 'select * from issueTypeGroups where name=?';
                }
                $result = $zend_db->createStatement($sql)->execute([$id]);
                if (count($result)) {
                    $this->exchangeArray($result->current());
                }
                else {
                    throw new \Exception('issueTypes/unknownGroup');
                }
            }
        }
        else {
            // This is where the code goes to generate a new, empty instance.
            // Set any default values for properties that need it here
        }
    }

    public function validate()
    {
        if (!$this->getName()) { throw new \Exception('missingRequiredFields'); }
    }

    public function save() { parent::save(); }

    //----------------------------------------------------------------
    // Generic Getters & Setters
    //----------------------------------------------------------------
    public function getId()   { return parent::get('id');   }
    public function getName() { return parent::get('name'); }

    public function setName($s) { parent::set('name', $s); }

    public function handleUpdate($post)
    {
        $this->setName($post['name']);
    }

    //----------------------------------------------------------------
    // Custom Functions
    //----------------------------------------------------------------
    public function __toString() { return parent::get('name'); }

    /**
     * @return array
     */
    public function getIssueTypeStats()
    {
        $sql = "select t.id, t.name, count(i.id) as count
                from issueTypes t
                left join issues i on t.id=i.issueType_id
                where t.issueTypeGroup_id=?
                group by t.id, t.name";
        $zend_db = Database::getConnection();
        $result = $zend_db->query($sql)->execute([$this->getId()]);
        return $result;
    }
}