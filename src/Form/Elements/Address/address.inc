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

<section 
	id="<?php echo $this->id ?>_holder" 
	class="form-group <?php echo $this->class ?> <?= $this->error ? 'has-error' : '' ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	<input type="hidden" name="<?php echo $this->name.'['.$this->counter.'][address_id]' ?>" value="<?php echo $this->value['address_id'] ?>" />
	
	<?php
	if(isset($this->label)){
		?>
		<label 
			for="<?php echo $this->name.'_street' ?>" 
			class="control-label <?php echo $this->required ? 'required' : '' ?>"
			><?php echo $this->label ?></label>
		<?php
	}
	?>

	<?php
	if($this->error === true)
		print '<div class="errors bs-callout bs-callout-danger">'.$this->error_msg.'</div>';
	?>

	<?php
	if(count($this->types)){		
		?>
		<div class="form-group <?= in_array('type', $error_flds) ? 'has-error' : '' ?> <?php echo $required['type'] ? 'required' : '' ?>">
			<?php
			if(isset($this->label)){
				?>
				<label 
					for="<?php echo $this->name.'_type' ?>"
					class="control-label" 
					>Type</label>
				<?php
			}
			?>
			<select 
				class="form-control" 
				id="<?php echo $this->name.'_type' ?>" 
				name="<?php echo $this->name.'['.$this->counter.'][type_id]' ?>" 
				<?php echo $required['type'] ? 'required' : '' ?>
			>
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
		</div>
	<?php
	}
	?>


	<div class="form-group <?= in_array('street', $error_flds) ? 'has-error' : '' ?> <?php echo $required['street'] ? 'required' : '' ?>">
		<?php
		if(isset($this->label)){
			?>
			<label for="<?php echo $this->name.'_street' ?>" class="control-label" >
				Street
			</label>
			<?php
		}
		?>
		<input 
			type="text" 
			class="form-control" 
			id="<?php echo $this->name.'_street' ?>" 
			name="<?php echo $this->name.'['.$this->counter.'][street]' ?>" 
			value="<?php echo $this->value['street'] ?>" 
			placeholder="<?php echo $this->placeholders['street'] ?>"
			<?php echo $required['street'] ? 'required' : '' ?>
		/>
	</div>

	<div class="row form-group">
		<div class="col-md-6 <?php echo in_array('city', $error_flds) ? 'has-error' : '' ?> <?php echo $required['city'] ? 'required' : '' ?>">
			<?php
			if(isset($this->label)){
				?>
				<label 
					for="<?php echo $this->name.'_city' ?>" 
					class="control-label">
					City
				</label>
				<?php
			}
			?>
			<input 
				type="text" 
				class="form-control" 
				id="<?php echo $this->name.'_city' ?>" 
				name="<?php echo $this->name.'['.$this->counter.'][city]' ?>" 
				value="<?php echo $this->value['city'] ?>" 
				placeholder="<?php echo $this->placeholders['city'] ?>"
				<?php echo $required['city'] ? 'required' : '' ?>
			/>
		</div>
		<div class="col-md-2 <?php echo in_array('state', $error_flds) ? 'has-error' : '' ?> <?php echo $required['state'] ? 'required' : '' ?>">
			<?php
			if(isset($this->label)){
				?>
				<label 
					for="<?php echo $this->name.'_state' ?>" 
					class="control-label">
					State
				</label>
				<?php
			}
			?>
			<input 
				type="text" 
				class="form-control" 
				id="<?php echo $this->name.'_state' ?>" 
				name="<?php echo $this->name.'['.$this->counter.'][state]' ?>" 
				value="<?php echo $this->value['state'] ?>" 
				maxlength="2" 
				placeholder="<?php echo $this->placeholders['state'] ?>"
				<?php echo $required['state'] ? 'required' : '' ?>
			/>
		</div>
		<div class="col-md-4 <?php echo in_array('zip', $error_flds) ? 'has-error' : '' ?> <?php echo $required['zip'] ? 'required' : '' ?>">
			<?php
			if(isset($this->label)){
				?>
				<label 
					for="<?php echo $this->name.'_zip' ?>" 
					class="control-label">
					Zipcode
				</label>
				<?php
			}
			?>
			<input 
				type="text" 
				class="form-control" 
				id="<?php echo $this->name.'_zip' ?>" 
				name="<?php echo $this->name.'['.$this->counter.'][zip]' ?>" 
				value="<?php echo $this->value['zip'] ?>" 
				maxlength="10" 
				placeholder="<?php echo $this->placeholders['zip'] ?>"
				<?php echo $required['zip'] ? 'required' : '' ?>
			/>
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