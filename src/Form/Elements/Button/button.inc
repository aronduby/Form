<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->holder_class ?> <?php echo $this->required ? 'required' : '' ?>"  <?php echo $this->outputDataProperties() ?>>

	<input type="button"  id="<?php echo $this->id ?>" name="<?php echo $this->name ?>" class="button <?php echo $this->class ?>" value="<?php echo $this->value ?>" <?php echo $this->outputDataProperties() ?> />
	
	<?php
	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}
	?>

</section>