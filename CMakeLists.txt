idf_component_register(
	SRCS
    "src/lvglpp/core/display.cpp"
    "src/lvglpp/core/event.cpp"
    "src/lvglpp/core/indev.cpp"
    "src/lvglpp/core/object.cpp"
    "src/lvglpp/core/group.cpp"
    "src/lvglpp/core/theme.cpp"
  
    "src/lvglpp/draw/desc.cpp"
    "src/lvglpp/draw/image.cpp"
    "src/lvglpp/draw/mask.cpp"

    "src/lvglpp/font/font.cpp"
    
    "src/lvglpp/misc/anim.cpp"
    "src/lvglpp/misc/area.cpp"
    "src/lvglpp/misc/color.cpp"
    "src/lvglpp/misc/fs.cpp"
    "src/lvglpp/misc/style.cpp"
    "src/lvglpp/misc/timer.cpp"
  
    "src/lvglpp/widgets/animimg.cpp"
    "src/lvglpp/widgets/arc.cpp"
    "src/lvglpp/widgets/bar.cpp"
    "src/lvglpp/widgets/btnmatrix.cpp"
    "src/lvglpp/widgets/calendar.cpp"
    "src/lvglpp/widgets/canvas.cpp"
    "src/lvglpp/widgets/chart.cpp"
    "src/lvglpp/widgets/checkbox.cpp"
    "src/lvglpp/widgets/colorwheel.cpp"
    "src/lvglpp/widgets/dropdown.cpp"
    "src/lvglpp/widgets/image.cpp"
    "src/lvglpp/widgets/imgbtn.cpp"
    "src/lvglpp/widgets/keyboard.cpp"
    "src/lvglpp/widgets/label.cpp"
    "src/lvglpp/widgets/led.cpp"
    "src/lvglpp/widgets/line.cpp"
    "src/lvglpp/widgets/list.cpp"
    "src/lvglpp/widgets/menu.cpp"
    "src/lvglpp/widgets/meter.cpp"
    "src/lvglpp/widgets/msgbox.cpp"
    "src/lvglpp/widgets/roller.cpp"
    "src/lvglpp/widgets/slider.cpp"
    "src/lvglpp/widgets/span.cpp"
    "src/lvglpp/widgets/spinbox.cpp"
    "src/lvglpp/widgets/spinner.cpp"
    "src/lvglpp/widgets/table.cpp"
    "src/lvglpp/widgets/tabview.cpp"
    "src/lvglpp/widgets/textarea.cpp"
    "src/lvglpp/widgets/tileview.cpp"
    "src/lvglpp/widgets/win.cpp"

	INCLUDE_DIRS
		"src"
    
    REQUIRES main
)
