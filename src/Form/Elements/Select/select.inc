<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label))
		print '<label for="'.$this->name.'_select">'.$this->label.'</label>';
	?>
	
	<select id="<?php echo $this->id ?>" name="<?php echo $this->name ?>" class="<?php echo $this->class ?>">
		<?php
		if(isset($this->placeholder)){
			print '<option data-placeholder="" value="">'.$this->placeholder.'</option>';
		}
		foreach($this->options as $val=>$text){
			// if we were passed an object use text and value properties and make the rest data
			if(is_object($text)){
				$properties = [];
				foreach(get_object_vars($text) as $k=>$v){
					$properties[] = ($k!='value'?'data-':'').$k.'="'.$v.'"';
				}
				print '<option '.implode(' ', $properties).' '.($text->value == $this->value ? 'selected="selected"' : '').' >'.$text->text.'</option>';
			} else {
				print '<option value="'.$val.'" '.($val == $this->value ? 'selected="selected"' : '').' >'.$text.'</option>';
			}
		}
		?>
	</select>

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