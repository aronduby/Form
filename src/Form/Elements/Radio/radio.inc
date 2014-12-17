<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label))
		print '<label class="control-label">'.$this->label.'</label>';
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>

	<div>
		<?php
		foreach($this->options as $val=>$text){
			if($this->inline == false){
				print '<div class="radio">';
			}
			?>
				<label class="<?= $this->inline ? 'radio-inline' : '' ?>">
					<input 
						type="radio"
						name="<?= $this->name ?>" 
						value="<?= $val ?>" 
						<?= (in_array($val, (array)$this->value) ? 'checked' : '' ) ?> 
					/>
					<?= $text ?>
				</label>
			<?php
			if($this->inline == false){
				print '</div>';
			}
		}
		?>
	</div>

	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>
</section>