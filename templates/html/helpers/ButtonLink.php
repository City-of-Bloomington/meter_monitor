<?php
/**
 * Provides markup for button links
 *
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Templates\Helpers;

use Blossom\Classes\Helper;

class ButtonLink extends Helper
{
	const SIZE_BUTTON = 'button';
	const SIZE_ICON   = 'icon';

	public static $types = [
		'add'    => 'fa fa-plus',
		'edit'   => 'fa fa-pencil',
		'delete' => 'fa fa-times',
		'cancel' => 'fa fa-times',
		'print'  => 'fa fa-print',
		'download' => 'fa fa-download'
	];

	public function buttonLink($url, $label, $type, $size=self::SIZE_BUTTON)
	{
		$a = $size == self::SIZE_BUTTON
			? '<a href="%s" class="btn"><i class="%s"></i> %s</a>'
			: '<a href="%s" class="%s" ><i class="hidden-label">%s</i></a>';
		$class = array_key_exists($type, self::$types) ? self::$types[$type] : $type;
		return sprintf($a, $url, $class, $label);
	}
}
