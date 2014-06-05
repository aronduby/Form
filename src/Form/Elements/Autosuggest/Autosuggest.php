<?php

namespace Form\Elements;

class Autosuggest extends Input{

	protected $template = 'autosuggest.inc';
	
	public $class_type = 'autosuggest';
	public $options = array();
	public $additional_js = ['jquery.autoSuggest.js','form.autosuggest.js'];
	public $additional_css = 'form.autosuggest.css';

	protected $formatted_options = array();
	protected $formatted_value = array();


	public function __construct($opts, $form=null){
		parent::__construct($opts, $form);

		$this->formatForOutput();
		
	}

	public function process(){
		// if a value is supplied, take it
		if(strlen($_REQUEST['as_values_'.$this->name.'_values'])>0){
			
			// trim and explore the value from the request
			$this->value = array();
			foreach( explode(',',trim($_REQUEST['as_values_'.$this->name.'_values'],', \t\n\r\0\x0B')) as $val )
				$this->value[] = $val;

			$this->formatForOutput();
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


	protected function formatForOutput(){
		// setup formatted options and values as arrays that autosuggest js plugin understands
		$this->formatted_options = array();
		foreach($this->options as $value=>$label)
			$this->formatted_options[] = array('value'=>$value, 'label'=>$label);
		
		$this->formatted_value = array();
		if(is_array($this->value) && count($this->value)>0){
			foreach($this->value as $v){
				if(array_key_exists($v, $this->options))
					$this->formatted_value[] = array('value'=>$v, 'label'=>$this->options[$v]);
				else
					$this->formatted_value[] = array('value'=>null, 'label'=>$v);
			}
		}
	}

}
?>
