extends Node

var Agones = load("res://bin/agones.gdns").new()

func _ready():
	if Agones.connect():
		Agones.ready()

func _exit_tree():
	Agones.shutdown()

func _on_HealthTimer_timeout():
	Agones.health()
