<div id="<?php echo $this->name ?>_holder" class="credit_card_holder <?php echo $this->class ?>" <?php echo $this->outputDataProperties() ?>>

	<!-- name -->
	<section id="<?php echo $this->name ?>_name_holder" class="element_holder multiple_holder <?php echo $this->required && in_array('first_name', $this->required_flds) ? 'required' : '' ?> <?php echo array_key_exists('name', $this->error_flds) ? 'error' : '' ?>">		
		<label 
			for="<?php echo $this->name.'_first_name' ?>" 
			class="<?php echo $this->required && in_array('first_name', $this->required_flds) ? 'required' : '' ?> <?php echo array_key_exists('name', $this->error_flds) ? 'error' : '' ?>"
			>First &amp; Last Name On the Card</label>
		
		<div class="name_holder">
			<label 
				for="<?php echo $this->name.'_first_name' ?>" 
				class="first_name"
				>First Name</label>
			<label 
				for="<?php echo $this->name.'_last_name' ?>" 
				class="last_name"
				>Last Name</label>
			<input 
				type="text" 
				class="first_name" 
				id="<?php echo $this->name.'_first_name' ?>" 
				name="<?php echo $this->name.'[first_name]' ?>" 
				value="<?php echo $this->value['first_name'] ?>" 
				/>
			<input 
				type="text" 
				class="last_name"
				id="<?php echo $this->name.'_last_name' ?>" 
				name="<?php echo $this->name.'[last_name]' ?>" 
				value="<?php echo $this->value['last_name'] ?>" 
				/>
		</div>

		<?php
		if(isset($this->description['name'])) {
			print '<div class="description">';
				print $this->description['name'];
			print '</div>';
		}

		if(array_key_exists('name', $this->error_flds))
			print '<label class="errors"><ul><li>'.implode('</li><li>', $this->error_flds['name']).'</li></ul></label>';
		?>
	</section>

	<!-- card number -->
	<section id="<?php echo $this->name ?>_card_number_holder" class="element_holder <?php echo $this->required && in_array('card_number', $this->required_flds) ? 'required' : '' ?> <?php echo array_key_exists('card_number', $this->error_flds) ? 'error' : '' ?>">
		
		<label for="<?php echo $this->name ?>_card_number">Credit Card Number</label>
		<input 
			type="text" 
			id="<?php echo $this->name ?>_card_number" 
			name="<?php echo $this->name ?>[card_number]" 
			class="cc_card_number"
			value="<?php echo preg_replace('/(\d{4})/','$1 ', $this->value['card_number']) ?>"
			autocomplete="off"
			/>
		
		<?php
		if(isset($this->description['card_number'])) {
			print '<div class="description">';
				print $this->description['card_number'];
			print '</div>';
		}

		if(array_key_exists('card_number', $this->error_flds))
			print '<label class="errors" for="'.$this->name.'_card_number">'.$this->error_flds['card_number'].'</label>';
		?>

	</section>

	<!-- card type -->
	<section id="<?php echo $this->name ?>__card_type_holder" class="element_holder <?php echo $this->required && in_array('card_type', $this->required_flds) ? 'required' : '' ?> <?php echo array_key_exists('card_type', $this->error_flds) ? 'error' : '' ?>">

		<label>Credit Card Type</label>

		<ul class="option_holder cc_type">
			<?php
			$i = 1;
			foreach($this->card_types as $val=>$text){
				print '<li>
					<input type="radio" id="'.$this->name.'_card_type_'.$i.'" name="'.$this->name.'[card_type]" value="'.$val.'" '.($val==(isset($this->value['card_type']) ? $this->value['card_type'] : '') ? 'checked="checked"' : '').' class="cc_type" />
					<label for="'.$this->name.'_card_type_'.$i.'" class="cc_type '.$val.'">'.$text.'</label>
				</li>';
				$i++;
			}
			?>
		</ul>

		<?php
		if(isset($this->description['card_type'])) {
			print '<div class="description">';
				print $this->description['card_type'];
			print '</div>';
		}

		if(array_key_exists('card_type', $this->error_flds))
			print '<label class="errors">'.$this->error_flds['card_type'].'</label>';
		?>
	</section>


	<!-- expiration date -->
	<section id="<?php echo $this->name ?>_expiration_holder" class="element_holder <?php echo $this->required && in_array('exp_month', $this->required_flds) ? 'required' : '' ?> <?php echo array_key_exists('expiration', $this->error_flds) ? 'error' : '' ?>">

		<label for="<?php echo $this->name ?>_exp_month">Expiration Date (mm/yyyy)</label>
		
		<select id="<?php echo $this->name ?>_exp_month" name="<?php echo $this->name ?>[exp_month]" class="cc_exp_month">
			<?php
			foreach($this->exp_months as $val=>$text){
				print '<option value="'.$val.'" '.($val == $this->value['exp_month'] ? 'selected="selected"' : '').' >'.$val.' - '.$text.'</option>';
			}
			?>
		</select>
		<select id="<?php echo $this->name ?>_exp_year" name="<?php echo $this->name ?>[exp_year]" class="cc_exp_year">
			<?php
			foreach($this->exp_years as $year){
				print '<option value="'.$year.'" '.($year == $this->value['exp_year'] ? 'selected="selected"' : '').' >'.$year.'</option>';
			}
			?>
		</select>

		<?php
		if(isset($this->description['expiration'])) {
			print '<div class="description">';
				print $this->description['expiration'];
			print '</div>';
		}

		if(array_key_exists('expiration', $this->error_flds))
			print '<label class="errors" for="'.$this->name.'_exp_month">'.$this->error_flds['expiration'].'</label>';
		?>
	</section>

	<!-- cvv2 -->
	<section id="<?php echo $this->name ?>_cvv2_holder" class="element_holder <?php echo $this->required && in_array('cvv2', $this->required_flds) ? 'required' : '' ?> <?php echo array_key_exists('cvv2', $this->error_flds) ? 'error' : '' ?> cvv2_holder">
		
		<label for="<?php echo $this->name ?>_cvv2">Security Code</label>
		<input type="text"
			id="<?php echo $this->name ?>_cvv2" 
			name="<?php echo $this->name ?>[cvv2]"
			class="cc_cvv2" 
			value="<?php echo $this->value['cvv2'] ?>" 
			maxlength="4"
			/>
		
		<?php
		if(isset($this->description['cvv2'])) {
			print '<div class="description cvv2_description">';
				print $this->description['cvv2'];
			print '</div>';
		}

		if(array_key_exists('cvv2', $this->error_flds))
			print '<label class="errors" for="'.$this->name.'cvv2">'.$this->error_flds['cvv2'].'</label>';
		?>

	</section>

</div>