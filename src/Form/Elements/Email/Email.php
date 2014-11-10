<?php

namespace Form\Elements;

class Email extends Text{

	public $class_type = 'email';	
	public $type = 'email';

	public function process(){
		
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && strlen($_REQUEST[$this->name])>0){
			$this->value = $_REQUEST[$this->name];

			if($this->validEmail($this->value)){
				return true;
			} else {
				$this->error = true;
				$this->error_msg = 'The email address you entered does not appear to be a valid.';
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


	/**
	 *	copied from: http://www.linuxjournal.com/article/9585?page=0,3
	 *	Validate an email address.
	 *	Provide email address (raw input)
	 *	Returns true if the email address has the email 
	 *	address format and the domain exists.
	*/
	protected function validEmail($email){
	   $isValid = true;
	   $atIndex = strrpos($email, "@");

	   if (is_bool($atIndex) && !$atIndex) {
		  $isValid = false;
	   } else {
		  $domain = substr($email, $atIndex+1);
		  $local = substr($email, 0, $atIndex);
		  $localLen = strlen($local);
		  $domainLen = strlen($domain);

		  if ($localLen < 1 || $localLen > 64) {
			 // local part length exceeded
			 $isValid = false;
		  
		  } else if ($domainLen < 1 || $domainLen > 255) {
			 // domain part length exceeded
			 $isValid = false;

		  } else if ($local[0] == '.' || $local[$localLen-1] == '.') {
			 // local part starts or ends with '.'
			 $isValid = false;

		  } else if (preg_match('/\\.\\./', $local)) {
			 // local part has two consecutive dots
			 $isValid = false;

		  } else if (!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain)) {
			 // character not valid in domain part
			 $isValid = false;

		  } else if (preg_match('/\\.\\./', $domain)) {
			 // domain part has two consecutive dots
			 $isValid = false;

		  } else if (!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local))) {
			 // character not valid in local part unless 
			 // local part is quoted
			 if (!preg_match('/^"(\\\\"|[^"])+"$/', str_replace("\\\\","",$local))) {
				$isValid = false;
			 }
		  }

		  if ($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A"))) {
			 // domain not found in DNS
			 $isValid = false;
		  }
	   }

	   return $isValid;
	}

}
?>
