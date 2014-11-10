<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group autosuggest_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label)){
		?>
		<label class="control-label"><?php echo $this->label ?></label>
		<?php
	}
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>

	<div class="form-control">
		<input 
			type="text"  
			id="<?php echo $this->id ?>" 
			name="<?php echo $this->name ?>" 
			class="as-input <?php echo $this->class ?>" 
			autocomplete="off"
			placeholder="<?php echo $this->placeholder ?>"
		/>
	</div>

	<div class="hidden json options"><?php print json_encode($this->formatted_options) ?></div>
	<div class="hidden json selected"><?php print json_encode($this->formatted_value) ?></div>

	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>
	
</section>