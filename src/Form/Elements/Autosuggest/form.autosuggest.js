(function($){
	
	$(document).ready(function(){
		$('.autosuggest_holder').each(function(){
			var $this = $(this),
				available_options = $.parseJSON($this.find('.options').text()),
				selected_options = $.parseJSON($this.find('.selected').text()),
				input = $this.find('input.as-input');

			input.autoSuggest(available_options, {
				startText: 'begin typing...',
				preFill: selected_options,
				selectedItemProp: 'label',
				selectedValuesProp: 'value',
				searchObjProps: 'label',
				neverSubmit: true,
				asHtmlID: input.attr('name')+'_values'
			});
		});

		$('.autosuggest_holder .description a.prefill').click(function(){			
			var d = {
				'label': $(this).text(),
				'value': $(this).data('id')
			}
			$(this).parents('.autosuggest_holder').find('input.as-input').trigger('addASItem', d);
			return false;
		});

	});

})(jQuery);