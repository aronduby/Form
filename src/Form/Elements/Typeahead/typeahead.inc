<section id="<?php echo $this->name ?>_holder" class="element_holder typeahead_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label)){
		?>
		<label><?php echo $this->label ?></label>
		<?php
	}
	?>

	<input 
		type="text"  
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name ?>" 
		class="<?php echo $this->class ?> typeahead-input" 
		autocomplete="off"
		placeholder="<?php echo $this->placeholder ?>"
		value="<?php echo $this->value ?>"
	/>

	<div class="json datasets"><?php print is_string($this->datasets) ? $this->datasets : json_encode($this->datasets) ?></div>

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