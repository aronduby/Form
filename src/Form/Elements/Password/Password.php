<?php

namespace Form\Elements;

class Password extends Text{
	
	public $class_type = 'password';
	public $type = 'password';
	public $confirm = false;
	public $confirm_value;
	public $confirm_placeholder;

	protected $template = 'password.inc';

	public function process(){
		
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && strlen($_REQUEST[$this->name])>0){
			$this->value = $_REQUEST[$this->name];

			if($this->confirm == true){
				if(isset($_REQUEST[$this->name.'_confirm']) && strlen($_REQUEST[$this->name.'_confirm'])>0){
					$this->confirm_value = $_REQUEST[$this->name.'_confirm'];

					if($this->value == $this->confirm_value){
						return true;
					} else {
						// confirmation does not match
						$this->error = true;
						$this->error_msg = 'The confirmation does not match.';
						$this->value='';
						$this->confirm_value='';
						return false;
					}
				} else {
					// no confirmation sent
					$this->error = true;
					$this->error_msg = 'You must confirm the value you supplied.';
					$this->value='';
					$this->confirm_value='';
					return false;
				}

			} else {
				return true;
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
