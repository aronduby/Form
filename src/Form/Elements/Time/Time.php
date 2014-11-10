<?php

namespace Form\Elements;

class Time extends Text{
	
	public $class_type = 'time';
	public $type = 'time';
	public $format = 'g:i'; // php date format for displaying, actual value is saved as a timestamp

	public function output($format = 'html'){

		if(isset($this->value))
			$this->value = $this->value->format($this->format);

		return parent::output($format);
	}


	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && strlen($_REQUEST[$this->name])){

			try{
				$this->value = new \DateTime(str_replace('-','/',$_REQUEST[$this->name]));
				return true;
			} catch(\Exception $e){
				$this->error = true;
				$this->error_msg = 'Sorry, but we were unable to parse your entry as a time. Please check your entry and try again';
				error_log($e->getMessage());
				return false;
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
