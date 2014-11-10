<?php

namespace Form\Elements;

class DateTime extends Text{
	
	public $class_type = 'datetime';
	public $type = 'datetime';
	// php date format for displaying, actual value is saved as a timestamp
	public $date_format = 'm/d/y';
	public $time_format = 'g:i a';
	public $placeholders = [
		'date' => 'date',
		'time' => 'time'
	];

	protected $template = 'datetime.inc';

	public function output($format = 'html'){

		if(isset($this->value))
			$this->value = $this->value->format($this->date_format.' '.$this->time_format);

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
				$this->error_msg = 'Sorry, but we were unable to parse your entry as a date. Please check your entry and try again';
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
