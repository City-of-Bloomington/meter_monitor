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

class Issue extends ActiveRecord
{
    protected $tablename = 'issues';
    protected $meter;
    protected $issueType;

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
                $sql = 'select * from issues where id=?';

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
            $this->setReportedDate('now');
        }
    }

    public function validate()
    {
        if (!$this->getMeter_id()) { throw new \Exception('missingRequiredFields'); }
    }

    public function save  () { parent::save  (); }
    public function delete() { parent::delete(); }

    //----------------------------------------------------------------
    // Generic Getters & Setters
    //----------------------------------------------------------------
    public function getId()           { return parent::get('id');           }
    public function getComments()     { return parent::get('comments');     }
    public function getMeter_id()     { return parent::get('meter_id');     }
    public function getIssueType_id() { return parent::get('issueType_id'); }
    public function getMeter()     { return parent::getForeignKeyObject(__namespace__.'\Meter',     'meter_id'); }
    public function getIssueType() { return parent::getForeignKeyObject(__namespace__.'\IssueType', 'issueType_id'); }
    public function getReportedDate($f=null, $tz=null) { return parent::getDateData('reportedDate', $f, $tz); }
    public function getResolvedDate($f=null, $tz=null) { return parent::getDateData('resolvedDate', $f, $tz); }

    public function setComments($s) { parent::set('comments', $s); }
    public function setMeter_id($i) { parent::setForeignKeyField (__namespace__.'\Meter', 'meter_id', $i); }
    public function setMeter   ($o) { parent::setForeignKeyObject(__namespace__.'\Meter', 'meter_id', $o); }
    public function setIssueType_id($i) { parent::setForeignKeyField (__namespace__.'\IssueType', 'issueType_id', $i); }
    public function setIssueType   ($o) { parent::setForeignKeyObject(__namespace__.'\IssueType', 'issueType_id', $o); }
    public function setReportedDate($d) { parent::setDateData('reportedDate', $d); }
    public function setResolvedDate($d) { parent::setDateData('resolvedDate', $d); }

    /**
     * @param array $post
     */
    public function handleUpdate($post)
    {
        $fields = ['meter_id', 'comments', 'reportedDate', 'resolvedDate', 'issueType_id'];
        foreach ($fields as $f) {
            if (isset($post[$f])) {
                $set = 'set'.ucfirst($f);
                $this->$set($post[$f]);
            }
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
}
