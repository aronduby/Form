(function($){
	$(document).ready(function(){
		$('input[name="payment_type"]').change(function(){
			if($(this).is(':checked')){			
				if( $(this).val() == 'credit_card' ){
					$('.payment_type_credit_card').show();
				} else {
					$('.payment_type_credit_card').hide();
				}
			}
		}).change();
		
		// hook the checked class for type radio and label
		$('input.cc_type').change(function(){
			var $label = $('label[for="'+$(this).attr('id')+'"]');
			$(this).parents('ul').find('label').removeClass('checked');
			if($(this).attr('checked') == 'checked')
				$label.addClass('checked');
			else
				$label.removeClass('checked');
		}).change();
		
		// on keyup for card number figure what the card type is
		$('input.cc_card_number').on('keyup', function(){
			var cc_type = calcCardType($(this).val());
			if(cc_type != undefined){
				$(this).parents('.credit_card_holder').find('input.cc_type[value="'+cc_type+'"]').attr('checked','checked').change();
			} else {
				$(this).parents('.credit_card_holder').find('input.cc_type[checked="checked"]').removeAttr('checked').change();
			}
		}).triggerHandler('keyup');

		// nice tooltip on hover of cvv2 abbr
		$('.cvv2_holder .description abbr').each(function(){
			
			var content = $(this).attr('title');
			$(this).removeAttr('title');
			$(this).append('<div class="cvv2_tooltip"><p>'+content+'</p></div>');
		});



		function calcCardType(num){
			if(num[0] == 4)
				return 'visa';
			else if(num.substr(0,4)=='6011')
				return 'discover';
			else if(num.match(/^5[1-5]/))
				return 'mastercard';
			else if(num.match(/^3[47]/))
				return 'amex';
		}
	});
})(jQuery);