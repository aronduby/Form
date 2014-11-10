<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->holder_class ?> <?php echo $this->required ? 'required' : '' ?>"
	<?php echo $this->outputDataProperties() ?>
>
	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->id ?>" 
			class="control-label <?php echo $this->required ? 'required' : '' ?>"
			><?php echo $this->label ?></label>
		<?php
	}
	?>

	<input 
		type="button"
		id="<?php echo $this->id ?>"
		name="<?php echo $this->name ?>"
		class="btn btn-default <?php echo $this->class ?>"
		value="<?php echo $this->value ?>" 
		<?php echo $this->outputDataProperties() ?> 
	/>
	
	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>

</section>