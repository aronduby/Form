<section id="<?php echo $this->name ?>_holder" class="element_holder autosuggest_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label)){
		?>
		<label><?php echo $this->label ?></label>
		<?php
	}
	?>

	<div class="note">Select all that apply by clicking each item, or type your own terms in the box</div>

	<input 
		type="text"  
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name ?>" 
		class="<?php echo $this->class ?> as-input" 
		autocomplete="off"
		placeholder="<?php echo $this->placeholder ?>"
	/>

	<div class="json options"><?php print json_encode($this->formatted_options) ?></div>
	<div class="json selected"><?php print json_encode($this->formatted_value) ?></div>

	<?php
	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}

	if($this->error === true)
		print '<label class="errors">'.$this->error_msg.'</label>';
	?>
</section>