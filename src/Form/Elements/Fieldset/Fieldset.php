<?php

namespace Form\Elements;

class Fieldset extends Input{
	
	public $class_type = 'fieldset';
	public $legend = '';
	public $elements = [];

	public $additional_js = [];
	public $additional_css = ['form.fieldset.css'];
	
	protected $form;
	protected $template = 'fieldset.inc';

	private $element_counters = [];
	private $display_order = [];

	public function __construct($opts, $form=null){
		$this->form = $form;

		parent::__construct($opts, $form);
	}

	public function add($type, $opts=null){

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
			foreach((array)$add->additional_js as $js){
				if(file_exists($base.$js) && !in_array($base.$js, $this->additional_js))
					$this->additional_js[] = $base.$js;
			}
		}
		if(count((array)$add->additional_css)){
			$base = substr($add->template_path, strpos($add->template_path,$_SERVER['DOCUMENT_ROOT']) + strlen($_SERVER['DOCUMENT_ROOT']));
			foreach((array)$add->additional_css as $css){
				if(file_exists($base.$css) && !in_array($base.$css, $this->additional_css))
					$this->additional_css[] = $base.$css;
			}
		}

		if(method_exists(get_class($add), 'add'))
			return $add;
		else
			return $this;

	}

	public function end(){
		$this->form->addCSS('', $this->additional_css);
		$this->form->addJS('', $this->additional_js);
		return $this->form;
	}


	public function process(){
		// loop through all of the elements and call the process
		foreach($this->elements as $el){
			if($el->ignore == true)
				continue;

			if($el->process() === false){
				if(!is_array($this->form->errors))
					$this->form->errors = array();

				$this->form->errors[$el->name] = $el->error_msg;
			}			
		}

		return true;		
	}


	public function getValue(){
		$values = array();
		foreach($this->elements as $key=>$el){
			if($el->ignore || get_class($el)=='Captcha')
				continue;
			
			foreach($el->getValue() as $name=>$value){
				if(array_key_exists($name, $values)){
					$temp = $values[$name];
					$values[$name] = array();
					$values[$name] = array_merge($values[$name], $temp);

					$values[$name] = array_merge($values[$name], $value);
				} else {
					$values[$name] = $value;
				}
			}
		}
		return $values;
	}


}

?>