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
    
    "src/lvglpp/widgets/animimg/animimg.cpp"
    "src/lvglpp/widgets/arc/arc.cpp"
    "src/lvglpp/widgets/bar/bar.cpp"
    "src/lvglpp/widgets/btnmatrix/btnmatrix.cpp"
    "src/lvglpp/widgets/calendar/calendar.cpp"
    "src/lvglpp/widgets/canvas/canvas.cpp"
    "src/lvglpp/widgets/chart/chart.cpp"
    "src/lvglpp/widgets/checkbox/checkbox.cpp"
    "src/lvglpp/widgets/colorwheel/colorwheel.cpp"
    "src/lvglpp/widgets/dropdown/dropdown.cpp"
    "src/lvglpp/widgets/image/image.cpp"
    "src/lvglpp/widgets/imgbtn/imgbtn.cpp"
    "src/lvglpp/widgets/keyboard/keyboard.cpp"
    "src/lvglpp/widgets/label/label.cpp"
    "src/lvglpp/widgets/led/led.cpp"
    "src/lvglpp/widgets/line/line.cpp"
    "src/lvglpp/widgets/list/list.cpp"
    "src/lvglpp/widgets/menu/menu.cpp"
    "src/lvglpp/widgets/meter/meter.cpp"
    "src/lvglpp/widgets/msgbox/msgbox.cpp"
    "src/lvglpp/widgets/roller/roller.cpp"
    "src/lvglpp/widgets/slider/slider.cpp"
    "src/lvglpp/widgets/span/span.cpp"
    "src/lvglpp/widgets/spinbox/spinbox.cpp"
    "src/lvglpp/widgets/spinner/spinner.cpp"
    "src/lvglpp/widgets/table/table.cpp"
    "src/lvglpp/widgets/tabview/tabview.cpp"
    "src/lvglpp/widgets/textarea/textarea.cpp"
    "src/lvglpp/widgets/tileview/tileview.cpp"
    "src/lvglpp/widgets/win/win.cpp"

	INCLUDE_DIRS
		"src"
    
    REQUIRES main
)
idf_build_set_property(COMPILE_OPTIONS "-Wno-unused-function" APPEND)
