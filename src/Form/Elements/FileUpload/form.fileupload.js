(function($){

	$(document).ready(function(){
		
		$('.form_class .file_holder').each(function(){
			var eq = 1,
				t = $(this),
				multiple = $(this).hasClass('multiple');

			if(multiple){
				var org = $(this).find('input[type="file"]').clone();
			}

			$('.file_trigger, .file_list', t).show();
			$('input:file', t).css({
				'opacity':0,
				'position': 'absolute',
				'left':'-999999px'
			});

			// dialog trigger
			t.on('click', '.file_trigger', function(){
				var file_el;

				if(multiple){
					var file_inputs = t.find('input[type="file"]');
					if(!file_inputs.length){
						file_inputs = org.clone().appendTo(t);
					}

					file_el = file_inputs.last();
					if(file_el[0].files.length > 0){
						// create a new file input and file list
						file_el = org.clone().attr('data-eq', eq).val('').appendTo(t);
						t.find('.list_holder').append('<ul class="file_list" data-eq="'+eq+'"></ul>');
						eq++;
					}
				} else {
					file_el = t.find('input[type="file"]');
				}

				file_el.trigger('click');
				return false;
			});

			// removing for multiples
			t.on('click', '.remove a', function(e){
				var ul = $(this).parents('ul'),
					eq = ul.attr('data-eq'),
					file = t.find('input[type="file"][data-eq="'+eq+'"]');

				ul.remove();
				file.remove();

				if($('.list_holder', t).is(':empty')){
					$('.list_holder', t).append('<ul class="file_list" data-eq="0"></ul>');
				}
				
				e.stopPropagation();
				e.preventDefault();
				return false;
			});

			// skip things that don't understand FileList
			if(typeof FileList != 'undefined'){
				t.on('change', 'input[type="file"]', function(e){
					files = $(this)[0].files;
					$list = t.find('.file_list[data-eq="'+$(this).attr('data-eq')+'"]');

					processFiles(files, $list);
				});

			} else {
				$('input:file', t).change(function(e){
					var $list = t.find('.file_list[data-eq="'+$(this).attr('data-eq')+'"]');
					$list.html('<li>'+( $(this).val().replace("C:\\fakepath\\", '') )+'</li>');
				});
			}

		});// end foreach

	}); // end domready

	function processFiles(files, $list){
		var image_filter = /image.*/;
		$list.empty();

		for(var i=0; i<files.length; i++){
			(function (i){ // Loop through our files with a closure so each of our FileReader's are isolated.
				var file = files[i];

				// safari catch, name = fileName, size = fileSize, no type
				if(typeof file.fileName != 'undefined'){
					file.name = file.fileName;
					file.size = file.fileSize;
				}
				
				// safari doesn't do file type
				if(typeof file.type != 'undefined' && file.type.match(image_filter)) {
					var $img = $('<img src="" class="upload_pic" title="" alt="" />'),
						reader = new FileReader();

					reader.onload = function (event) {
						var newImg = $img.clone().attr({
							src: event.target.result,
							title: (files.name),
							alt: (files.name)
						})
						$list.append($('<li></li>').append(newImg).append('<span class="name">'+file.name+'</span> <span class="size">'+Math.round(file.size/1024)+'kb</span>'));
					};
					reader.readAsDataURL(file);

				} else {
					$list.append('<li><span class="name">'+file.name+'</span ><span class="size">'+Math.round(file.size/1024)+'kb</span></li>');
				}
			})(i);						
		}

		if($list.parents('.file_holder').hasClass('multiple')){
			$list.append('<li class="remove"><a href="#">&times;</a></li>');
		}
	}

})(jQuery);