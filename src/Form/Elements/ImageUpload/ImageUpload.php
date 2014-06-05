<?php

namespace Form\Elements;

class ImageUpload extends FileUpload{

	public $class_type = 'imageupload';
	public $upload_path;
	public $mime_type;
	public $width;
	public $height;
	public $resize_type = 'fit'; // either fit or exact

	public $make_thumb = false;
	public $thumb_name;
	public $thumb_value;
	public $thumb_path; // defaults to upload path
	public $thumb_width;
	public $thumb_height;
	public $thumb_resize_type = 'fit'; // either fit or exact


	public function __construct($opts, $form){
		parent::__construct($opts, $form);
		
		
		// make sure we have the thumb_path, if not default it to the upload path
		if($this->make_thumb === true){
			if($this->thumb_path == null)
				$this->thumb_path = $this->upload_path;

			if($this->thumb_name == null)
				throw new \Exception('Thumb name not set for '.$this->name);

		}

	}


	public function process(){

		// check to see if the file is in the $_FILES array
		if($_FILES[$this->name]['error'] !== 4){

			if($this->checkForUploadErrors() === true){

				# NORMAL IMAGES
				$fullsize = $this->processImg($this->current_location, $this->filename, $this->upload_path, $this->width, $this->height, $this->resize_type, false);
				if($fullsize === false)
					return false;
				
				$this->value = $fullsize;

				# THUMBNAILS
				if($this->make_thumb === true){
					
					// copy the normal sized file
					$base_thumbnail_on = $this->upload_path.$this->value;
					if (!$current_location = tempnam("", "FORM")){
						$this->error = true;
						$this->error_msg = "Could not create temporary file for the image thumbnail.";
						return false;
					}
					if (!copy($base_thumbnail_on, $current_location)){
						$this->error = true;
						$this->error_msg = "Could not copy image '".$base_thumbnail_on."' to temporary file '".$current_location."'.";
						return false;
					}
					$filename = basename($this->value);
					$thumbnail = $this->processImg($current_location, $filename, $this->thumb_path, $this->thumb_width, $this->thumb_height, $this->thumb_resize_type, true);

					if($thumbnail === false)
						return false;

					$this->thumb_value = $thumbnail;

					return true;
				}
				
			} else {
				return false;
			}
		
		// nothing submitted, check if it's required
		} else {

			if($this->required){
				$this->error = true;
				$this->error_msg = 'This is a required field';
				return false;
			
			// not required, doesn't matter
			} else {
				return true;
			}
						
		}
	}

	// override the default so we can return thumb info as well (if needed)
	public function getValue(){

		$return = array($this->name => $this->value);
		if($this->make_thumb === true)
			$return[$this->thumb_name] = $this->thumb_value;
		return $return;

	}


	private function ProcessImg($current_location, $filename, $upload_path, $width, $height, $resize_type, $thumbnail = false){
		
		// resize as needed
		if(strtoupper($resize_type)=='FIT'){
			$new_extension = $this->resizeImageFit($current_location, $width, $height);
			if ($new_extension) { // i.e. GIF -> PNG conversion
				$old_extension = array_pop(explode('.', $filename));
				$filebase = basename($filename, '.'.$old_extension);
				$filename = $filebase.'.'.$new_extension;
			}
		} elseif(strtoupper($resize_type)=='EXACT') {
			$new_extension = $this->resizeImageExact($current_location, $width, $height);
			if ($new_extension) { // i.e. GIF -> PNG conversion
				$old_extension = array_pop(explode('.', $filename));
				$filebase = basename($filename, '.'.$old_extension);
				$filename = $filebase.'.'.$new_extension;
			}
		}

		# replace spaces with underscore
		$filename = preg_replace('/\s+/','_',$filename);

		# remove funky characters
		$filename = preg_replace('/[^\w\.\-]+/','',$filename);

		# add "_thumb" to thumbnails
		if ($thumbnail===true) {
			$fileext = explode('.', $filename);
			$fileext = array_pop($fileext);
			$filebase = basename($filename, '.'.$fileext);
			$filename = "{$filebase}_thumb.{$fileext}";
		}

		# if file already exists, figure a new name for this file
		# (i.e., "foobar.pdf"->"foobar_1.pdf", etc.)
		while (is_file($upload_path.$filename)) {
			$fileext = explode('.', $filename);
			$fileext = array_pop($fileext);
			$filebase = basename($filename, '.'.$fileext);
			if (preg_match('/^(.+)_(\d+)$/',$filebase,$matches)) {
				$suffix_digit = $matches[2] + 1;
				$filename = "{$matches[1]}_{$suffix_digit}.{$fileext}";
			} else {
				$filename = "{$filebase}_1.{$fileext}";
			}
		}

		# try to move file
		try{
			if ($thumbnail === true) {
				chmod($current_location, 0644);
				if($move_status = copy($current_location, $upload_path.$filename))
					unlink($current_location);
			} else
				$move_status = move_uploaded_file($current_location, $upload_path.$filename);

			if(!$move_status)
				throw new \Exception("'".$current_location."' could not be moved to '".$upload_path.$filename."'. This is probably because the directory doesn't exist or the web server doesn't have permission to write to it.");

			return $filename;
		
		} catch(\Exception $e){
			$this->error = true;
			$this->error_msg = $this->filename." could not be uploaded at this time, please try again later.";
			error_log($e->getMessage());
			return false;
		}
	}


	/*
	 * ------------ IMAGE RESIZING FUNCTIONS -------------
	*/
	private function resizeImageExact($image_file, $max_w, $max_h){
		list($org_width, $org_height, $org_type) = getImageSize($image_file);

		switch($org_type){
			case IMAGETYPE_JPEG:
				$org_img = imageCreateFromJpeg($image_file);
				if($org_img)
					$thumb = $this->resizeAndCrop($org_img, $max_w, $max_h);
				if($thumb)
					imageJpeg($thumb, $image_file, 90);
				break;
			case IMAGETYPE_PNG:
				$org_img = imageCreateFromPng($image_file);
				// attempt to save full alpha
				imagealphablending($org_img, false);
				imagesavealpha($org_img, true);
				if($org_img)
					$thumb = $this->resizeAndCrop($org_img, $max_w, $max_h);
				if($thumb)
					imagePng($thumb, $image_file);
				break;
			case IMAGETYPE_GIF:
				$org_img = imageCreateFromGif($image_file);
				// attempt to save full alpha
				imagealphablending($org_img, false);
				imagesavealpha($org_img, true);
				if($org_img)
					$thumb = $this->resizeAndCrop($org_img, $max_w, $max_h);
				if($thumb){
					imagePng($thumb, $image_file);
					$new_extension = 'png';
				}
				break;
		}

		imageDestroy($org_img);
		imageDestroy($thumb);

		if(isset($new_extension)) return $new_extension;

	}

	// this function requires GD 2 to run
	private function resizeImageFit($image_file, $max_width, $max_height) {
		list($width, $height, $type) = getImageSize($image_file);

		if (!$max_width)
			$max_width = 1000000;
		if (!$max_height)
			$max_height = 1000000;

		// should we resize?
		if (($width > $max_width || $height > $max_height)) {
			if ($width/$max_width > $height/$max_height) {
				$new_width = $max_width;
				$new_height = $height*($max_width/$width);
			} else {
				$new_width = $width*($max_height/$height);
				$new_height = $max_height;
			}

			$smaller_img = imageCreateTrueColor($new_width, $new_height);

			// attempt to save full alpha
			imagealphablending($smaller_img, false);
			imagesavealpha($smaller_img, true);

			switch ($type) {
				case IMAGETYPE_JPEG:
					$img = imageCreateFromJpeg($image_file);
					if ($img)
						$success = $this->imageCopyResampledAndSharpen($smaller_img, $img, 0, 0, 0, 0, $new_width, $new_height, $width, $height);
					if ($success)
						imageJpeg($smaller_img, $image_file, 90);
					imageDestroy($img);
					imageDestroy($smaller_img);
					break;
				case IMAGETYPE_PNG:
					$img = imageCreateFromPng($image_file);
					if ($img)
						$success = $this->imageCopyResampledAndSharpen($smaller_img, $img, 0, 0, 0, 0, $new_width, $new_height, $width, $height);
					if ($success){
						imagePng($smaller_img, $image_file);
					}
					imageDestroy($img);
					imageDestroy($smaller_img);
					break;
				case IMAGETYPE_GIF:
					$img = imageCreateFromGif($image_file);
					if ($img)
						$success = $this->imageCopyResampledAndSharpen($smaller_img, $img, 0, 0, 0, 0, $new_width, $new_height, $width, $height);
					if ($success) {
						imagePng($smaller_img, $image_file);
						$new_extension = 'png';
					}
					imageDestroy($img);
					imageDestroy($smaller_img);
					break;
			}
		}
		if(isset($new_extension)) return $new_extension;
	}


	/*
		@org_img = img resource at original size
		@w = width it should be after processing
		@h = heigh it should be after processing
	*/
	private function resizeAndCrop($org_img, $w, $h) {
		$org_width = imagesx($org_img);
		$org_height = imagesy($org_img);
		$org_ratio = $org_width/$org_height;

		// taller
		if ($w/$h > $org_ratio) {
			$new_height = $w/$org_ratio;
			$new_width = $w;

		// wider
		} else {
			$new_width = $h*$org_ratio;
			$new_height = $h;
		}

		$x_mid = $new_width/2;  //horizontal middle
		$y_mid = $new_height/2; //vertical middle

		// we need an inbetween image to get it to the right size prior ro cropping
		$process = imagecreatetruecolor(round($new_width), round($new_height));
		// make sure to do regular copy resampled here otherwise sharpen gets applied twice
		imageCopyResampled($process, $org_img, 0, 0, 0, 0, $new_width, $new_height, $org_width, $org_height);

		// now we crop from the process
		$thumb = imagecreatetruecolor($w, $h);
		$this->imageCopyResampledAndSharpen($thumb, $process, 0, 0, ($x_mid-($w/2)), ($y_mid-($h/2)), $w, $h, $w, $h);

		imagedestroy($process);
		return $thumb;
	}


	/*
	 *	@ same as imageCopyResampled (see link on next link)
	 *	applies imageCopyResampled http://us.php.net/imagecopyresampled
	 *	then sharpens via imageConvolution http://us.php.net/manual/en/function.imageconvolution.php
	*/
	private function imageCopyResampledAndSharpen($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h){

		$success = imageCopyResampled($dst_image, $src_image, $dst_x, $dst_y, $src_x, $src_y, $dst_w, $dst_h, $src_w, $src_h);

		if(function_exists("imageconvolution")){
			$matrix = array(
				array( -1, -1, -1 ),
				array( -1, 16, -1 ),
				array( -1, -1, -1 )
			);
			$divisor = 8;
			$offset = 0;
			imageconvolution($dst_image, $matrix, $divisor, $offset);
		}

		return $success;

	}




}
?>
