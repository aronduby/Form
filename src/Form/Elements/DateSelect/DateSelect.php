<?php

namespace Form\Elements;

class DateSelect extends Input {

	public $class_type = 'date';
	public $months;
	public $days;
	public $years;
	
	public $min_year;
	public $max_year;
	public $year_order = 'ASC';

	public $month_format = 'F'; // one of the month options from http://us.php.net/manual/en/function.date.php

	public $placeholder = [
		'month' => "Month",
		'day' => "Day",
		'year' => "Year"
	];

	public $additional_js = ['form.select.js'];

	protected $template = 'dateselect.inc';

	public function __construct($opts, $form=null){
		
		parent::__construct($opts, $form);

		$cur_year = date('Y');

		// months
		if(!isset($this->months)){
			//$this->months[0] = $this->placeholder['month'];
			foreach(range(1,12) as $m)
				$this->months[$m] = date($this->month_format, strtotime($cur_year.'-'.$m.'-1'));
		}

		// days
		// $this->days = array_merge([$this->placeholder['day']], range(1,31));
		$this->days = range(1,31);

		// years
		if(!isset($this->years)){
			$this->min_year = isset($this->min_year) ? $this->min_year : $cur_year - 100;
			$this->max_year = isset($this->max_year) ? $this->max_year : $cur_year;
			foreach(range($this->min_year, $this->max_year) as $y)
				$this->years[$y] = $y;
			
			if($this->year_order == 'DESC')
				$this->years = array_reverse($this->years, true);
		}

		return $this;
	}

	public function process(){
		// if a value is supplied, take it
		if(isset($_REQUEST[$this->name]) && count($_REQUEST[$this->name])){
			$vals = $_REQUEST[$this->name];
			$missing_fields = [];
			
			if($vals['month']==0)
				$missing_fields[] = 'Month';
			if($vals['day']==0)
				$missing_fields[] = 'Day';
			if($vals['year']==0)
				$missing_fields[] = 'Year';

			if(count($missing_fields) && $this->required){
				$this->error = true;
				$this->error_msg = 'You must choose a '.implode(', ', $missing_fields);
				return false;
			} else {
				try{
					if(array_sum($vals)==0 && !$this->required){
						$this->value = null;
					} else {
						$this->value = new \DateTime($vals['year'].'-'.$vals['month'].'-'.$vals['day']);
					}
					return true;
				} catch(Exception $e){
					$this->error = true;
					$this->error_msg = $e->getMessage();
					return false;
				}
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
	

}

?>
