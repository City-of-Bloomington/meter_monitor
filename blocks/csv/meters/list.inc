<?php
/**
 * @copyright 2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Zend\Db\Result $this->meters
 */
declare (strict_types=1);
header('Content-Disposition: attachment; filename="meters.csv"');

echo "Meter ID,Meter,Zone\n";

$out = fopen('php://output', 'w');
foreach ($this->meters as $m) {
    $row = [
        $m->getId(),
        $m->getName(),
        $m->getZone()
    ];
    fputcsv($out, $row);
}
