<?php

namespace Form\Elements;

class Name extends Input{

	public $class_name = 'name';
	public $placeholder = [
		'first' => "",
		'last' => ""
	];

	protected $template = 'name.inc';

	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && is_array($_REQUEST[$this->name])){
			$this->value = $_REQUEST[$this->name];

			if(!strlen($this->value['first']) || !strlen($this->value['last'])){
				// check for required
				if($this->required){
					$this->error = true;
					$this->error_msg = 'You must supply both a first and last name';
					return false;
				
				// not required, doesn't matter
				} else {
					return true;
				}
			}

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
