<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group phone_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>


	<?php
	if(isset($this->label))
		print '<label class="control-label" for="'.$this->id.'">'.$this->label.'</label>';
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>

	<div class="form-inline">
		<span>(</span>
		<input 
			type="tel"  
			id="<?php echo $this->id ?>-areacode" 
			name="<?php echo $this->name ?>[areacode]" 
			class="form-control <?php echo $this->class ?> phone areacode" 
			value="<?php echo $this->value['areacode'] ?>" 
			placeholder="<?php echo $this->placeholder['areacode'] ?>"
			maxlength="3"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			<?php echo $this->required ? 'required' : '' ?>
		/>
		<span>)</span>
		<input 
			type="tel"  
			id="<?php echo $this->id ?>-prefix" 
			name="<?php echo $this->name ?>[prefix]" 
			class="form-control <?php echo $this->class ?> phone prefix" 
			value="<?php echo $this->value['prefix'] ?>" 
			placeholder="<?php echo $this->placeholder['prefix'] ?>"
			maxlength="3"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			<?php echo $this->required ? 'required' : '' ?>
		/>
		<span>-</span>
		<input 
			type="tel"  
			id="<?php echo $this->id ?>-linenumber" 
			name="<?php echo $this->name ?>[linenumber]" 
			class="form-control <?php echo $this->class ?> phone linenumber" 
			value="<?php echo $this->value['linenumber'] ?>" 
			placeholder="<?php echo $this->placeholder['linenumber'] ?>"
			maxlength="4"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			<?php echo $this->required ? 'required' : '' ?>
		/>
		<span>extension:</span>
		<input 
			type="tel"  
			id="<?php echo $this->id ?>-extension" 
			name="<?php echo $this->name ?>[extension]" 
			class="form-control <?php echo $this->class ?> phone extension" 
			value="<?php echo isset($this->value['extension']) ? $this->value['extension'] : '' ?>" 
			placeholder="<?php echo $this->placeholder['extension'] ?>"
			<?php echo $this->disabled ? 'disabled' : '' ?>
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