$(document).ready(function(){

	$('.form_class').on('change', 'select', function(){
		console.log( $('option:selected', this) );
	});

});