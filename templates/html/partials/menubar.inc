<?php
use Application\Models\Person;
?>
<nav>
<?php
    $a = '<a href="%s">%s</a>';

    $routes = [
        'issues'     => 'issue',
        'issueTypes' => 'issueType',
        'people'     => 'person',
        'users'      => 'user'
    ];
    foreach ($routes as $plural=>$singular) {
        if (Person::isAllowed($plural, 'index')) {
            echo sprintf($a, BASE_URI.'/'.$plural, $this->_([$singular, $plural, 2]));
        }
    }
?>
</nav>
