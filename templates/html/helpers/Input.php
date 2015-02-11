<?php
/**
* Provides markup for basic inputs
*
* @copyright 2014-2015 City of Bloomington, Indiana
* @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
* @author Dan Hiester <hiesterd@bloomington.in.gov>
*/
namespace Application\Templates\Helpers;

use Blossom\Classes\Helper;

class Input extends Helper
{
    public function text($id, $label, $value = '', $type = 'text', $required = false, $inputAttributesArray = [])
    {
        $extraAttributes = '';
        $required = $required === false ? '' : '<abbr title="Required field" class="text-required">*</abbr> ';
        foreach ($inputAttributesArray as $attribute => $attrValue)
        {
            $extraAttributes .= "$attribute=\"$attrValue\" ";
        }
        echo <<<EOT
        <dl class="input-field">
            <dt><label for="$id">$required$label</label></dt>
            <dd><input id="$id" name="$id" value="$value" type="$type" $extraAttributes/></dd>
        </dl>

EOT;
    }

    public function checkbox($groupLabel, $items = []) {
        foreach ($items as $item) {
            $checked = $item['checked'] ? 'checked="checked"' : '';
            $dds .= "<dd><label><input type=\"checkbox\" value=\"{$item['value']}\" $checked><span>{$item['label']}</label>";
        }
        echo <<<EOT
        <dl class="input-field mod-checkbox">
            <dt>$groupLabel</dt>
            $dds
        </dl>

EOT;
    }
}
