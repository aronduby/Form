<?php

namespace Form\Elements;

class Button extends Input{

	public $class_type = 'button';
	public $ignore = true;
	public $additional_css = 'form.button.css';

	protected $template = 'button.inc';

}
?>
