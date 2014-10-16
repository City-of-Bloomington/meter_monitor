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

class Meter extends ActiveRecord
{
    protected $tablename = 'meters';

    private $issues = [];

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
                $sql = ActiveRecord::isId($id)
                    ? 'select * from meters where id=?'
                    : 'select * from meters where name=?';

                $result = $zend_db->createStatement($sql)->execute([$id]);
                if (count($result)) {
                    $this->exchangeArray($result->current());
                }
                else {
                    throw new \Exception('meters/unknownMeter');
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
        if (!$this->getName() || !$this->getZone()) {
            throw new \Exception('missingRequiredFields');
        }
    }

    public function save() { parent::save(); }

    //----------------------------------------------------------------
    // Generic Getters & Setters
    //----------------------------------------------------------------
    public function getId()   { return parent::get('id');   }
    public function getName() { return parent::get('name'); }
    public function getZone() { return parent::get('zone'); }

    public function setName($s) { parent::set('name',      $s); }
    public function setZone($i) { parent::set('zone', (int)$i); }

    public function handleUpdate($post)
    {
        $this->setName($post['name']);
        $this->setZone($post['zone']);
    }

    //----------------------------------------------------------------
    // Custom Functions
    //----------------------------------------------------------------
    public function __toString() { return parent::get('name'); }

    public function getUrl() { return BASE_URL.'/meters/view?meter_id='.$this->getId(); }
    public function getUri() { return BASE_URI.'/meters/view?meter_id='.$this->getId(); }

    /**
     * Returns the array of distinct field values for Meter records
     *
     * This is primarily used to populate autocomplete lists for search forms
     * Make sure to keep this function as fast as possible
     *
     * @param string $fieldname
     * @return array
     */
    public static function getDistinct($fieldname)
    {
        $fieldname = trim($fieldname);
        $zend_db = Database::getConnection();

        $validFields = array('zone');
        if (in_array($fieldname, $validFields)) {
            $sql = "select distinct $fieldname from meters";
        }
        $result = $zend_db->createStatement($sql)->execute();
        $o = [];
        foreach ($result as $row) { $o[] = $row[$fieldname]; }
        return $o;
    }

    public function getIssues()
    {
        if ($this->getId() && !$this->issues) {
            $table = new IssuesTable();
            $list = $table->find(['meter_id'=>$this->getId()]);
            foreach ($list as $i) {
                $this->issues[] = $i;
            }
        }
        return $this->issues;
    }

    public function getWorkOrders()
    {
        $table = new WorkOrdersTable();
        return $table->find(['meter_id'=>$this->getId()]);
    }

    public function hasOpenIssue()
    {
        foreach ($this->getIssues() as $i) {
            if ($i->getStatus() == Issue::STATUS_OPEN) { return true; }
        }
        return false;
    }
}
