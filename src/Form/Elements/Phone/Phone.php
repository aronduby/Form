<?php

namespace Form\Elements;

class Phone extends Input{

	public $class_type = 'phone';
	public $types = [];
	public $placeholder = [
		'areacode' => "",
		'prefix' => "",
		'linenumber' => "",
		'extension' => ""
	];
	public $value = [
		'digits' => null,
		'areacode' => null,
		'prefix' => null,
		'linenumber' => null,
		'extension' => null
	];

	public $template = 'phone.inc';

	public $additional_js = ['form.phone.js'];
	public $additional_css = ['form.phone.css'];

	static private $regex = "/(?<areacode>\d{3})(?<prefix>\d{3})(?<linenumber>\d{4})(?<extension>\d+)?/";

	public function __construct($opts, $form=null){
		parent::__construct($opts, $form);

		if(isset($this->value) && is_string($this->value)){
			preg_match(self::$regex, $this->value, $this->value);
		} elseif( isset($this->value['digits']) ){
			preg_match(self::$regex, $this->value['digits'], $tmp);
			$this->value = array_merge($this->value, $tmp);
		}
	}

	static public function format($digits){
		if(preg_match(self::$regex, $digits, $matches) === 1){
			return '('.$matches['areacode'].') '.$matches['prefix'].'-'.$matches['linenumber'].(isset($matches['extension']) ? ' ext.'.$matches['extension'] : '');
		} else {
			return $digits;
		}
	}
	

	public function process(){
		if(isset($_REQUEST[$this->name]) && is_array($_REQUEST[$this->name])){
			$this->value = array_merge($this->value, $_REQUEST[$this->name]);
			
			// can't include the extension in the regex check since it throws off the number count
			$required_parts = $this->value['areacode'].$this->value['prefix'].$this->value['linenumber'];
			$this->value['digits'] = $required_parts.$this->value['extension'];
			$this->value['formatted'] = $this->format($this->value['digits']);

			// check it against the regex
			if(!preg_match(self::$regex, $required_parts)){
				$this->error = true;
				$this->error_msg = 'Phone number is not formatted correctly';
				return false;
			}
			
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
