<?php

namespace Form\Elements;

class Typeahead extends Input{

	public $class_type = 'typeahead';
	protected $template = 'typeahead.inc';
	
	/*
	 *	Check out https://github.com/twitter/typeahead.js for format of datasets
	*/
	public $datasets = [];
	public $additional_js = ['typeahead.min.js', 'form.typeahead.js'];
	public $additional_css = 'form.typeahead.css';

}
?>
