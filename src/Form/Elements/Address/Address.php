<?php

namespace Form\Elements;

class Address extends Input{
	
	public $class_type = 'address';
	public $counter = 0;
	public $required_fields = array('street', 'city', 'state', 'zip');
	public $placeholders = array(
		'street' => 'street address',
		'city' => 'city',
		'state' => 'state',
		'zip' => 'zipcode',
	);
	public $types = [];

	protected $template = 'address.inc';
	protected $error_flds = array();


	public function __construct($opts, $form=null){

		parent::__construct($opts, $form);
		
		//if($form != null)
		//	$this->counter = $form->element_counters[$this->id];
	}

	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && is_array($_REQUEST[$this->name])){
			$this->value = $_REQUEST[$this->name][$this->counter];
			
			// check the values for the required fields
			// first just make sure that they are supplied
			if($this->required && is_array($this->required_fields)){ foreach($this->required_fields as $fld){
				if(!isset($this->value[$fld]) || strlen($this->value[$fld])<=0)
					$this->error_flds[$fld] = 'You must supply a value for '.ucwords(str_replace('_','',$fld));
			}}

			// now specific fields
			// state
			$this->value['state'] = strtoupper($this->value['state']);
			if(strlen($this->value['state']) > 0 && strlen($this->value['state']) > 2)
				$this->error_flds['state'] = 'State field should be 2 characters long';			
			
			// finally submit any errors back to the form
			if(count($this->error_flds)){
				$this->error = true;
				if(count($this->error_flds)==1)
					$this->error_msg = '<label for="'.$this->name.'_'.$this->counter.'_'.implode('', array_keys($this->error_flds)).'">'.implode('',$this->error_flds).'</label>';
				else {
					$this->error_msg = 'You have '.count($this->error_flds).' errors with this address:<ul>';
					foreach($this->error_flds as $name=>$msg){
						$this->error_msg .= '<li><label for="'.$this->name.'_'.$name.'">'.$msg.'</label></li>';
					}
					$this->error_msg .= '</ul>';
				}

				return false;
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

	public function getValues(){

		return array( $this->name => array( $this->counter => $this->value ));

	}

}
?>
