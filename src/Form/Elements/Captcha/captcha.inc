<section id="<?php echo $this->name ?>_holder" class="element_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	<?php
	if(isset($this->label)){
		?>
		<label for="recaptcha_response_field"><?php echo $this->label ?></label>	
		<?php
	}
	
	if(is_array($this->js_options) && count($this->js_options)){
		?>
		<script type="text/javascript">
			var RecaptchaOptions = <?php echo json_encode($this->js_options) ?>;
		</script>	
		<?php
	}

	echo recaptcha_get_html(RECAPTCHA_GLOBAL_PUBLIC_KEY);

	if($this->error === true)
		print '<label class="errors" for="recaptcha_response_field">'.$this->error_msg.'</label>';
	?>
</section>