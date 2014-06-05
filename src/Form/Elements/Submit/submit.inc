<section id="<?php echo $this->id ?>_holder" class="<?php echo $this->holder_class ?> <?php echo $this->required ? 'required' : '' ?> element_holder btn_holder" <?php echo $this->outputDataProperties() ?>>

	<input type="submit"  id="<?php echo $this->id ?>" name="<?php echo $this->name ?>" class="submit button <?php echo $this->class ?>" value="<?php echo $this->value ?>" />
	
	<?php
	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}
	?>

</section>