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
        if (!$this->getMeter()) { throw new \Exception('missingRequiredFields'); }
    }

    public function save() { parent::save(); }

    //----------------------------------------------------------------
    // Generic Getters & Setters
    //----------------------------------------------------------------
    public function getId()           { return parent::get('id');          }
    public function getZone()         { return parent::get('zone');        }
    public function getMeter()        { return parent::get('meter');       }
    public function getComments()     { return parent::get('comments');    }
    public function getReportedDate($f=null, $tz=null) { return parent::getDateData('reportedDate', $f, $tz); }
    public function getResolvedDate($f=null, $tz=null) { return parent::getDateData('resolvedDate', $f, $tz); }

    public function setZone    ($s) { parent::set('zone',(int)$s); }
    public function setMeter   ($s) { parent::set('meter',    $s); }
    public function setComments($s) { parent::set('comments', $s); }
    public function setReportedDate($d) { parent::setDateData('reportedDate', $d); }
    public function setResolvedDate($d) { parent::setDateData('resolvedDate', $d); }

    /**
     * @param array $post
     */
    public function handleUpdate($post)
    {
        $fields = ['zone', 'meter', 'comments', 'reportedDate', 'resolvedDate'];
        foreach ($fields as $f) {
            $set = 'set'.ucfirst($f);
            $this->$set($post[$f]);
        }
    }

    //----------------------------------------------------------------
    // Custom Functions
    //----------------------------------------------------------------
}
