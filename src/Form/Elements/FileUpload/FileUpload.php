<?php

namespace Form\Elements;

class FileUpload extends Input{

	public $class_type = 'fileupload';	
	public $upload_path;
	public $mime_type;
	public $display; // used to display an image as the default
	public $multiple = false;
	public $accept;

	public $additional_js = array('form.fileupload.js');
	public $additional_css = ['form.fileupload.css'];

	protected $template = 'fileupload.inc';
	protected $max_file_size;

	public function __construct($opts, $form){
		parent::__construct($opts, $form);
		
		$this->max_file_size = sscanf(ini_get('upload_max_filesize'), "%dM");
		$this->max_file_size = array_pop($this->max_file_size);
		$this->max_file_size = $this->max_file_size*1024*1024;

		if(!isset($this->upload_path))
			throw new \Exception('Upload path not set for '.get_class($this).' '.$this->name);
	}


	public function process(){

		$files = $this->rearrange($_FILES[$this->name]);

		foreach($files as $file){
			if($file['error'] !== 4){

				try{
					$this->checkForUploadErrors($file);
					
					if(isset($this->accept))
						$this->checkFileType($file);
					
					$new_file = $this->renameAndMoveFile($file);
					if($this->multiple)
						$this->value[] = $new_file;
					else
						$this->value = $new_file;

				}catch(\Exception $e){
					$this->error = true;
					$this->error_msg = $e->getMessage();
					return false;
				}

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
	}

	protected function checkForUploadErrors(&$file){
		
		if ($file['error']){
			switch($file['error']){
				case 1: 
				case 2:
					throw new \Excpetion("File '".$file['name']."' is too big; the maximum allowed file size is ".($this->max_file_size/1024)."kb.");
					break;
				case 3: 
					throw new \Exception("The file '".$file['name']."' was only partially uploaded.");
					break;
			}
		}
		return true;
	}

	protected function checkFileType(&$file){		
		if(!in_array($file['type'], $this->accept))
			throw new \Exception("File '".$file['name']."' is not an allowed type");
	}

	protected function rearrange( $arr ){
		$new = [];
		$i = 0;
		foreach( $arr as $key => $all ){
			if(is_array($all)){
				foreach( $all as $i => $val ){
					$new[$i][$key] = $val;   
				}
			} else {
				$new[$i][$key] = $all;
			}
		}
		return $new;
	}


	protected function renameAndMoveFile(&$file){
		# replace spaces with underscore
		$filename = preg_replace('/\s+/','_',$file['name']);

		# remove funky characters
		$filename = preg_replace('/[^\w\.\-]+/','',$filename);

		# if file already exists, figure a new name for this file 
		# (i.e., "foobar.pdf"->"foobar_1.pdf", etc.)
		while (is_file($this->upload_path.$filename)) {
			$fileext = array_pop(explode('.', $filename));
			$filebase = basename($filename, '.'.$fileext);
			if (preg_match('/^(.+)_(\d+)$/',$filebase,$matches)) {
				$suffix_digit = $matches[2] + 1;
				$filename = "{$matches[1]}_{$suffix_digit}.{$fileext}";
			} else {
				$filename = "{$filebase}_1.{$fileext}";
			}
		}

		# try to move file
		if(!move_uploaded_file($file['tmp_name'], $this->upload_path.$filename))
			throw new \Exception("'".$file['tmp_name']."' could not be moved to '".$this->upload_path.$filename."'. This is probably because the directory doesn't exist or the web server doesn't have permission to write to it.");

		return $filename;
	}

}
?>
