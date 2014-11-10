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
			id="<?php echo $this->id ?>-month" 
			name="<?php echo $this->name ?>[month]" 
			class="form-control month <?php echo $this->class ?>"
		>
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['month'].'</option>';
			foreach($this->months as $val=>$text){
				print '<option value="'.$val.'" '.(isset($this->value) && $val == $this->value->format('n') ? 'selected="selected"' : '').' >'.$text.'</option>';
			}
			?>
		</select>
		<select 
			id="<?php echo $this->id ?>-day" 
			name="<?php echo $this->name ?>[day]" 
			class="form-control day <?php echo $this->class ?>"
		>
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['day'].'</option>';
			foreach($this->days as $val=>$text){
				print '<option value="'.$text.'" '.(isset($this->value) && $text == $this->value->format('j') ? 'selected="selected"' : '').' >'.$text.'</option>';
			}
			?>
		</select>
		<select 
			id="<?php echo $this->id ?>-year" 
			name="<?php echo $this->name ?>[year]" 
			class="form-control year <?php echo $this->class ?>"
		>
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['year'].'</option>';
			foreach($this->years as $val=>$text){
				print '<option value="'.$val.'" '.(isset($this->value) && $val == $this->value->format('Y') ? 'selected="selected"' : '').' >'.$text.'</option>';
			}
			?>
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