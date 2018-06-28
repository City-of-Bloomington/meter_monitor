<?php
/**
 * @copyright 2014-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Zend\Db\Result $this->issues
 * @param Meter          $this->meter (optional)
 */
header('Content-Disposition: attachment; filename="issues.csv"');

echo "Issue ID,Meter ID,Meter,Zone,Issue Type,Date Reported,Reported By\n";

$out = fopen('php://output', 'w');
foreach ($this->issues as $i) {
    $m = $i->getMeter();
    $p = $i->getReportedByPerson();

    $reportedBy = $p ? $p->getFullname() : '';

    $row = [
        $i->getId(),
        $m->getId(),
        $m->getName(),
        $m->getZone(),
        $i->getIssueType(),
        $i->getReportedDate(DATE_FORMAT),
        $reportedBy
    ];
    fputcsv($out, $row);
}
