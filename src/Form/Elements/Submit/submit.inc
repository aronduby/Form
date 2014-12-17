<section 
	id="<?php echo $this->id ?>_holder" 
	class="form-group" 
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

	<div>
		<input 
			type="submit" 
			id="<?php echo $this->id ?>" 
			name="<?php echo $this->name ?>" 
			class="btn btn-primary <?php echo $this->class ?>" 
			value="<?php echo $this->value ?>" 
		/>
	</div>
	
	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>

</section>