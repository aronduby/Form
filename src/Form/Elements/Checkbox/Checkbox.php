<?php

namespace Form\Elements;

class Checkbox extends Select{

	protected $template = 'checkbox.inc';

	public $class_type= 'checkbox';
	public $inline = false;
	
	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && is_array($_REQUEST[$this->name])){
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
