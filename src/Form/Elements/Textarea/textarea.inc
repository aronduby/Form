<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label))
		print '<label for="'.$this->name.'_textarea">'.$this->label.'</label>';
	?>

	<textarea  
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name ?>" 
		class="<?php echo $this->class ?>"
		placeholder="<?php echo $this->placeholder ?>"
		><?php echo $this->value ?></textarea>
	
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