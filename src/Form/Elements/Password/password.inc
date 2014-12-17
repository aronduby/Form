<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>"
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

	<input 
		type="password"  
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name ?>" 
		class="form-control <?php echo $this->class ?>" 
		value="<?php echo $this->value ?>" 
		placeholder="<?php echo $this->placeholder ?>"
		<?php echo $this->required ? 'required' : '' ?>
	/>
	
	<?php
	if($this->confirm){
		?>
		<div class="form-group password_confirm">
			<?php
			if(isset($this->label))
				print '<label class="control-label" for="'.$this->id.'_confirm">Confirm '.$this->label.'</label>';
			?>
			<input 
				type="password"  
				id="<?php echo $this->id ?>_confirm" 
				name="<?php echo $this->name ?>_confirm" 
				class="form-control <?php echo $this->class ?>" 
				value="<?php echo $this->confirm_value ?>" 
				placeholder="<?php echo $this->confirm_placeholder ?>"
				<?php echo $this->required ? 'required' : '' ?>
			/>
		</div>
		<?php
	}


	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>

</section>