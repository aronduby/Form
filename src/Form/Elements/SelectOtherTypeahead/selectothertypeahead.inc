<section id="<?php echo $this->name ?>_holder" class="element_holder selectothertypeahead_holder <?php echo $this->required ? 'required' : '' ?> <?php echo $this->error ? 'error' : '' ?>" <?php echo $this->outputDataProperties() ?>>
	
	<?php
	if(isset($this->label))
		print '<label for="'.$this->name.'_select">'.$this->label.'</label>';
	?>
	
	<select id="<?php echo $this->id ?>" name="<?php echo $this->name ?>[id]" class="<?php echo $this->class ?>">
		<?php
		if(isset($this->placeholder)){
			print '<option data-placeholder="" value="">'.$this->placeholder.'</option>';
		}
		foreach($this->options as $id=>$obj){
			if(!$obj->public) continue;

			// if we were passed an object use text and value properties and make the rest data
			$properties = [];
			foreach(get_object_vars($obj) as $k=>$v){
				if(is_array($v)) continue;
				$properties[] = ($k!='value'?'data-':'').$k.'="'.$v.'"';
			}
			$selected = ($obj->value == $this->value['id'] || ( !$this->value_is_public && $obj->other ));
			print '<option '.implode(' ', $properties).' '.( $selected ? 'selected="selected" ' : '' ).' >'.$obj->text.'</option>';
		}
		?>
	</select>

	<section class="other">
		<input 
			type="text"  
			id="<?php echo $this->id ?>-string" 
			name="<?php echo $this->name ?>[string]" 
			class="<?php echo $this->class ?> typeahead-input" 
			autocomplete="off"
			placeholder="<?php echo $this->typeahead_placeholder ?>"
			value="<?php echo isset($this->value['id']) ? $this->options[$this->value['id']]->text : '' ?>"
		/>

		<div class="json datasets">
			<?php
			$local = [];
			foreach($this->options as $opt){
				$opt->id = $opt->value;
				$opt->value = $opt->text;
				$local[] = $opt;
			}
			print '{"local":'.json_encode($local).'}';
			?>
		</div>
	</section>

	<?php
	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}

	if($this->error === true)
		print '<label class="errors" for="'.$this->id.'">'.$this->error_msg.'</label>';
	?>
</section>