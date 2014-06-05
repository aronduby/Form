<?php
# REQUIRED
$required = array(
	'type' => $this->required &&  in_array('type', $this->required_fields) && count($this->types)>0,
	'street' => $this->required && in_array('street', $this->required_fields),
	'city' => $this->required && in_array('city', $this->required_fields),
	'state' => $this->required && in_array('state', $this->required_fields),
	'zip' => $this->required && in_array('zip', $this->required_fields),
);

// if any of city/state/zipcode are required treat that label as required
$required['csz'] = ($required['city'] || $required['state'] || $required['zip']);
// if any of the parts of the address are required treat the main address label as required
$required['address'] = ($required['street'] || $required['csz'] );

# ERRORS
// if city/state/zipcode has an error
if(
	in_array('city', array_keys($this->error_flds))
	|| in_array('state', array_keys($this->error_flds))
	|| in_array('zip', array_keys($this->error_flds))
)
	$this->error_flds['csz'] = true;

// if any parts of the address have an error
if(
	in_array('street', array_keys($this->error_flds))
	|| in_array('csz', array_keys($this->error_flds))
)
	$this->error_flds['address'] = true;
$error_flds = array_keys($this->error_flds);
?>

<section id="<?php echo $this->id ?>_holder" class="address_holder element_holder multiple_holder <?php echo $this->class ?> <?= $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>

	<a class="remover" data-icon="0"></a>

	<input type="hidden" name="<?php echo $this->name.'['.$this->counter.'][address_id]' ?>" value="<?php echo $this->value['address_id'] ?>" />
	
	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->name.'_street' ?>" 
			class="<?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>"
			><?php echo $this->label ?></label>
		<?php
	}


	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}
	?>
	

	<?php
	if(count($this->types)){
		if(isset($this->label)){
			?>
			<label 
				for="<?php echo $this->name.'_type' ?>"
				class="inline <?php echo $required['type'] ? 'required' : '' ?> <?php echo in_array('type', $error_flds) ? 'error' : '' ?>" 
				>Type</label>
			<?php
		}
		?>
		<select 
			class="type <?php echo $required['type'] ? 'required' : '' ?> <?php echo in_array('type', $error_flds) ? 'error' : '' ?>" 
			id="<?php echo $this->name.'_type' ?>" 
			name="<?php echo $this->name.'['.$this->counter.'][type_id]' ?>" 
		/>
			<?php
			foreach($this->types as $k=>$v){
				$data = [];
				if(is_array($v)){
					$text = $v['text'];
					foreach($v as $dk=>$dv){
						$data[] = 'data-'.$dk.'="'.$dv.'"';
					}
				} else {
					$text = $v;
				}
				print '<option value="'.$k.'" '.implode(' ',$data).' '.($k==$this->value['type_id'] ? 'selected' : '').'>'.$text.'</option>';
			}
			?>
		</select>
	<?php
	}
	?>




	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->name.'_street' ?>"
			class="inline <?php echo $required['street'] ? 'required' : '' ?> <?php echo in_array('street', $error_flds) ? 'error' : '' ?>" 
			>Street</label>
		<?php
	}
	?>
	<input 
		type="text" 
		class="street <?php echo $required['street'] ? 'required' : '' ?> <?php echo in_array('street', $error_flds) ? 'error' : '' ?>" 
		id="<?php echo $this->name.'_street' ?>" 
		name="<?php echo $this->name.'['.$this->counter.'][street]' ?>" 
		value="<?php echo $this->value['street'] ?>" 
		placeholder="<?php echo $this->placeholders['street'] ?>"
		/>

	
	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->name.'_city' ?>"
			class="inline <?php echo $required['csz'] ? 'required' : '' ?> <?php echo in_array('csz', $error_flds) ? 'error' : '' ?>" 
			>City/State/Zip</label>
		<?php
	}
	?>
	<input 
		type="text" 
		class="city <?php echo $required['city'] ? 'required' : '' ?> <?php echo in_array('city', $error_flds) ? 'error' : '' ?>" 
		id="<?php echo $this->name.'_city' ?>" 
		name="<?php echo $this->name.'['.$this->counter.'][city]' ?>" 
		value="<?php echo $this->value['city'] ?>" 
		placeholder="<?php echo $this->placeholders['city'] ?>"
	/><input 
		type="text" 
		class="state <?php echo $required['state'] ? 'required' : '' ?> <?php echo in_array('state', $error_flds) ? 'error' : '' ?>" 
		id="<?php echo $this->name.'_state' ?>" 
		name="<?php echo $this->name.'['.$this->counter.'][state]' ?>" 
		value="<?php echo $this->value['state'] ?>" 
		maxlength="2" 
		placeholder="<?php echo $this->placeholders['state'] ?>"
	/><input 
		type="text" 
		class="zipcode <?php echo $required['zip'] ? 'required' : '' ?> <?php echo in_array('zip', $error_flds) ? 'error' : '' ?>" 
		id="<?php echo $this->name.'_zip' ?>" 
		name="<?php echo $this->name.'['.$this->counter.'][zip]' ?>" 
		value="<?php echo $this->value['zip'] ?>" 
		maxlength="10" 
		placeholder="<?php echo $this->placeholders['zip'] ?>"
		/>

	<?php
	if($this->error === true)
		print '<label class="errors">'.$this->error_msg.'</label>';
	?>

</section>