(function($){
	
	$(document).ready(function(){
		$('.phone_holder')
		.on('click', 'input', function(){
			return false;	
		})
		.on('keyup', 'input', function(){
			if( $(this).val().length == $(this).attr('maxlength') ){
				$(this).nextAll('input:eq(0)').focus();
			}
		});
	});

})(jQuery);