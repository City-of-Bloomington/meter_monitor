<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;
use Blossom\Classes\ActiveRecord;
use Blossom\Classes\Database;
use Blossom\Classes\ExternalIdentity;

class WorkOrder extends ActiveRecord
{
    protected $tablename = 'workOrders';
    protected $meter;
    protected $completedByPerson;

    private $workTypes = [];
    private $issues    = [];

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
                $sql = 'select * from workOrders where id=?';

                $result = $zend_db->createStatement($sql)->execute([$id]);
                if (count($result)) {
                    $this->exchangeArray($result->current());
                }
                else {
                    throw new \Exception('issues/unknownIssue');
                }
            }
        }
        else {
            // This is where the code goes to generate a new, empty instance.
            // Set any default values for properties that need it here
            $this->setDateCompleted('now');
        }
    }

    public function validate()
    {
        if (!$this->getMeter_id()) {
            throw new \Exception('missingRequiredFields');
        }
    }

    public function save()
    {
        parent::save();
        $this->saveWorkTypes();
        $this->saveIssues();
    }

    public function delete()
    {
        $this->deleteWorkTypes();
        $this->deleteIssues();
        parent::delete();
    }


    //----------------------------------------------------------------
    // Generic Getters & Setters
    //----------------------------------------------------------------
    public function getId()                   { return parent::get('id');       }
    public function getComments()             { return parent::get('comments'); }
    public function getMeter_id()             { return parent::get('meter_id'); }
    public function getCompletedByPerson_id() { return parent::get('completedByPerson_id'); }
    public function getMeter()             { return parent::getForeignKeyObject(__namespace__.'\Meter',  'meter_id'); }
    public function getCompletedByPerson() { return parent::getForeignKeyObject(__namespace__.'\Person', 'completedByPerson_id'); }
    public function getDateCompleted($f=null, $tz=null) { return parent::getDateData('dateCompleted', $f, $tz); }
    public function getReportedDate ($f=null, $tz=null) { return parent::getDateData('reportedDate',  $f, $tz); }

    public function setComments($s) { parent::set('comments', $s); }
    public function setMeter_id($i) { parent::setForeignKeyField (__namespace__.'\Meter', 'meter_id', $i); }
    public function setMeter   ($o) { parent::setForeignKeyObject(__namespace__.'\Meter', 'meter_id', $o); }
    public function setDateCompleted($d) { parent::setDateData('dateCompleted', $d); }
    public function setCompletedByPerson_id($i) { parent::setForeignKeyField (__namespace__.'\Person', 'completedByPerson_id', $i); }
    public function setCompletedByPerson   ($o) { parent::setForeignKeyObject(__namespace__.'\Person', 'completedByPerson_id', $o); }

    /**
     * @param array $post
     */
    public function handleUpdate($post)
    {
        $fields = ['meter_id', 'dateCompleted', 'completedByPerson_id', 'comments', 'workTypes', 'issues'];
        foreach ($fields as $f) {
            $set = 'set'.ucfirst($f);
            $this->$set($post[$f]);
        }
    }

    //----------------------------------------------------------------
    // Custom Functions
    //----------------------------------------------------------------
    /**
     * @return array An array of types with the typeId as the key
     */
    public function getWorkTypes()
    {
        if ($this->getId() && !count($this->workTypes)) {
            $table = new WorkTypesTable();
            $list = $table->find(['workOrder_id'=>$this->getId()]);
            foreach ($list as $type) {
                $this->workTypes[$type->getId()] = $type;
            }
        }
        return $this->workTypes;
    }

    /**
     * @return array
     */
    public function getIssues()
    {
        if ($this->getId() && !count($this->issues)) {
            $table = new IssuesTable();
            $list = $table->find(['workOrder_id'=>$this->getId()]);
            foreach ($list as $issue) {
                $this->issues[$issue->getId()] = $issue;
            }
        }
        return $this->issues;
    }

    /**
     * @param WorkType $type
     * @return boolean
     */
    public function hasWorkType(WorkType $type)
    {
        return in_array($type->getId(), array_keys($this->getWorkTypes()));
    }

    /**
     * @param Issue $issue
     * @return boolean
     */
    public function hasIssue(Issue $issue)
    {
        return in_array($issue->getId(), array_keys($this->getIssues()));
    }


    /**
     * @param array $ids An array of typeIds
     */
    public function setWorkTypes(array $ids)
    {
        $this->workTypes = [];
        foreach ($ids as $id) {
            try {
                $type = new WorkType($id);
                $this->workTypes[$type->getId()] = $type;
            }
            catch (\Exception $e) {
                // Just ignore any invalid types
            }
        }
    }

    public function setIssues(array $ids)
    {
        $this->issues = [];
        foreach ($ids as $id) {
            try {
                $issue = new Issue($id);
                $this->issues[$issue->getId()] = $issue;
            }
            catch (\Exception $e) {
                // Just ignore any invalid issues
            }
        }
    }

    public function deleteWorkTypes()
    {
        $zend_db = Database::getConnection();
        $query = $zend_db->createStatement('delete from workOrder_workTypes where workOrder_id=?');
        $query->execute([$this->getId()]);
    }

    public function deleteIssues()
    {
        if ($this->getId()) {
            $zend_db = Database::getConnection();
            $query = $zend_db->createStatement('update issues set workOrder_id=null where workOrder_id=?');
            $query->execute([$this->getId()]);
        }
    }

    public function saveWorkTypes()
    {
        if ($this->getId()) {
            $this->deleteWorkTypes();

            $zend_db = Database::getConnection();
            $query = $zend_db->createStatement('insert workOrder_workTypes set workOrder_id=?,workType_id=?');
            foreach ($this->workTypes as $id=>$o) {
                $query->execute([$this->getId(), $o->getId()]);
            }
        }
    }

    public function saveIssues()
    {
        if ($this->getId()) {
            $this->deleteIssues();

            $zend_db = Database::getConnection();
            $query = $zend_db->createStatement('update issues set workOrder_id=? where id=?');
            foreach ($this->issues as $id=>$o) {
                $query->execute([$this->getId(), $o->getId()]);
            }
        }
    }
}
