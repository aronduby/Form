<?php
require 'vendor/autoload.php';

$form = new Form\Form();
//$form->class = 'breaks';
$form
	->add('Address', ['label'=>"Address", 'description'=>"Your Address", 'required'=>true])
	->add('Autosuggest', ['label'=>"Autosuggest", 'description'=>"Autosuggest", 'required'=>true, 'options'=>["hello", "world"]])
	->add('Button', ['label'=>"Button", 'description'=>"Button", 'required'=>true, 'value'=>"Random Button"])
	->add('Captcha', [
		'label'=>"Captcha", 
		'description'=>"Captcha", 
		'required'=>true, 
		'public_key' => "6LdmjP0SAAAAAEHQ_dYoS-aJeFQfyrr_wbyyBFO3",
		'private_key' => "6LdmjP0SAAAAAAe3UE-QPa58gP5Ic38TtAGEjpEr"
	])
	->add('Checkbox', ['label'=>"Checkbox", 'description'=>"Checkbox", 'required'=>true, 'options'=>[1,2,3,4,5]])
	->add('Checkbox', ['label'=>"Checkbox", 'description'=>"Checkbox", 'required'=>true, 'options'=>[1,2,3,4,5], 'inline'=>true])
	->add('CreditCard', ['label'=>"CreditCard", 'description'=>"CreditCard", 'required'=>true])
	->add('Date', ['label'=>"Date", 'description'=>"Date", 'required'=>true])
	->add('DateSelect', ['label'=>"DateSelect", 'description'=>"DateSelect", 'required'=>true])
	->add('Time', ['label'=>"Time", 'description'=>"Time", 'required'=>true])
	->add('TimeSelect', ['label'=>"TimeSelect", 'description'=>"TimeSelect", 'required'=>true])
	->add('DateTime', ['label'=>"DateTime", 'description'=>"DateTime", 'required'=>true])
	->add('Email', ['label'=>"Email", 'description'=>"Email", 'required'=>true])
	->add('Fieldset', ['legend'=>"Fieldset"])
		->add('Text', ['label'=>"Text In Fieldset", 'required'=>true])
	->end()
	->add('FileUpload', ['label'=>"FileUpload", 'description'=>"FileUpload", 'required'=>true, 'upload_path'=>"/tmp", 'multiple'=>true])
	->add('Hidden', ['label'=>"Hidden", 'description'=>"Hidden", 'required'=>true])
	->add('ImageUpload', ['label'=>"ImageUpload", 'description'=>"ImageUpload", 'required'=>true, 'upload_path'=>"/tmp"])
	->add('Name', ['label'=>"Name", 'description'=>"Name", 'required'=>true])
	->add('Number', ['label'=>"Number", 'description'=>"Number", 'required'=>true])
	->add('Password', ['label'=>"Password", 'description'=>"Password", 'required'=>true, 'confirm'=>true])
	->add('Phone', ['label'=>"Phone", 'description'=>"Phone", 'required'=>true])
	->add('Radio', ['name'=>"radio", 'label'=>"Radio", 'description'=>"Radio", 'required'=>true, 'options'=>['a','b','c','d']])
	->add('Radio', ['name'=>"radio-inline", 'label'=>"Radio", 'description'=>"Radio", 'required'=>true, 'options'=>['a','b','c','d'], 'inline'=>true])
	->add('Select', ['label'=>"Select", 'description'=>"Select", 'required'=>true, 'options'=>['a','b','c','d']])
	->add('StateSelect', ['label'=>"StateSelect", 'description'=>"StateSelect", 'required'=>true])
	->add('Text', ['label'=>"Text", 'description'=>"Text", 'required'=>true])
	->add('Textarea', ['label'=>"Textarea", 'description'=>"Textarea", 'required'=>true])
	->add('Submit', ['label'=>"Submit", 'description'=>"Submit", 'required'=>true]);
?>
<!doctype HTML>
<html>
<head>
	<title>All Inputs</title>
	<link rel="stylesheet" href="bootstrap/css/bootstrap.min.css" />
	<link rel="stylesheet" href="bootstrap/css/bootstrap-theme.min.css" />
	<?php
	foreach($form->additional_css as $href){
		print '<link rel="stylesheet" href="'.$href.'" />';
	}
	?>

	<script src="//code.jquery.com/jquery-2.1.1.min.js"></script>
	<?php
	foreach($form->additional_js as $src){
		print '<script src="'.$src.'"></script>';
	}
	?>
</head>
<body>
	<?php
	print $form->output();
	?>
</body>
</html>