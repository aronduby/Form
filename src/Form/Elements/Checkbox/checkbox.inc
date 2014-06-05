<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label))
		print '<label>'.$this->label.'</label>';
	?>

	<ul class="option_holder">
		<?php
		$i = 1;
		foreach($this->options as $val=>$text){
			print '<li>
				<input type="checkbox" id="'.$this->name.'_'.$i.'" name="'.$this->name.'[]" value="'.$val.'" '.(in_array($val, (array)$this->value) ? 'checked="checked"' : '' ).' />
				<label for="'.$this->name.'_'.$i.'">'.$text.'</label>
			</li>';
			$i++;
		}
		?>
	</ul>

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