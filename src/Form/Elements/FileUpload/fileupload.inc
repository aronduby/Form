<section 
	id="<?php echo $this->name ?>_holder" 
	class="element_holder file_holder<?php echo ($this->required ? ' required' : '').($this->error ? ' error' : '').($this->multiple ? ' multiple' : '') ?>" 
	<?php echo $this->outputDataProperties() ?>
>
	
	<?php
	if(isset($this->label))
		print '<label>'.$this->label.'</label>';
	?>

	
	<input type="hidden" name="MAX_FILE_SIZE" value="<?php echo $this->max_file_size ?>" />
	<input type="button" class="button file_trigger" value="<?php echo $this->multiple ? 'add files' : 'browse' ?>" <?php echo $this->multiple ? 'data-multiple' : '' ?>>
	<div class="list_holder"><ul class="file_list" data-eq="0"><?php
		/*
		if(isset($this->value) || isset($this->display)){
			$show = isset($this->value) ? $this->value : $this->display;
			// if its an image
			$ext = explode('.', $show);
			$ext = array_pop($ext);
			$img_exts = array('jpeg','jpg','gif','png');
			if(in_array(strtolower($ext), $img_exts)){
				print '<li><img src="'.$show.'" class="upload_pic" title="" alt="" /><span class="name">'.basename($this->value).'</span></li>';
			} else {
				print '<li><a href="'.$show.'" target="_blank">'.basename($show).'</a></li>';
			}
		} else {
			// print '<li class="empty">no files choosen</li>';
		}
		*/
	?></ul></div>

	<?php
	if(isset($this->description)) {
		print '<div class="description">';
			print $this->description;
		print '</div>';
	}

	if($this->error === true)
		print '<label class="errors" >'.$this->error_msg.'</label>';
	?>
	
	<input type="file" 
		id="<?php echo $this->id ?>" 
		name="<?php echo $this->name .($this->multiple ? '[]' : '') ?>" 
		class="<?php echo $this->class ?>"
		data-eq="0"
		<?php echo $this->multiple ? 'multiple' : '' ?>
		<?php echo $this->accept ? 'accept="'.(is_array($this->accept) ? implode(',', $this->accept) : $this->accept).'"' : '' ?>
	/>

</section>