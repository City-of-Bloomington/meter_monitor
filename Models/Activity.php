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

class Activity extends ActiveRecord
{
    protected $tablename = 'activity';
    protected $meter;

    private $issueTypes = [];

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
                $sql = 'select * from activity where id=?';

                $result = $zend_db->createStatement($sql)->execute([$id]);
                if (count($result)) {
                    $this->exchangeArray($result->current());
                }
                else {
                    throw new \Exception('activity/unknownActivity');
                }
            }
        }
        else {
            // This is where the code goes to generate a new, empty instance.
            // Set any default values for properties that need it here
            $this->setReportedDate('now');
        }
    }

    public function validate()
    {
        if (!$this->getMeter_id()) { throw new \Exception('missingRequiredFields'); }
    }

    public function save()
    {
        parent::save();
        $this->saveIssueTypes();
    }

    //----------------------------------------------------------------
    // Generic Getters & Setters
    //----------------------------------------------------------------
    public function getId()           { return parent::get('id');          }
    public function getComments()     { return parent::get('comments');    }
    public function getMeter_id()     { return parent::get('meter_id');    }
    public function getMeter()        { return parent::getForeignKeyObject(__namespace__.'\Meter', 'meter_id'); }
    public function getReportedDate($f=null, $tz=null) { return parent::getDateData('reportedDate', $f, $tz); }
    public function getResolvedDate($f=null, $tz=null) { return parent::getDateData('resolvedDate', $f, $tz); }

    public function setComments($s) { parent::set('comments', $s); }
    public function setMeter_id($i) { parent::setForeignKeyField (__namespace__.'\Meter', 'meter_id', $i); }
    public function setMeter   ($o) { parent::setForeignKeyObject(__namespace__.'\Meter', 'meter_id', $o); }
    public function setReportedDate($d) { parent::setDateData('reportedDate', $d); }
    public function setResolvedDate($d) { parent::setDateData('resolvedDate', $d); }

    /**
     * @param array $post
     */
    public function handleUpdate($post)
    {
        $fields = ['meter_id', 'comments', 'reportedDate', 'resolvedDate', 'issueTypes'];
        foreach ($fields as $f) {
            $set = 'set'.ucfirst($f);
            $this->$set($post[$f]);
        }
    }

    //----------------------------------------------------------------
    // Custom Functions
    //----------------------------------------------------------------
    public function getZone()
    {
        $meter = $this->getMeter();
        if ($meter) { return $meter->getZone(); }
    }

    public function getIssueTypes() {
        if (!$this->issueTypes && $this->getId()) {
            $table = new IssueTypesTable();
            $list = $table->find(['activity_id'=>$this->getId()]);
            foreach ($list as $type) {
                $this->issueTypes[$type->getId()] = $type;
            }
        }
        return $this->issueTypes;
    }

    /**
     * @param array $ids An array of issueType_ids to set
     */
    public function setIssueTypes($ids=null) {
        $this->issueTypes = [];
        foreach ($ids as $id) {
            try {
                $type = new IssueType($id);
                $this->issueTypes[$type->getId()] = $type;
            }
            catch (\Exception $e) {
                // Just ignore any invalid issueTypes
            }
        }
    }

    public function hasIssueType(IssueType $type)
    {
        return in_array($type->getId(), array_keys($this->getIssueTypes()));
    }

    public function saveIssueTypes()
    {
        if ($this->getId()) {
            $zend_db = Database::getConnection();

            $query = $zend_db->createStatement('delete from activity_issueTypes where activity_id=?');
            $query->execute([$this->getId()]);

            $query = $zend_db->createStatement('insert activity_issueTypes set activity_id=?,issueType_id=?');
            foreach ($this->issueTypes as $type) {
                $query->execute([$this->getId(),$type->getId()]);
            }
        }
    }
}
