<?php

namespace Form\Elements;

class CreditCard extends Input{
	
	public $class_type = 'creditcard';
	public $additional_js = 'form.creditcard.js';
	public $additional_css = 'form.creditcard.css';
	public $required_flds = array('name', 'card_number', 'card_type', 'cvv2', 'exp_month', 'exp_year');

	protected $card_types = array(
		'mastercard'=>"MasterCard", 
		'visa'=>"Visa",
		'amex'=>"American Express", 
		'discover'=>"Discover"
	);

	protected $exp_months = array(
		'01' => "January",
		'02' => "February",
		'03' => "March",
		'04' => "April",
		'05' => "May",
		'06' => "June",
		'07' => "July",
		'08' => "August",
		'09' => "September",
		'10' => "October",
		'11' => "November",
		'12' => "December"
	);
	protected $exp_years = array();
	

	protected $template = 'creditcard.inc';
	protected $error_flds = array();

	public function __construct($opts, $form=null){
		parent::__construct($opts, $form);

		$this->exp_years = range(date('Y'), date('Y')+10);
	}

	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && is_array($_REQUEST[$this->name])){
			$this->value = $_REQUEST[$this->name];

			$this->value['card_number'] = preg_replace('/[^\d]/','',$this->value['card_number']);

			// check the values for the required fields
			// first just make sure that they are supplied
			if($this->required && is_array($this->required_flds)){ 
				foreach($this->required_flds as $fld){
					if(!isset($this->value[$fld]) || strlen($this->value[$fld])<=0){
						$this->error_flds[$fld] = 'You must supply a value for '.ucwords(str_replace('_','',$fld));
					}
				}
			}

			// run the luhn/mod10 check for valid number
			if(!array_key_exists('card_number', $this->error_flds)){
				try{
					if($this->luhn($this->value['card_number'])){

						//check the card type and see if it validates as that type of card
						if(in_array($this->value['card_type'], array_keys($this->card_types))){							
							if(!$this->validateCardType($this->value['card_number'], $this->value['card_type'])){
								$this->error_flds['card_number'] = 'This card number is not a valid card type. Please check the number and try again.';
							}

						} else {
							$this->error_flds['card_type'] = 'Card type not accepted. Please try a different card.';
						}			
					
					} else {
						$this->error_flds['card_number'] = 'That number doesn\'t appear to be valid. Please check your entry and try again.';
					}
				} catch(\Exception $e){
					$this->error_flds['card_number'] = 'We were unable to validate the card. Please check your entry and try again.';
				}
			}

			// make sure month and year are greater than now
			if(mktime(0,0,0,trim($this->value['exp_month']),1,$this->value['exp_year']) < mktime(0,0,0,date('n'),1,date('Y'))){
				$this->error_flds['expiration'] = 'The choosen expiration date appears to be in the past.';
			}

			// finally submit any errors back to the form
			if(count($this->error_flds) && $this->required){
				$this->error = true;
				return false;
			} else {
				return true;
			}


		} else {
			
			// check for required
			if($this->required){
				$this->error = true;
				$this->error_flds[] = 'This is a required field';
				return false;
			
			// not required, doesn't matter
			} else {
				return true;
			}
		}
	}

	// see http://en.wikipedia.org/wiki/Bank_card_number#Issuer_Identification_Number_.28IIN.29 for details
	private function validateCardType($ccnum, $type){
		switch($type){
			case 'mastercard':
				return (strlen($ccnum) == 16 && preg_match('/^5[1-5]/', $ccnum));

			case 'visa':
				return ((strlen($ccnum) == 16 || strlen($ccnum) == 13) && substr($ccnum,0,1)==4);

			case 'amex':
				return (strlen($ccnum) == 15 && preg_match('/^3[47]/', $ccnum));

			case 'discover':
				return (strlen($ccnum) == 16 && substr($ccnum,0,4) == '6011');

			default:
				return false;
		}
	}
	
	// http://forums.whirlpool.net.au/archive/1737543
	private function luhn($number){

		$chars = array_reverse(str_split($number, 1));
		$odd = array_intersect_key($chars, array_fill_keys(range(1, count($chars), 2), null));
		$even = array_intersect_key($chars, array_fill_keys(range(0, count($chars), 2), null));
		
		// $odd = array_map(function($n) { return ($n >= 5)?2 * $n – 9:2 * $n; }, $odd); FOR USE WITH 5.3 & anon function
		$odd = array_map(array($this, 'luhnOddDigit'), $odd);

		$total = array_sum($odd) + array_sum($even);
		return (((floor($total / 10) + 1) * 10 - $total) % 10 === 0);
		
	}
	
	// split to its own function since 5.2 doesn't have anonymous functions
	private function luhnOddDigit($n){
		return ($n >= 5) ? 2 * $n - 9 : 2 * $n;
	}

}
?>
