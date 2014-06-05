<section id="<?php echo $this->name ?>_holder" class="element_holder multiple_holder <?php echo ($this->error ? 'error' : '') ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->name.'_first' ?>" 
			class="<?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>"
			><?php echo $this->label ?></label>
		<?php
	}
	?>
	
	<div class="name_holder">
		<?php
		if(isset($this->label)){
			?>
			<label 
				for="<?php echo $this->name.'_first' ?>" 
				class="first_name"
				>First Name</label>
			<label 
				for="<?php echo $this->name.'_last' ?>" 
				class="last_name"
				>Last Name</label>
			<?php
		}
		?>
		<input 
			type="text" 
			class="first_name" 
			id="<?php echo $this->name.'_first' ?>" 
			name="<?php echo $this->name.'[first]' ?>" 
			value="<?php echo $this->value['first'] ?>" 
			placeholder="<?php echo $this->placeholder['first'] ?>"
		/><input 
			type="text" 
			class="last_name"
			id="<?php echo $this->name.'_last' ?>" 
			name="<?php echo $this->name.'[last]' ?>" 
			value="<?php echo $this->value['last'] ?>" 
			placeholder="<?php echo $this->placeholder['last'] ?>"
			/>
	</div>

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