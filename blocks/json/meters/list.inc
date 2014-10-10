<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->meters
 */
$meters = [];

foreach ($this->meters as $m) {
    $meters[] = [
        'id'   => $m->getId(),
        'name' => $m->getName(),
        'zone' => $m->getZone()
    ];
}
echo json_encode($meters);
