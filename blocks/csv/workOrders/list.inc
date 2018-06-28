<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->workOrders
 * @param Meter $this->meter (optional)
 */
header('Content-Disposition: attachment; filename="workOrders.csv"');

echo "Work ID,Meter ID,Meter,Zone,Date Completed,Completed By,Issue ID,Issue Type,Date Reported\n";
foreach ($this->workOrders as $w) {
    $m = $w->getMeter();
    $issues = $w->getIssues();
    $person = $w->getCompletedByPerson();

    $completedBy = $person ? $person->getFullname() : '';

    $workInfo = "{$w->getId()},{$m->getId()},{$m->getName()},{$m->getZone()},{$w->getDateCompleted(DATE_FORMAT)},$completedBy";


    if (count($issues)) {
        foreach ($issues as $i) {
            echo $workInfo.",{$i->getId()},{$i->getIssueType()},{$i->getReportedDate(DATE_FORMAT)}\n";
        }
    }
    else {
        echo $workInfo.",,,\n";
    }
}
