<section 
	id="<?php echo $this->name ?>_holder" 
	class="form-group credit-card-holder <?= $this->required ? 'required' : '' ?> <?= count($this->error_flds) ? 'has-error' : '' ?>"
	<?php echo $this->outputDataProperties() ?>
>

	<input class="card-type" type="hidden" name="<?= $this->name ?>[card_type]" value="<?php echo $this->value['name'] ?>" />

	<?php
	if(isset($this->label))
		print '<label class="control-label">'.$this->label.'</label>';
	?>

	<?php
	if($this->error === true){
		print '<div class="errors bs-callout bs-callout-danger"><ul><li>'.implode('</li><li>', $this->error_flds).'</li></ul></div>';
	}
	?>

	<!-- name -->
	<div class="form-group <?php echo array_key_exists('name', $this->error_flds) ? 'has-error' : '' ?>">
		<label for="<?php echo $this->name.'_name' ?>" class="control-label">
			Name On the Card
		</label>
		<input 
			type="text" 
			class="form-control" 
			id="<?php echo $this->name.'_name' ?>" 
			name="<?php echo $this->name.'[name]' ?>" 
			value="<?php echo $this->value['name'] ?>" 
			<?= $this->required ? 'required' : '' ?>
			/>
	</div>

	<!-- number -->
	<div class="form-group <?php echo array_key_exists('card_number', $this->error_flds) || array_key_exists('card_type', $this->error_flds) ? 'has-error' : '' ?> <?= $this->required ? 'required' : '' ?>">
		<label for="<?php echo $this->name.'_card_numner' ?>" class="control-label">
			Card Number
		</label>
		<div class="input-group">
			<input 
				type="text" 
				id="<?php echo $this->name ?>_card_number" 
				name="<?php echo $this->name ?>[card_number]" 
				class="form-control cc_card_number"
				value="<?php echo preg_replace('/(\d{4})/','$1 ', $this->value['card_number']) ?>"
				autocomplete="off"
				<?= $this->required ? 'required' : '' ?>
			/>
			<span class="input-group-addon cc-type" data-card-type="<?= $this->value['card_type'] ?>"></span>
		</div>
	</div>

	<!-- date and security -->
	<div>
		<div class="row">
			<div class="col-md-3 form-group <?php echo array_key_exists('expiration', $this->error_flds) ? 'has-error' : '' ?> <?= $this->required ? 'required' : '' ?>">
				<label for="<?php echo $this->name ?>_exp_month" class="control-label">
						Expiration Date (mm/yyyy)
				</label>
				<div class="form-inline">
					<select 
						id="<?php echo $this->name ?>_exp_month" 
						name="<?php echo $this->name ?>[exp_month]" 
						class="cc_exp_month form-control"
						<?= $this->required ? 'required' : '' ?>
					>
						<?php
						foreach($this->exp_months as $val=>$text){
							print '<option value="'.$val.'" '.($val == $this->value['exp_month'] ? 'selected="selected"' : '').' >'.$val.' - '.$text.'</option>';
						}
						?>
					</select>
					<select 
						id="<?php echo $this->name ?>_exp_year" 
						name="<?php echo $this->name ?>[exp_year]"
						class="cc_exp_year form-control"
						<?= $this->required ? 'required' : '' ?>
					>
						<?php
						foreach($this->exp_years as $year){
							print '<option value="'.$year.'" '.($year == $this->value['exp_year'] ? 'selected="selected"' : '').' >'.$year.'</option>';
						}
						?>
					</select>
				</div>
			</div>
			<div class="col-md-3 form-group <?php echo array_key_exists('cvv2', $this->error_flds) ? 'has-error' : '' ?> <?= $this->required ? 'required' : '' ?>">
				<label for="<?php echo $this->name ?>_cvv2" class="control-label">
					Security Code <abbr title="For MasterCard &amp; Visa, it's the last three digits in the signature area on the back of your card.  For American Express, it's the four digits on the front of the card.">whats this?</abbr>
				</label>
				<input type="text"
					id="<?php echo $this->name ?>_cvv2" 
					name="<?php echo $this->name ?>[cvv2]"
					class="cc_cvv2 form-control" 
					value="<?php echo $this->value['cvv2'] ?>" 
					maxlength="4"
					<?= $this->required ? 'required' : '' ?>
					/>
			</div>
		</div>
	</div>


	<?php
	if(isset($this->description)) {
		print '<div class="help-block">';
			print $this->description;
		print '</div>';
	}
	?>

</section>