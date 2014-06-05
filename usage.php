<?php
try{
	//submitting and posting a story
	$form = new Form\Form('story_submit_frm','stories-submit.php');
	$form
		->add('text', array('name'=>"title", 'label'=>"Title of the Story", 'required'=>true))
		->add('radio', array(
			'name' => "section", 
			'label' => "Program this applies to",
			'required' => true,
			'options' => array(
				'Foster Grandparents' => "Foster Grandparents",
				'Senior Companions' => "Senior Companions"
			)))
		->add('text', array('name'=>"name", 'label'=>"Name of the person in the story", 'required'=>true))
		->add('text', array(
				'name'=>"location", 
				'label'=>"Location of the story", 
				'description'=>"ie. Gratiot County, Mt. Pleasant"
			))
		->add('imageupload', array(
				'name' => "photo",
				'label' => "Upload a photo for this story",
				'upload_path' => "/wip/mafgscp/uploads/images/stories_of_service/",
				'width' => 300,
				'make_thumb' => true,
				'thumb_name' => "thumb",
				'thumb_width' => 96,
				'thumb_height' => 96,
				'thumb_resize_type' => "exact"
			))
		->add('textarea', array('name'=>"story", 'label'=>"The story", 'required'=>true))
		->add('email', array(
				'name'=>"submitted_by", 
				'label'=>"Your email address", 
				'required'=>true, 
				'description'=>"Only used if more information is needed for the story"
			))
		->add('captcha', array('js_options'=>array('theme'=>"clean"), 'label'=>"Prove you're human"))
		->add('submit', array('ignore'=>true, 'class'=>"action", 'value'=>"Submit Story"));

	if($form->hasBeenSubmitted()){
		
		if($form->process()){
			// everything is good, do what we need to do with the data
			$values = $form->getValues();
			if(DB::insertOrUpdate('story_of_service', $values, 'story_id')){

				$p = Page::getPageContentForUrl('stories-submit-success');
				print $p['content'];

				$editors = MemberController::getMembersByRole('sos_editor');
				$emails = array();
				foreach($editors as $r){
					$emails[] = $r->email;
				}

				$subject = "New Story of Service Submitted";
				$msg = "New story of service has been submitted, heres all the info\n\n".print_r($values, true);
				mail(implode(', '$emails), $subject, $msg, "-f".DEV_EMAIL);

			} else {
				$p = Page::getPageContentForUrl('stories-submit-error');
				print $p['content'];
				print $form->output();
			}


		} else {
			// something is wacked, output the form again
			$p = Page::getPageContentForUrl('stories-submit-error');
			print $p['content'];
			print $form->output();
		}

	} else {
		$p = Page::getPageContentForUrl('stories-submit');
		print $p['content'];
		print $form->output();
	}

} catch( Exception $e){
	print '<p>'.$e->getMessage().'</p>';
	print_p($e->getTrace());
}
?>