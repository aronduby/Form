<?php
if($this->errors !== false){
	// print_p($this->errors);
	print '<div class="form-errors bs-callout bs-callout-danger">';
		print '<h4>Oops...</h4>';
		print '<p>There appears to be '.count($this->errors).' fields with error'.(count($this->errors)>1 ? 's' : '').'. Please check the highlighted fields and try again</p>';
		if(array_key_exists('form', $this->errors)){
			print '<ul><li>'.$this->errors['form'].'</li></ul>';
		}
	print '</div>';
}
?>

<form 
	role="form"
	id="<?php echo $this->dom_id ?>" 
	class="<?php echo $this->class . ($this->errors !== false ? ' has-errors' : '')?>" 
	action="<?php echo $this->action ?>" 
	method="<?php echo $this->method ?>" 
	enctype="multipart/form-data" 
	<?php echo $this->autocomplete == false ? 'autocomplete="off"' : '' ?>
	>
	<?php

	foreach($this->elements as $el){
		print $el->output();
	}


	// output the json
	// print '<div class="json form_definition">'.$this->output('json').'</div>';
	?>
</form>