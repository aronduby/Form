<section id="<?php echo $this->name ?>_holder" class="phone_holder element_holder <?php echo $this->holder_class ?> <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>


<?php
if(isset($this->label))
	print '<label for="'.$this->id.'">'.$this->label.'</label>';

?>
	<div class="inline-elements">
		<span>(</span><input 
			type="number"  
			id="<?php echo $this->id ?>-areacode" 
			name="<?php echo $this->name ?>[areacode]" 
			class="<?php echo $this->class ?> phone areacode" 
			value="<?php echo $this->value['areacode'] ?>" 
			placeholder="<?php echo $this->placeholder['areacode'] ?>"
			maxlength="3"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			/><span>)</span>
		<input 
			type="number"  
			id="<?php echo $this->id ?>-prefix" 
			name="<?php echo $this->name ?>[prefix]" 
			class="<?php echo $this->class ?> phone prefix" 
			value="<?php echo $this->value['prefix'] ?>" 
			placeholder="<?php echo $this->placeholder['prefix'] ?>"
			maxlength="3"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			/><span>-</span>
		<input 
			type="number"  
			id="<?php echo $this->id ?>-linenumber" 
			name="<?php echo $this->name ?>[linenumber]" 
			class="<?php echo $this->class ?> phone linenumber" 
			value="<?php echo $this->value['linenumber'] ?>" 
			placeholder="<?php echo $this->placeholder['linenumber'] ?>"
			maxlength="4"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			/><span>extension:</span>
		<input 
			type="number"  
			id="<?php echo $this->id ?>-extension" 
			name="<?php echo $this->name ?>[extension]" 
			class="<?php echo $this->class ?> phone extension" 
			value="<?php echo isset($this->value['extension']) ? $this->value['extension'] : '' ?>" 
			placeholder="<?php echo $this->placeholder['extension'] ?>"
			<?php echo $this->disabled ? 'disabled' : '' ?>
			/>
	</div>

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