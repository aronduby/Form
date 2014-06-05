(function($){
	$.fn.form = function(){
		var form = {
			$form: false,
			
			elements: {},
			processed: false,
			errors: false,
			display_order: [],
			dom_id: null,
			actions: null,
			method: 'post',
			allow_js_to_override_definition: false,
			autocomplete: null,
			debug: false,
			skip_hash_check: false,
			element_counters: {},
			additional_js: null,
			additional_css: null,

			init: function(){
				
				this.$form = $('#'+this.dom_id);
				this.$form.on('submit', this.submit);
				
				

			},
			// used to ajax in form elements
			// placement == BEFORE || AFTER
			// placement name == the name of the element to display BEFORE || AFTER
			add: function(opts, placement, placement_name, callback){
				$.getJSON('ajax_add_form_element.php', 
					opts, 
					function(d){

						var key = d.name,
							placement_name_key,
							$p;

						if(form.elements[key] != 'undefined'){
							key = key+'_'+(++form.element_counters[key]);
						} else {
							form.element_counters[$key] = 0;
							key = key+'_'+form.element_counters[key];
						}
						form.elements[key] = d;

						// handle some defaults
						if(placement == null)
							placement = 'BEFORE';
						if(placement_name == null)
							placement_name = 'submit';

						// display order uses the keys made from appending the count of that name to the supplied name
						// so if placement is before, append 0 for display
						// otherwise append the current element count
						if(placement == 'BEFORE'){
							placement_name_key = placement_name+'_0';
						} else {
							placement_name_key = placement_name+'_'+form.element_counters[placement_name];
						}

						// add it to the display order
						var index_of_pn = $.inArray(placement_name_key, form.display_order);
						if(index_of_pn < 0)
							index_of_pn = $.inArray('submit_0', form.display_order);
						
						$p = form.$form.find('#'+placement_name);

						if(placement.toUpperCase() == 'BEFORE'){
							form.display_order.splice(index_of_pn, 0, key);
							$(d.content).insertBefore($p);
						} else {
							form.display_order.splice(index_of_pn+1, 0, key);
							$(d.content).insertAfter($p);
						}
						
						if(typeof callback == 'function' )
							callback.apply(form, [d]);

						delete( form.elements[key].content );
					}
				);
			},

			remove: function(){},

			// scoped to the form
			submit: function(){
				$('input[type="submit"]', $(this)).val('working').removeClass('action').attr('disabled', 'disabled');
				$('body').addClass('wait');
				// $('#form_definition', $(this)).val( $.toJSON( form ) );
				
				// console.log( $.toJSON( form ) );
				// return false;
			}
		};

		var definition = {}, //$.parseJSON($('.json.form_definition', this).text()),
			form = $.extend(form, definition);

		form.init();

		return form;
	}
})(jQuery);

$(document).ready(function(){
	
	var jqforms = {};
	$('form.form_class').each(function(){
		jqforms[$(this).attr('id')] = $(this).form();
	});

	$('.inline-elements')
	.on('click', function(){
		$(this).find('input:eq(0)').focus();
	})
	.on('focus', 'input, select', function(){
		$(this).parents('.inline-elements').addClass('focus');
		return false;
	})
	.on('blur', 'input, select', function(){
		$(this).parents('.inline-elements').removeClass('focus');
		return false;
	})
	.on('click', 'select', function(){
		return false;
	})


	// toggles
	$('form.form_class [data-toggle_el]').each(function(){
		var self = $(this),
			el = $(this).parents('.form_class').find('[name="'+$(this).data('toggle_el')+'"]'),
			val = $(this).data('toggle_val');
		
		el.on('change', function(){
			if($(this).attr('type') == 'radio' || $(this).attr('type') == 'checkbox'){
				if($(this).is(':checked') && $(this).val() == val)
					self.show();
				else
					self.hide();
			} else {
				if($(this).val() == val)
					self.show();
				else
					self.hide();
			}
			
			
		}).triggerHandler('change');
	});
	
});



// jquery json from http://code.google.com/p/jquery-json/
(function($){var escapeable=/["\\\x00-\x1f\x7f-\x9f]/g,meta={'\b':'\\b','\t':'\\t','\n':'\\n','\f':'\\f','\r':'\\r','"':'\\"','\\':'\\\\'};$.toJSON=typeof JSON==='object'&&JSON.stringify?JSON.stringify:function(o){if(o===null){return'null';}
var type=typeof o;if(type==='undefined'){return undefined;}
if(type==='number'||type==='boolean'){return''+o;}
if(type==='string'){return $.quoteString(o);}
if(type==='object'){if(typeof o.toJSON==='function'){return $.toJSON(o.toJSON());}
if(o.constructor===Date){var month=o.getUTCMonth()+1,day=o.getUTCDate(),year=o.getUTCFullYear(),hours=o.getUTCHours(),minutes=o.getUTCMinutes(),seconds=o.getUTCSeconds(),milli=o.getUTCMilliseconds();if(month<10){month='0'+month;}
if(day<10){day='0'+day;}
if(hours<10){hours='0'+hours;}
if(minutes<10){minutes='0'+minutes;}
if(seconds<10){seconds='0'+seconds;}
if(milli<100){milli='0'+milli;}
if(milli<10){milli='0'+milli;}
return'"'+year+'-'+month+'-'+day+'T'+
hours+':'+minutes+':'+seconds+'.'+milli+'Z"';}
if(o.constructor===Array){var ret=[];for(var i=0;i<o.length;i++){ret.push($.toJSON(o[i])||'null');}
return'['+ret.join(',')+']';}
var name,val,pairs=[];for(var k in o){type=typeof k;if(type==='number'){name='"'+k+'"';}else if(type==='string'){name=$.quoteString(k);}else{continue;}
type=typeof o[k];if(type==='function'||type==='undefined'){continue;}
val=$.toJSON(o[k]);pairs.push(name+':'+val);}
return'{'+pairs.join(',')+'}';}};$.evalJSON=typeof JSON==='object'&&JSON.parse?JSON.parse:function(src){return eval('('+src+')');};$.secureEvalJSON=typeof JSON==='object'&&JSON.parse?JSON.parse:function(src){var filtered=src.replace(/\\["\\\/bfnrtu]/g,'@').replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g,']').replace(/(?:^|:|,)(?:\s*\[)+/g,'');if(/^[\],:{}\s]*$/.test(filtered)){return eval('('+src+')');}else{throw new SyntaxError('Error parsing JSON, source is not valid.');}};$.quoteString=function(string){if(string.match(escapeable)){return'"'+string.replace(escapeable,function(a){var c=meta[a];if(typeof c==='string'){return c;}
c=a.charCodeAt();return'\\u00'+Math.floor(c/16).toString(16)+(c%16).toString(16);})+'"';}
return'"'+string+'"';};})(jQuery);