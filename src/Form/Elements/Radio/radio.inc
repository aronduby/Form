<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?> <?php echo $this->class ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label))
		print '<label>'.$this->label.'</label>';

	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}
	?>

	<ul class="option_holder">
		<?php
		$i = 1;
		foreach($this->options as $val=>$text){
			print '<li>
				<input type="radio" id="'.$this->name.'_'.$i.'" name="'.$this->name.'" value="'.$val.'" '.($val==$this->value ? 'checked="checked"' : '').' class="'.$val.'" />
				<label for="'.$this->name.'_'.$i.'" class="'.$val.'">'.$text.'</label>
			</li>';
			$i++;
		}
		?>
	</ul>

	<?php
	if($this->error === true)
		print '<label class="errors">'.$this->error_msg.'</label>';
	?>
</section>