# A C++ wrapper for LVGL

This package contains a rather bushy wrapper for LVGL. I originally needed to program a simple user interface, but I didn't want to write a GUI framework from scratch, and found LVGL rather nice. Only that it's written in C. So I started writing C++ classes for the part of the code I wanted to use, and then it got out of control. Now most of the library has some kind of wrapper class provided, although most of them haven't been tested yet (they compile).

This is a work in progress. I will likely improve things as I use it, which will take between one day and forever. I of course welcome any contribution.

Note that I'm not part of the LVGL team. If you have requests related to LVGL itself, please rather ask them.

## Structure

I tried to mirror the directory structure of LVGL to some degree (with exceptions with *extra*, *hal* directories). A number of types that are defined in multiple files are compiled together as one (e.g. style, image, draw). I've put all the widgets (include extra ones) in the *widgets* directory.

My point was to provide functions that take a certain LVGL object type as first argument as a class method. For instance, all functions taking a `lv_obj_t*` as first argument end up as methods of the `Object` class. I tried to replace raw pointer args either with a C++ class instance passed by reference or a smart pointer.

There is a template class in *lv_wrapper.h*, `PointerWrapper<lv_class, lv_deleter>`, to facilitate encapsulation. It stores a `unique_ptr` of type `lv_class` with custom deleter function `lv_deleter`. A number of LVGL types have an associated deleter function, which can be provided there. For widgets, there's a template class called `Widget<lv_allocator>` that provides a constructor to nest objects.

Here is a list of classes with the corresponding link to LVGL:
| Class | File | Wrapped type | LVGL file(s) |
|-------|------|-----------|--------------|
| `Display` | *core/display.h* | `lv_disp_t`<br/>`lv_disp_drv_t` | *hal/lv_hal_disp.h*<br/>*core/lv_disp.h* |
| `Event` | *core/event.h* | `lv_event_t` | *core/lv_event.h* |
| `Group` | *core/group.h* | `lv_group_t` | *core/lv_group.h* |
| `InputDevice`<br/>`PointerInputDevice`<br/>`ButtonInputDevice`<br/>`KeypadInputDevice`<br/>`EncoderInputDevice` | *core/indev.h* | `lv_indev_t`<br/>`lv_indev_drv_t` | *hal/lv_hal_indev.h*<br/>*core/lv_indev.h* |
| `Object` | *core/object.h* | `lv_obj_t` | *core/lv_obj.h*<br/>*core/lv_obj_draw.h*<br/>*core/lv_obj_pos.h*<br/>*core/lv_scroll.h*<br/>*core/lv_obj_style.h*<br/>*core/lv_obj_tree.h* |
| `RectangleDrawDescriptor` | *draw/desc.h* | `lv_draw_rect_dsc_t` | *draw/lv_draw_rect.h* |
| `LabelDrawDescriptor` | *draw/desc.h* | `lv_draw_label_dsc_t` | *draw/lv_draw_label.h* |
| `ImageDrawDescriptor` | *draw/desc.h* | `lv_draw_img_dsc_t` | *draw/lv_draw_img.h* |
| `LineDrawDescriptor` | *draw/desc.h* | `lv_draw_line_dsc_t` | *draw/lv_draw_line.h* |
| `ArcDrawDescriptor` | *draw/desc.h* | `lv_draw_arc_dsc_t` | *draw/lv_draw_arc.h* |
| `ImageDecoder` | *draw/image.h* | `lv_img_decoder_dsc_t` | *draw/lv_img_decoder.h* |
| `ImageHeader` | *draw/image.h* | `lv_img_header_t` | *draw/lv_img_buf.h* |
| `ImageDescriptor` | *draw/image.h* | `lv_img_dsc_t` | *draw/lv_img_buf.h* |
| `Font` | *font/font.h* | `lv_font_t` | *font/lv_font.h* |
| `Animation` | *misc/anim.h* | `lv_anim_t` | *misc/lv_anim.h* |
| `AnimationTimeline` | *misc/anim.h* | `lv_anim_timeline_t` | *misc/lv_anim_timeline.h* |
| `Area` | *misc/area.h* | `lv_area_t` | *misc/lv_area.h* |
| `Color` | *misc/color.h* | `lv_color_t` | *misc/lv_color.h* |
| `FileSystem` | *misc/fs.h* | `lv_fs_t` | *misc/lv_fs.h* |
| `File` | *misc/fs.h* | `lv_fs_file_t` | *misc/lv_fs.h* |
| `Directory` | *misc/fs.h* | `lv_fs_dir_t` | *misc/lv_fs.h* |
| `Style` | *misc/style.h* | `lv_style_t` | *misc/lv_style.h*<br/>*misc/lv_style_gen.h* |
| `Timer` | *misc/timer.h* | `lv_timer_t` | *misc/lv_timer.h* |
| `AnimatedImage` | *widgets/animimg.h* | `lv_animimg_t` | *extra/widgets/animimg/lv_animimg.h* |
| `Arc` | *widgets/arc.h* | `lv_arc_t` | *widgets/lv_arc.h* |
| `Bar` | *widgets/bar.h* | `lv_bar_t` | *widgets/lv_bar.h* |
| `ButtonMatrix` | *widgets/btnmatrix.h* | `lv_btnmatrix_t` | *widgets/lv_btnmatrix.h* |
| `Button` | *widgets/button.h* | `lv_btn_t` | *widgets/lv_btn.h* |
| `Calendar` | *widgets/calendar.h* | `lv_calendar_t` | *extra/widgets/calendar/lv_calendar.h* |
| `Canvas` | *widgets/canvas.h* | `lv_canvas_t` | *widgets/lv_canvas.h* |
| `Chart` | *widgets/chart.h* | `lv_chart_t` | *extra/widgets/chart/lv_chart.h* |
| `Checkbox` | *widgets/checkbox.h* | `lv_checkbox_t` | *widgets/lv_checkbox.h* |
| `ColorWheel` | *widgets/colorwheel.h* | `lv_colorwheel_t` | *extra/widgets/colorwheel/lv_colorwheel.h* |
| `Dropdown` | *widgets/dropdown.h* | `lv_dropdown_t` | *widgets/lv_dropdown.h* |
| `Image` | *widgets/image.h* | `lv_image_t` | *widgets/lv_img.h* |
| `ImageButton` | *widgets/imgbtn.h* | `lv_imgbtn_t` | *extra/widgets/imgbtn/lv_imgbtn.h* |
| `Keyboard` | *widgets/keyboard.h* | `lv_keyboard_t` | *extra/widgets/keyboard/lv_keyboard.h* |
| `Label` | *widgets/label.h* | `lv_label_t` | *widgets/lv_label.h* |
| `Led` | *widgets/led.h* | `lv_led_t` | *extra/widgets/led/lv_led.h* |
| `Line` | *widgets/line.h* | `lv_line_t` | *widgets/lv_line.h* |
| `List` | *widgets/list.h* | `lv_list_t` | *extra/widgets/list/lv_list.h* |
| `Menu` | *widgets/menu.h* | `lv_menu_t` | *extra/widgets/menu/lv_menu.h* |
| `Meter` | *widgets/meter.h* | `lv_meter_t` | *extra/widgets/meter/lv_meter.h* |
| `MessageBox` | *widgets/msgbox.h* | `lv_msgbox_t` | *extra/widgets/msgbox/lv_msgbox.h* |
| `Roller` | *widgets/roller.h* | `lv_roller_t` | *widgets/lv_roller.h* |
| `Slider` | *widgets/slider.h* | `lv_slider_t` | *widgets/lv_slider.h* |
| `Span` | *widgets/span.h* | `lv_span_t` | *extra/widgets/span/lv_span.h* |
| `Spinbox` | *widgets/spinbox.h* | `lv_spinbox_t` | *extra/widgets/spinbox/lv_spinbox.h* |
| `Spinner` | *widgets/spinner.h* | `lv_spinner_t` | *extra/widgets/spinner/lv_spinner.h* |
| `Switch` | *widgets/switch.h* | `lv_switch_t` | *widgets/lv_switch.h* |
| `Table` | *widgets/table.h* | `lv_table_t` | *widgets/lv_table.h* |
| `Tabview` | *widgets/tabview.h* | `lv_tabview_t` | *extra/widgets/tabview/lv_tabview.h* |
| `TextArea` | *widgets/textarea.h* | `lv_textarea_t` | *widgets/lv_textarea.h* |
| `TileView` | *widgets/tileview.h* | `lv_tileview_t` | *extra/widgets/tileview/lv_tileview.h* |
| `Window` | *widgets/win.h* | `lv_win_t` | *extra/widgets/win/lv_win.h* |

# API documentation

There is a documentation generated from docstrings in the *doc* folder. See [here](doc/html/index.html).

## Tests

Time to write some...

## Examples

Time to write some too...
