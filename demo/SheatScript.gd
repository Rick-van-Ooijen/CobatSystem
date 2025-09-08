extends CharSheat


# Called when the node enters the scene tree for the first time.
func _ready():
	var file = FileAccess.open("res://data.txt", FileAccess.READ)
	var content = file.get_as_text()
	self.InitializeValues(content)
	
	self.PrintData()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
