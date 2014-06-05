<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label))
		print '<label for="'.$this->id.'">'.$this->label.'</label>';
	?>

	<input 
		type="<?php echo $this->type ?>"  
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name ?>" 
		class="<?php echo $this->class ?>" 
		value="<?php echo $this->value ?>" 
		placeholder="<?php echo $this->placeholder ?>"
		<?php echo $this->disabled ? 'disabled' : '' ?>
		/>
	
	<?php
	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}

	if($this->error === true)
		print '<label class="errors" for="'.$this->id.'">'.$this->error_msg.'</label>';
	?>

</section>