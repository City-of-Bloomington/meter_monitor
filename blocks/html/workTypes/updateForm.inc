<?php
/**
 * @copyright 2014-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param WorkType $this->workType
 */
$fields = ['id', 'name', 'description'];
foreach ($fields as $f) {
    $get = 'get'.ucfirst($f);
    $$f  = self::escape($this->workType->$get());
}

$title = $id ? $this->_('workType_edit') : $this->_('workType_add');
?>
<section>
    <header>
        <h1><?= $title; ?></h1>
    </header>
    <form method="post" action="<?= BASE_URI; ?>/workTypes/update">
        <fieldset><legend><?= $this->_('workType'); ?></legend>
            <input name="workType_id" type="hidden" value="<?= $id ?>" />

            <?php
                $f = $this->template->getHelper('field');
                echo $f->input([
                    'name'=>'name', 'id'=>'name', 'label'=>$this->_('name'), 'value'=>$name, 'required'=>true
                ]);
            ?>
            <div>
                <div><label for="description"><?= $this->_('description'); ?></label></div>
                <textarea name="description" id="description"><?= $description; ?></textarea>
            </div>

            <?php
                $h = $this->template->getHelper('saveAndCancelButtons');
                echo $h->saveAndCancelButtons(BASE_URI.'/workTypes');
            ?>
        </fieldset>
    </form>
</section>
