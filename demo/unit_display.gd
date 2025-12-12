extends Control




func _process(delta):
	
	get_child(0).text = get_parent().PrintData()
	
	pass
