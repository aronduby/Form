<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label)){
		?><label for="<?php echo $this->name ?>_date" class="control-label"><?php echo $this->label ?></label><?php
	}
	?>

	<?php
	if($this->error === true){
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	}
	?>
	
	<div class="form-inline">
		<input 
			type="date"  
			id="<?php echo $this->id ?>" 
			name="<?php echo $this->name ?>[date]" 
			class="form-control <?php echo $this->class ?>" 
			value="<?= isset($this->value) ? $this->value->format($this->date_format) : '' ?>" 
			placeholder="<?php echo $this->placeholder['date'] ?>"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			<?php echo $this->required ? 'required' : '' ?>
		/>
		@
		<input 
			type="time"  
			id="<?php echo $this->id ?>" 
			name="<?php echo $this->name ?>[time]" 
			class="form-control <?php echo $this->class ?>" 
			value="<?= isset($this->value) ? $this->value->format($this->time_format) : '' ?>" 
			placeholder="<?php echo $this->placeholder['time'] ?>"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			<?php echo $this->required ? 'required' : '' ?>
		/>
	</div>

	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print html_entity_decode($this->description);
		print '</div>';
	}
	?>
	
</section>