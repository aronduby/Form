<?php

namespace Form;

function formAutoload($class){
	if(strpos($class, 'Form\\Elements') !== false){
		$parts = explode('\\', $class);
		$element = end($parts);
		$path = dirname(__FILE__).'/Elements/'.$element.'/'.$element.'.php';
		if(file_exists($path))
			include $path;
	}
}
spl_autoload_register('Form\\formAutoload');

// make sure we have a session for hash checking
$sid = session_id();
if($sid == '')
	session_start();

class Form{

	public $elements = array();
	public $processed = false;
	public $errors = false;
	public $display_order = array();
	
	public $dom_id = 'form';
	public $action = false;
	public $class = '';
	public $method = 'post';
	public $allow_js_to_override_definition = false; // set to false for forms where you won't be changing the structure client side
	public $autocomplete = true;

	public $debug = false; // disables captcha and form hash check
	public $skip_hash_check = false;
	public $element_counters = array();

	public $additional_js = array('form.js');
	public $additional_css = array('form.css');

	public $template_path;

	protected $template = 'form.inc';
	protected $values;

	private $form_hash;

	public function __construct($dom_id=false, $action=false, $method=false){

		if($dom_id !== false)
			$this->dom_id = $dom_id;

		if($action !== false)
			$this->action = $action;
		else
			$this->action = $_SERVER['PHP_SELF'];

		if($method !== false)
			$this->method = $method;
		

		// default the template path
		$this->template_path = dirname(__FILE__).'/';
		$base = substr($this->template_path, strpos($this->template_path,$_SERVER['DOCUMENT_ROOT']) + strlen($_SERVER['DOCUMENT_ROOT']));
		foreach($this->additional_js as &$add){
			$add = $base.$add;
		}
		foreach($this->additional_css as &$add){
			$add = $base.$add;
		}
	}

	// adds elements to the form
	// $type is either string name of element class
	// or an element object
	// return the element object
	public function add($type, $opts=null){

		if($this->debug === true && ($type=='Captcha' || is_object($type) && get_class($type)=='Captcha'))
			return $this;

		$key = isset($opts['name']) ? $opts['name'] : null;
		if(array_key_exists($key, $this->element_counters)){
			$key = $key.'_'.++$this->element_counters[$key];
		} else {
			$this->element_counters[$key] = 0;
			// $key = $key.'_'.$this->element_counters[$key];
		}
		
		$obj = 'Form\\Elements\\'.$type;

		$add = new $obj($opts, $this);
		$this->elements[$key] = $add;
		$this->display_order[] = $key;

		// add the additional js/css
		if(count((array)$add->additional_js)){
			$base = substr($add->template_path, strpos($add->template_path,$_SERVER['DOCUMENT_ROOT']) + strlen($_SERVER['DOCUMENT_ROOT']));
			$this->addJS($base, (array)$add->additional_js);
		}
		if(count((array)$add->additional_css)){
			$base = substr($add->template_path, strpos($add->template_path,$_SERVER['DOCUMENT_ROOT']) + strlen($_SERVER['DOCUMENT_ROOT']));
			$this->addCSS($base, (array)$add->additional_css);
		}


		if(method_exists(get_class($add), 'add'))
			return $add;
		else
			return $this;

	}

	public function addCSS($base, array $add_css){
		foreach($add_css as $css){
			// if(file_exists($base.$css) && !in_array($base.$css, $this->additional_css))
			if(!in_array($base.$css, $this->additional_css))
				$this->additional_css[] = $base.$css;
		}
	}

	public function addJS($base, array $add_js){
		foreach($add_js as $js){
			// if(file_exists($base.$js) && !in_array($base.$js, $this->additional_js)){
			if(!in_array($base.$js, $this->additional_js)){
				$this->additional_js[] = $base.$js;
			}
		}
	}

	// prints the from
	public function output($format = 'html'){

		if($format == 'html'){
			// generate a hash to verify submission
			$this->form_hash = $this->generateHash();
			
			if(!array_key_exists('form_hash', $_SESSION) || !is_array($_SESSION['form_hash']))
				$_SESSION['form_hash'] = [];
			$_SESSION['form_hash'][$this->dom_id] = $this->form_hash;
			
			$this->add('Hidden', array('name'=>'form_hash', 'value'=>$this->form_hash, 'ignore'=>true));

			// add the hidden to hold the json definition of the form
			// $this->add('Hidden', array('id'=>"form_definition", 'name'=>"form_definition", 'ignore'=>true));

			// grab the main form template which calls the output for the rest
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

	public function hasBeenSubmitted(){
		return isset($_REQUEST['form_hash']);
	}

	public function process(){
		// first check the form_hash
		if($this->skip_hash_check === false){
			if(
				$this->debug === false 
				&& (
					!array_key_exists('form_hash', $_SESSION) 
					|| array_key_exists($this->dom_id, $_SESSION['form_hash']) == false
					|| $_SESSION['form_hash'][$this->dom_id] !== $_REQUEST['form_hash']
				)
			){
				$this->errors = array('form'=>'Supplied hashes do not match. You may have waited to long to submit the form.');
			}
		}

		// should we let the submitted definition override the php definition?
		if($this->allow_js_to_override_definition == true && strlen($_REQUEST['form_definition'])>0){
			$this->elements = array();
			$this->element_counters = array();
			$this->display_order = array();

			$js_form_definition = json_decode($_REQUEST['form_definition'], true);
			foreach($js_form_definition['display_order'] as $r){
				// skip form hash and definition
				if($r == 'form_hash' || $r == 'form_definition')
					continue;
				
				$this->add($js_form_definition['elements'][$r]['object'], $js_form_definition['elements'][$r]);
			}
		}

		// loop through all of the elements and call the process
		foreach($this->elements as $el){
			if($el->ignore == true)
				continue;

			if($el->process() === false){
				if(!is_array($this->errors))
					$this->errors = array();

				$this->errors[$el->name] = $el->error_msg;
			}
		}

		$this->processed = true;

		if($this->errors == false)
			return true;
		else
			return false;
	}

	public function getValues($force = false){
		if($force == false && isset($this->values) && is_array($this->values))
			return $this->values;

		$this->values = array();
		foreach($this->elements as $key=>$el){
			if($el->ignore || get_class($el)=='Captcha')
				continue;
			
			foreach($el->getValue() as $name=>$value){
				if(array_key_exists($name, $this->values)){
					$temp = $this->values[$name];
					$this->values[$name] = array();
					$this->values[$name] = array_merge($this->values[$name], $temp);

					$this->values[$name] = array_merge($this->values[$name], $value);
				} else {
					$this->values[$name] = $value;
				}
			}
		}
		return $this->values;
	}


	public function getElementNamed($name){
		if(array_key_exists($name, $this->elements))
			return $this->elements[$name];
		else{
			foreach($this->elements as $el){
				if(property_exists($el, 'elements') && array_key_exists($name, $el->elements)){
					return $el->elements[$name];
				}
			}
		}

		return false;
	}

	public function getElementsByType($type, $elements = null){
		if($elements == null)
			$elements = $this->elements;

		$return = [];
		foreach($elements as &$e){
			if($e->class_type == $type)
				$return[] = $e;

			if(property_exists($e, 'elements')){
				$return = array_merge($return, $this->getElementsByType($type, $e->elements));
			}
		}
		return $return;
	}


	private function generateHash(){
		$letters = array_merge(range('a','z'), range('A','Z'), range(0,9), array('!','@','#','$','%','^','&','*','(',')','_','+'));
		$hash = '';
		while(strlen($hash)<12){
			$letter = $letters[rand(0, count($letters)-1)];
			if(strpos($hash, $letter) === false)
				$hash .= $letter;
		}

		return md5($hash);
	}

	private function checkHash(){

	}


	/**/
	public function dump(){
		return get_object_vars($this);
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