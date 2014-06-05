<fieldset id="<?php echo $this->id ?>" <?php echo $this->outputDataProperties() ?> <?php echo $this->outputDataProperties() ?>>
	<?php
	if(isset($this->legend))
		print '<legend>'.$this->legend.'</legend>';

	foreach($this->elements as $el){
		print $el->output();
	}
	?>
</fieldset>