<?php

namespace Form\Elements;

// in the global include path
require 'recaptchalib.php';

class Captcha extends Input{

	protected $template = 'captcha.inc';
	
	public $class_type = 'captcha';
	public $required = true;
	public $js_options = array(); // see https://developers.google.com/recaptcha/ for the options
	public $name = 'captcha';


	public function process(){
		$rsp = recaptcha_check_answer (
			RECAPTCHA_GLOBAL_PRIVATE_KEY, 
			$_SERVER["REMOTE_ADDR"], 
			$_REQUEST["recaptcha_challenge_field"], 
			$_REQUEST["recaptcha_response_field"]
		);

		$this->value = $_REQUEST["recaptcha_response_field"];

		if(!$rsp->is_valid){
			$this->error = true;
			$this->error_msg = 'The CAPTCHA was entered incorrectly';
			return false;
		} else {
			return true;
		}
	}

}
?>
