(function($){
	$(document).ready(function(){
		$('form.form_class .selectothertypeahead_holder').each(function(){
			var holder = $(this);

			$('select', this).change(function(){
				if( $('option:selected', this).data('other')==1 ){
					$('.other', holder).slideDown('fast');		
				} else {
					$('.other', holder).hide();
				}
			});

			var datasets = $.parseJSON( $('.datasets', $(this)).text() ),
				input = $('.other input.typeahead-input', $(this));

			input.typeahead(datasets);
		});
	});
})(jQuery);