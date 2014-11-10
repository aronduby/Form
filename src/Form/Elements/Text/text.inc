<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label))
		print '<label for="'.$this->id.'" class="control-label">'.$this->label.'</label>';
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>

	<input 
		type="<?php echo $this->type ?>"  
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name ?>" 
		class="form-control <?php echo $this->class ?>" 
		value="<?php echo $this->value ?>" 
		placeholder="<?php echo $this->placeholder ?>"
		<?php echo $this->disabled ? 'disabled' : '' ?>
		<?php echo $this->required ? 'required' : '' ?>
	/>
	
	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>

</section>