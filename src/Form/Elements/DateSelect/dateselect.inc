<section id="<?php echo $this->name ?>_holder" class="element_holder multiple_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label)){
		?><label for="<?php echo $this->name ?>_select"><?php echo $this->label ?></label><?php
	}
	?>
	
	<div class="dateselect_holder">
		<select id="<?php echo $this->id ?>-month" name="<?php echo $this->name ?>[month]" class="month <?php echo $this->class ?>">
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['month'].'</option>';
			foreach($this->months as $val=>$text){
				print '<option value="'.$val.'" '.(isset($this->value) && $val == $this->value->format('n') ? 'selected="selected"' : '').' >'.$text.'</option>';
			}
			?>
		</select>
		<select id="<?php echo $this->id ?>-day" name="<?php echo $this->name ?>[day]" class="day <?php echo $this->class ?>">
			<?php
			print '<option data-placeholder="" value="0">'.$this->placeholder['day'].'</option>';
			foreach($this->days as $val=>$text){
				print '<option value="'.$text.'" '.(isset($this->value) && $text == $this->value->format('j') ? 'selected="selected"' : '').' >'.$text.'</option>';
			}
			?>
		</select>
		<select id="<?php echo $this->id ?>-year" name="<?php echo $this->name ?>[year]" class="year <?php echo $this->class ?>">
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
		print '<div class="description">';
			print html_entity_decode($this->description);
		print '</div>';
	}

	if($this->error === true)
		print '<label class="errors" for="'.$this->id.'">'.$this->error_msg.'</label>';
	?>
</section>