<?php

namespace Form\Elements;

abstract class Input{
	
	public $class_type = 'input'; 
	public $required = false;
	public $value;
	public $name;
	public $id;
	public $label;
	public $note;
	public $class;
	public $holder_class;
	public $description;
	public $ignore = false;
	public $object;
	public $placeholder;
	public $disabled = false;
	public $data = [];

	public $error = false;
	public $error_msg = '';

	public $additional_js = array();
	public $additional_css = array();

	public $template_path;

	protected $template;
	
	// default functions
	public function __construct($opts, $form=null){
		if(is_array($opts))
			$this->take($opts);

		$this->object = get_class($this);
		if(!isset($this->id))
			$this->id = $this->name;
		
		// default template path goes to CurrentDirectory/WhateverClassCreatedTheTemplateVariable/
		// note that this isn't always the current class due to extends
		// ex. Select declares the template file, StateSelect extends Select but only sets options
		// since StateSelect didn't declare it's own template variable the path will be to Select
		if(!isset($this->template_path)){
			$folder = new \ReflectionProperty(get_class($this), 'template');
			$folder = $folder->getDeclaringClass()->name;
			$this->template_path = dirname(__FILE__).str_replace([__NAMESPACE__,'\\'], ['','/'], $folder).'/';
		}

		return $this;
	}

	public function output($format = 'html'){
		if($format == 'html'){
			if(file_exists($this->template_path.$this->template)){
				ob_start();
				include $this->template_path.$this->template;
				return ob_get_clean();
			} else {
				throw new \Exception($this->template_path.$this->template.' template not found for '.get_class($this));
			}
		} elseif($format == 'json'){
			return json_encode( $this );
		}
	}

	public function process(){
		//print_p($this->name);

		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && strlen($_REQUEST[$this->name])>0){
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

	protected function outputDataProperties(){
		if(count($this->data)){
			$props = [];
			foreach($this->data as $k=>$v){
				$props[] = 'data-'.$k.'="'.$v.'"';
			}
			return implode(' ', $props);
		} else {
			return '';
		}
	}

	public function getValue(){
		return array($this->name => $this->value);
	}


	/**/
	public function dump(){
		return get_object_vars($this);
	}
	
	// loops through args and sets matching variables (that are public scope)
	// @args is an associative array
	public function take($args){
		
		$public = array();
		$reflect = new \ReflectionObject($this);
	    foreach ($reflect->getProperties(\ReflectionProperty::IS_PUBLIC) as $prop) {
			$public[] = $prop->getName();
		}		

		foreach($args as $k=>$v){
			if(in_array($k, $public)){
				$this->$k = $this->processValue($v);
			}
		}
	}

	private function processValue($val){
		if(is_array($val)){
			foreach($val as $k=>$v){
				$val[$k] = $this->processValue($v);
			}
		}elseif( is_numeric($val) && $val <= PHP_INT_MAX ) // dont convert if it will max out php's int
			$val = (int)$val;
		elseif( is_bool($val) )
			$val = (bool)$val;
		elseif( is_null($val) || $val == 'null' )
			$val = null;

		return $val;
	}

	#GET & SET FUNCTIONS
	public function __get($name){
		if(property_exists(get_class($this), $name))
			return $this->$name;
		else {
			$trace = debug_backtrace();
			throw new \Exception('Undefined property via __get(): '.$name.' in '.$trace[0]['file'].' on line '.$trace[0]['line']);
		}
	}

	public function __set($name, $value){
		if(property_exists(get_class($this), $name))
			return $this->$name = $value;
		else {
			$trace = debug_backtrace();
			throw new \Exception('Undefined property via __set(): '.$name.' in '.$trace[0]['file'].' on line '.$trace[0]['line']);
		}
	}
}
?>
