<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>"
	<?php echo $this->outputDataProperties() ?>
>

	<?php
	if(isset($this->label)){
		?>
		<label class="control-label" for="recaptcha_response_field"><?php echo $this->label ?></label>	
		<?php
	}

	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	
	if(is_array($this->js_options) && count($this->js_options)){
		?>
		<script type="text/javascript">
			var RecaptchaOptions = <?php echo json_encode($this->js_options) ?>;
		</script>	
		<?php
	}

	echo recaptcha_get_html($this->public_key);

	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	
	?>

</section>