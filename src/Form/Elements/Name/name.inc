<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo ($this->error ? 'has-error' : '') ?> <?php echo $this->required ? 'required' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->name.'_first' ?>" 
			class="control-label"
			><?php echo $this->label ?></label>
		<?php
	}
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>


	<div class="row form-group">
		<div class="col-md-6">
			<?php
			if(isset($this->label)){
				?>
				<label 
					for="<?php echo $this->name.'_first' ?>" 
					class="control-label">
					First Name
				</label>
				<?php
			}
			?>
			<input 
				type="text" 
				class="form-control" 
				id="<?php echo $this->name.'_first' ?>" 
				name="<?php echo $this->name.'[first]' ?>" 
				value="<?php echo $this->value['first'] ?>" 
				placeholder="<?php echo $this->placeholder['first'] ?>"
				<?php echo $this->required ? 'required' : '' ?>
			/>
		</div>
		<div class="col-md-6">
			<?php
			if(isset($this->label)){
				?>
				<label 
					for="<?php echo $this->name.'_last' ?>" 
					class="control-label">
					Last Name
				</label>
				<?php
			}
			?>
			<input 
				type="text" 
				class="form-control" 
				id="<?php echo $this->name.'_last' ?>" 
				name="<?php echo $this->name.'[last]' ?>" 
				value="<?php echo $this->value['last'] ?>" 
				placeholder="<?php echo $this->placeholder['last'] ?>"
				<?php echo $this->required ? 'required' : '' ?>
			/>
		</div>
	</div>


	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>

</section>