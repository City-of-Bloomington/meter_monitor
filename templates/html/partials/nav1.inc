<?php
use Application\Models\Person;
?>
<div class="nav1">
    <nav class="container">
    <?php
        $a = '<a href="%s" class="nav1-link">%s</a>';

        $routes = [
            'meters'     => 'meter',
            'issues'     => 'issue',
            'workOrders' => 'workOrder',
            'issueTypes' => 'issueType',
            'workTypes'  => 'workType'
        ];
        foreach ($routes as $plural=>$singular) {
            $requiredAction = ($plural=='workTypes')
                ? 'update'
                : 'index';
            if (Person::isAllowed($plural, $requiredAction)) {
                echo sprintf($a, BASE_URI.'/'.$plural, $this->_([$singular, $plural, 2]));
            }
        }
    ?>
    </nav>
</div>
