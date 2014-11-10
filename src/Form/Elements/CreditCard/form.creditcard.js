(function($){
	$(document).ready(function(){
		
		// on keyup for card number figure what the card type is
		$('input.cc_card_number').on('keyup', function(){
			var cc_type = calcCardType($(this).val());

			$(this).parents('.credit-card-holder').find('.cc-type').attr('data-card-type', cc_type);
		}).triggerHandler('keyup');

		
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