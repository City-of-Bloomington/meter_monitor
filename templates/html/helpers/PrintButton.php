<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Templates\Helpers;

use Blossom\Classes\Template;
use Blossom\Classes\Url;

class PrintButton
{
    private $template;

    public function __construct(Template $template)
    {
        $this->template = $template;
    }

    public function printButton()
    {
        $printUrl = new Url(Url::current_url());
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
