<?php

namespace Form\Elements;

class TimeSelect extends Input {

	public $class_type = 'timeselect';
	public $hours;
	public $minutes;
	public $ampm;
	
	public $placeholder = [
		'hours' => "Hour",
		'minutes' => "Minutes",
		'ampm' => "AM/PM"
	];

	protected $template = 'timeselect.inc';

	public function __construct($opts, $form=null){
		
		parent::__construct($opts, $form);

		// hours
		if(!isset($this->hours)){
			foreach(range(1,12) as $h)
				$this->hours[$h] = $h;
		}

		// minutes
		if(!isset($this->minutes)){
			$this->minutes = range(00,60);
		}

		// am/pm
		$this->ampm = ['AM', 'PM'];

		return $this;
	}

	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && count($_REQUEST[$this->name])){
			$vals = $_REQUEST[$this->name];
			$missing_fields = [];
			
			if($vals['hours']==0)
				$missing_fields[] = 'Hour';
			if($vals['minutes']==0)
				$missing_fields[] = 'Minutes';
			if(($vals['ampm'])==0)
				$missing_fields[] = 'AM/PM';

			if(count($missing_fields) && $this->required){
				$this->error = true;
				$this->error_msg = 'You must choose a '.implode(', ', $missing_fields);
				return false;
			} else {
				try{
					if(array_sum($vals)==0 && !$this->required){
						$this->value = null;
					} else {
						$this->value = new \DateTime($vals['hours'].'-'.$vals['minutes'].'-'.$vals['ampm']);
					}
					return true;
				} catch(Exception $e){
					$this->error = true;
					$this->error_msg = $e->getMessage();
					return false;
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
