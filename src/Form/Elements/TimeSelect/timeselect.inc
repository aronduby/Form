<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label)){
		?><label for="<?php echo $this->name ?>_select" class="control-label"><?php echo $this->label ?></label><?php
	}
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>
	
	<div class="form-inline">
		<select 
			id="<?php echo $this->id ?>-hours" 
			name="<?php echo $this->name ?>[hours]" 
			class="form-control hours <?php echo $this->class ?>"
		>
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['hours'].'</option>';
			foreach($this->hours as $val=>$text){
				$text = str_pad($text, 2, '0', STR_PAD_LEFT);
				print '<option value="'.$text.'" '.(isset($this->value) && $val == $this->value->format('g') ? 'selected' : '').' >'.$text.'</option>';
			}
			?>
		</select> :
		<select 
			id="<?php echo $this->id ?>-minutes" 
			name="<?php echo $this->name ?>[minutes]" 
			class="form-control minutes <?php echo $this->class ?>"
		>
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['minutes'].'</option>';
			foreach($this->minutes as $val=>$text){
				$text = str_pad($text, 2, '0', STR_PAD_LEFT);
				print '<option value="'.$text.'" '.(isset($this->value) && $text == $this->value->format('i') ? 'selected' : '').' >'.$text.'</option>';
			}
			?>
		</select> :
		<select 
			id="<?php echo $this->id ?>-ampm" 
			name="<?php echo $this->name ?>[ampm]" 
			class="form-control ampm <?php echo $this->class ?>"
		>
			<option data-placeholder="" value="0"><?= $this->placeholder['ampm'] ?></option>
			<option value="AM" <?= (isset($this->value) && 'AM' == $this->value->format('A') ? 'selected' : '') ?>>AM</option>
			<option value="PM" <?= (isset($this->value) && 'PM' == $this->value->format('A') ? 'selected' : '') ?>>PM</option>
		</select>
	</div>

	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print html_entity_decode($this->description);
		print '</div>';
	}
	?>
	
</section>