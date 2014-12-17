(function($){

	$(document).ready(function(){
		
		$('.file-holder').each(function(){
			var eq = 0,
				t = $(this),
				input_holder = t.find('.input-holder'),
				multiple = $(this).hasClass('multiple');

			if(multiple){
				var org = $(this).find('input[type="file"]').clone();
			}

			$('.file-trigger, .list-holder', t).show();
			input_holder.css({
				'opacity': 0,
				'position': 'absolute',
				'left':'-999999px'
			});

			// dialog trigger
			t.on('click', '.file-trigger', function(){
				var file_el;

				if(multiple){
					var file_inputs = input_holder.find('input[type="file"]');
					if(!file_inputs.length){
						file_inputs = org.clone().appendTo(input_holder);
					}

					file_el = file_inputs.last();
					if(file_el[0].files.length > 0){
						// create a new file input and file list
						eq++;
						file_el = org.clone().attr('data-eq', eq).val('').appendTo(input_holder);						
					}
				} else {
					file_el = t.find('input[type="file"]');
				}

				file_el.trigger('click');
				return false;
			});

			// removing for multiples
			t.on('click', '.close', function(e){
				var li = $(this).parents('li'),
					eq = li.attr('data-eq'),
					file = input_holder.find('input[type="file"][data-eq="'+eq+'"]');

				li.remove();
				file.remove();
				
				e.stopPropagation();
				e.preventDefault();
				return false;
			});

			// skip things that don't understand FileList
			if(typeof FileList != 'undefined'){
				t.on('change', 'input[type="file"]', function(e){
					files = $(this)[0].files;
					$list = t.find('.file-list');

					processFiles(files, $list, $(this).data('eq'));
				});

			} else {
				$('input:file', t).change(function(e){
					var $list = t.find('.file-list');
					$list.html('<li class="list-group-item">'+( $(this).val().replace("C:\\fakepath\\", '') )+'</li>');
				});
			}

		});// end foreach

	}); // end domready

	function processFiles(files, $list, eq){
		var image_filter = /image.*/;

		for(var i=0; i<files.length; i++){
			(function (i){ // Loop through our files with a closure so each of our FileReader's are isolated.
				var file = files[i],
					li = $('<li></li>').attr('data-eq', eq).addClass('list-group-item');

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
						});

						li
							.append(newImg)
							.append('<span class="name">'+file.name+'</span>')
							.append('<span class="size">'+Math.round(file.size/1024)+'kb</span>');
						
						$list.append(li);
					};
					reader.readAsDataURL(file);

				} else {
					li
						.append('<span class="name">'+file.name+'</span>')
						.append('<span class="size">'+Math.round(file.size/1024)+'kb</span></li>');
					$list.append(li);
				}

				if($list.parents('.file-holder').hasClass('multiple')){
					li.append('<button type="button" class="close"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>');
				}
			})(i);						
		}
	}

})(jQuery);