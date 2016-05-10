<?php
/**
 * @copyright 2014-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
$name = !empty($_GET['name']) ? self::escape($_GET['name']) : '';
$zone = !empty($_GET['zone']) ? self::escape($_GET['zone']) : '';
$inputHelper = $this->template->getHelper('field');
?>
<form method="get" action="<?= BASE_URI; ?>/meters">
    <fieldset>
        <legend><?= $this->_('search'); ?></legend>
        <?php
            echo $inputHelper->input([
                'name'=>'name', 'id'=>'name', 'label'=>$this->_('meter'), 'value'=>$name, 'attr'=>['class'=>'meterAutoComplete']
            ]);
        ?>
        <dl class="input-field"><dt><label for="zone"><?= $this->_('zone'); ?></label></dt>
            <dd><?php
                    $z = $this->template->getHelper('zoneSelector');
                    echo $z->zoneSelector($zone, 'zone');
                ?>
            </dd>
        </dl>

        <div class="input-buttons">
            <button type="submit"><i class="fa fa-search"></i> <?= $this->_('search'); ?></button>
            <a href="<?= BASE_URI; ?>/meters"><?= $this->_('clear'); ?></a>
        </div>
    </fieldset>
</form>
<?php
    $this->template->addToAsset('scripts', JQUERY.'/jquery.min.js');
    $this->template->addToAsset('scripts', JQUERY_UI.'/jquery-ui.min.js');
    $this->template->addToAsset('scripts', BASE_URI.'/js/meterAutoComplete.js');
    $this->template->addToAsset('stylesheets', JQUERY_UI.'/jquery-ui.min.css');
?>
