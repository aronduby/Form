<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group file-holder <?php echo ($this->required ? 'required' : '').($this->error ? 'has-error' : '') ?> <?=($this->multiple ? 'multiple' : '') ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label))
		print '<label class="control-label">'.$this->label.'</label>';
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>

	<div>
		<input type="hidden" name="MAX_FILE_SIZE" value="<?php echo $this->max_file_size ?>" />
		<input 
			type="button" 
			class="btn btn-default file-trigger" 
			value="<?php echo $this->multiple ? 'add files' : 'browse' ?>" 
			<?php echo $this->multiple ? 'data-multiple' : '' ?>
		>
		<div class="list-holder">
			<ul class="list-group file-list"></ul>
		</div>
	</div>

	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>
	
	<div class="input-holder">
		<input
			type="file" 
			id="<?php echo $this->id ?>" 
			name="<?php echo $this->name .($this->multiple ? '[]' : '') ?>" 
			class="<?php echo $this->class ?>"
			data-eq="0"
			<?php echo $this->multiple ? 'multiple' : '' ?>
			<?php echo $this->accept ? 'accept="'.(is_array($this->accept) ? implode(',', $this->accept) : $this->accept).'"' : '' ?>
		/>
	</div>

</section>