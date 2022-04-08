idf_component_register(
	SRCS
    "src/lvgl/core/display.cpp"
    "src/lvgl/core/event.cpp"
    "src/lvgl/core/indev.cpp"
    "src/lvgl/core/object.cpp"
  
    "src/lvgl/draw/desc.cpp"
    "src/lvgl/draw/image.cpp"

    "src/lvgl/font/font.cpp"
    
    "src/lvgl/misc/anim.cpp"
    "src/lvgl/misc/area.cpp"
    "src/lvgl/misc/color.cpp"
    "src/lvgl/misc/fs.cpp"
    "src/lvgl/misc/style.cpp"
    "src/lvgl/misc/timer.cpp"
  
    "src/lvgl/widgets/animimg.cpp"
    "src/lvgl/widgets/arc.cpp"
    "src/lvgl/widgets/bar.cpp"
    "src/lvgl/widgets/btnmatrix.cpp"
    "src/lvgl/widgets/calendar.cpp"
    "src/lvgl/widgets/canvas.cpp"
    "src/lvgl/widgets/chart.cpp"
    "src/lvgl/widgets/checkbox.cpp"
    "src/lvgl/widgets/colorwheel.cpp"
    "src/lvgl/widgets/dropdown.cpp"
    "src/lvgl/widgets/image.cpp"
    "src/lvgl/widgets/imgbtn.cpp"
    "src/lvgl/widgets/keyboard.cpp"
    "src/lvgl/widgets/label.cpp"
    "src/lvgl/widgets/led.cpp"
    "src/lvgl/widgets/line.cpp"
    "src/lvgl/widgets/list.cpp"
    "src/lvgl/widgets/menu.cpp"
    "src/lvgl/widgets/meter.cpp"
    "src/lvgl/widgets/msgbox.cpp"
    "src/lvgl/widgets/roller.cpp"
    "src/lvgl/widgets/slider.cpp"
    "src/lvgl/widgets/span.cpp"
    "src/lvgl/widgets/spinbox.cpp"
    "src/lvgl/widgets/table.cpp"
    "src/lvgl/widgets/tabview.cpp"
    "src/lvgl/widgets/textarea.cpp"
    "src/lvgl/widgets/tileview.cpp"
    "src/lvgl/widgets/win.cpp"

	INCLUDE_DIRS
		"src"
    
    REQUIRES main
)
