$(document).ready(function(){

	$('.form_class select').on('change', function(){
		if( $('option:selected', this).is('[data-placeholder]') )
			$(this).addClass('placeholder_selected');
		else
			$(this).removeClass('placeholder_selected');
	}).change();

});