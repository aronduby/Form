<?php

namespace Form\Elements;

class SelectOtherTypeahead extends Input{

	public $class_type = 'selectothertypeahead';
	protected $template = 'selectothertypeahead.inc';
	protected $value_is_public;
	
	public $additional_js = ['typeahead.min.js', 'form.selectothertypeahead.js'];
	public $additional_css = ['form.selectothertypeahead.css'];

	public $select_placeholder;
	public $typeahead_placeholder;

	public $value = [
		'id' => null,
		'string' => null
	];
	
	/*
	 *	Check out https://github.com/twitter/typeahead.js for format of datasets
	*/
	public $options = array();
	
	// add options, val, text
	public function addOption($obj){
		$this->options[] = $val;
		return $this;
	}

	public function output($format = 'html'){
		if(isset($this->value['id']))
			$value_is_public = $this->options[$this->value['id']]->public;
		else
			$value_is_public = false;

		return parent::output($format);
	}


	public function process(){

		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && count($_REQUEST[$this->name])>0){
			$this->value = $_REQUEST[$this->name];
			return true;

		} else {
			
			// check for required
			if($this->required){
				$this->error = true;
				$this->error_msg = 'This is a required field';
				return false;
			
			// not required, doesn't matter
			} else {
				return true;
			}
		}		
	}


}
?>
