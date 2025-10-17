extends CobatManager


# Called when the node enters the scene tree for the first time.
func _ready():
	
	AddUnit(get_parent().get_child(0))
	
	
	var file = FileAccess.open("res://attack.txt", FileAccess.READ)
	var content = file.get_as_text()
	self.RunSequence(content)
	pass # Replace with function body.

	self.ActivateTrigger("sa")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
