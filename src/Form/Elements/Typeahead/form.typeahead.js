(function($){
	$(document).ready(function(){
		$('form.form_class .typeahead_holder').each(function(){
			var datasets = $.parseJSON( $('.datasets', $(this)).text() ),
				input = $('input.typeahead-input', $(this));

			input.typeahead(datasets);
		});
	});
})(jQuery);