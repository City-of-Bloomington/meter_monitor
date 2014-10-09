<?php
use Application\Models\Person;
?>
<nav>
<?php
    $a = '<a href="%s">%s</a>';

    $routes = [
        'activity'   => 'activity',
        'issueTypes' => 'issueType',
        'people'     => 'person',
        'users'      => 'user'
    ];
    foreach ($routes as $plural=>$singular) {
        if (Person::isAllowed($plural, 'index')) {
            $label = $plural == 'activity'
                ? $this->_($plural)
                : $this->_([$singular, $plural, 2]);
            echo sprintf($a, BASE_URI.'/'.$plural, $label);
        }
    }
?>
</nav>
