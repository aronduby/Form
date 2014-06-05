<?php

namespace Form\Elements;

class Select extends Input{

	public $class_type = 'select';
	protected $template = 'select.inc';
	
	public $additional_js = ['form.select.js'];
	public $options = array();
	
	// add options, val, text
	public function addOption($val, $text){
		if(is_object($val)){
			$this->options[] = $val;
		} else {
			$this->options[$val] = $text;
		}

		return $this;
	}


}
?>
