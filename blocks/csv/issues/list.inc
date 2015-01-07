<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->issues
 * @param Meter $this->meter (optional)
 */
header('Content-Disposition: attachment; filename="issues.csv"');

echo "Issue ID,Meter ID,Meter,Zone,Issue Type,Date Reported,Reported By\n";

foreach ($this->issues as $i) {
    $m = $i->getMeter();
    $p = $i->getReportedByPerson();

    $reportedBy = $p ? $p->getFullname() : '';

    echo "{$i->getId()},{$m->getId()},$m,{$m->getZone()},{$i->getIssueType()},";
    echo "{$i->getReportedDate(DATE_FORMAT)},$reportedBy";
    echo "\n";
}
