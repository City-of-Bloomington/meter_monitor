<?php
/**
 * @copyright 2014-2017 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Templates\Helpers;

use Blossom\Classes\Helper;
use Blossom\Classes\Url;

class PrintButton extends Helper
{
    public function printButton()
    {
        $printUrl = new Url(Url::current_url(BASE_HOST));
        $printUrl->print = 1;
        if (isset($printUrl->page)) { unset($printUrl->page); }

        $helper = $this->template->getHelper('buttonLink');
        echo $helper->buttonLink(
            $printUrl,
            $this->template->_('print'),
            'print'
        );
    }
}
