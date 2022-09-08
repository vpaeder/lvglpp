# lvglpp: a C++ wrapper for LVGL

This package contains a rather bushy wrapper for [LVGL](https://github.com/lvgl/lvgl). I originally needed to program a simple user interface, but I didn't want to write a GUI framework from scratch, and found LVGL rather nice. Only that it's written in C. So I started writing C++ classes for the part of the code I wanted to use, and then it got out of control. Now most of the library has some kind of wrapper class provided. I've tested nearly all examples on an ESP32 with a touch screen interface. You can find a working application [here](https://github.com/vpaeder/esp_obs_commander).

This is a work in progress. I will likely improve things as I use it, which will take between one day and forever. I of course welcome contributions.

At the time of writing, I use LVGL version 8.3 (available [here](https://github.com/lvgl/lvgl)). Your C++ compiler must support C++17 or newer.

Note that I'm not part of the LVGL team. If you have requests related to LVGL itself, please ask them.

## TL;DR

See examples [here](examples/) and docs in the *doc* folder (you need to clone the repository for that).

## Structure

I tried to mirror the directory structure of LVGL to some degree (with exceptions with *extra* and *hal* directories). A number of types that are defined in multiple files are compiled together as one (e.g. style, image, draw). I've put all the widgets (including extra ones) in the *widgets* directory.

My point was to provide functions that take a certain LVGL object type as first argument as a class method. For instance, all functions taking a `lv_obj_t*` as first argument end up as methods of the `Object` class. I tried to replace raw pointer args either with a C++ class instance passed by reference or a smart pointer.

There is a template class in *lv_wrapper.h*, `PointerWrapper<lv_class, lv_deleter>`, to facilitate encapsulation. It stores a `unique_ptr` of type `lv_class` with custom deleter function `lv_deleter`. A number of LVGL types have an associated deleter function, which can be provided there. For widgets, there's a template class called `Widget<lv_allocator>` that provides a constructor to nest objects.

Here is a list of classes with the corresponding link to LVGL:
| Class | File | Wrapped type | LVGL file(s) |
|-------|------|-----------|--------------|
| `Display` | *core/display.h* | `lv_disp_t`<br/>`lv_disp_drv_t` | *hal/lv_hal_disp.h*<br/>*core/lv_disp.h* |
| `Event` | *core/event.h* | `lv_event_t` | *core/lv_event.h* |
| `Group` | *core/group.h* | `lv_group_t` | *core/lv_group.h* |
| `InputDevice`<br/>`PointerInputDevice`<br/>`ButtonInputDevice`<br/>`KeypadInputDevice`<br/>`EncoderInputDevice` | *core/indev.h* | `lv_indev_t`<br/>`lv_indev_drv_t` | *hal/lv_hal_indev.h*<br/>*core/lv_indev.h* |
| `Object` | *core/object.h* | `lv_obj_t` | *core/lv_obj.h*<br/>*core/lv_obj_draw.h*<br/>*core/lv_obj_pos.h*<br/>*core/lv_scroll.h*<br/>*core/lv_obj_style.h*<br/>*core/lv_obj_style_gen.h*<br/>*core/lv_obj_tree.h*<br/>*extra/layouts/flex/lv_flex.h*<br/>*extra/layouts/grid/lv_grid.h* |
| `Theme` | *core/theme.h* | `lv_theme_t` | *core/lv_theme.h* |
| `RectangleDrawDescriptor` | *draw/desc.h* | `lv_draw_rect_dsc_t` | *draw/lv_draw_rect.h* |
| `LabelDrawDescriptor` | *draw/desc.h* | `lv_draw_label_dsc_t` | *draw/lv_draw_label.h* |
| `ImageDrawDescriptor` | *draw/desc.h* | `lv_draw_img_dsc_t` | *draw/lv_draw_img.h* |
| `LineDrawDescriptor` | *draw/desc.h* | `lv_draw_line_dsc_t` | *draw/lv_draw_line.h* |
| `ArcDrawDescriptor` | *draw/desc.h* | `lv_draw_arc_dsc_t` | *draw/lv_draw_arc.h* |
| `ImageDecoder` | *draw/image.h* | `lv_img_decoder_dsc_t` | *draw/lv_img_decoder.h* |
| `ImageHeader` | *draw/image.h* | `lv_img_header_t` | *draw/lv_img_buf.h* |
| `ImageDescriptor` | *draw/image.h* | `lv_img_dsc_t` | *draw/lv_img_buf.h* |
| `LineMask` | *draw/mask.h* | `lv_draw_mask_line_param_t` | *draw/lv_draw_mask.h* |
| `AngleMask` | *draw/mask.h* | `lv_draw_mask_angle_param_t` | *draw/lv_draw_mask.h* |
| `RadiusMask` | *draw/mask.h* | `lv_draw_mask_radius_param_t` | *draw/lv_draw_mask.h* |
| `FadeMask` | *draw/mask.h* | `lv_draw_mask_fade_param_t` | *draw/lv_draw_mask.h* |
| `MapMask` | *draw/mask.h* | `lv_draw_mask_map_param_t` | *draw/lv_draw_mask.h* |
| `PolygonMask` | *draw/mask.h* | `lv_draw_mask_polygon_param_t` | *draw/lv_draw_mask.h* |
| `Font` | *font/font.h* | `lv_font_t` | *font/lv_font.h* |
| `Animation` | *misc/anim.h* | `lv_anim_t` | *misc/lv_anim.h* |
| `AnimationTimeline` | *misc/anim.h* | `lv_anim_timeline_t` | *misc/lv_anim_timeline.h* |
| `Area` | *misc/area.h* | `lv_area_t` | *misc/lv_area.h* |
| `FileSystem` | *misc/fs.h* | `lv_fs_t` | *misc/lv_fs.h* |
| `File` | *misc/fs.h* | `lv_fs_file_t` | *misc/lv_fs.h* |
| `Directory` | *misc/fs.h* | `lv_fs_dir_t` | *misc/lv_fs.h* |
| `Style` | *misc/style.h* | `lv_style_t` | *misc/lv_style.h*<br/>*misc/lv_style_gen.h* |
| `Timer` | *misc/timer.h* | `lv_timer_t` | *misc/lv_timer.h* |
| `AnimatedImage` | *widgets/animimg/animimg.h* | `lv_animimg_t` | *extra/widgets/animimg/lv_animimg.h* |
| `Arc` | *widgets/arc/arc.h* | `lv_arc_t` | *widgets/lv_arc.h* |
| `Bar` | *widgets/bar/bar.h* | `lv_bar_t` | *widgets/lv_bar.h* |
| `ButtonMatrix` | *widgets/btnmatrix/btnmatrix.h* | `lv_btnmatrix_t` | *widgets/lv_btnmatrix.h* |
| `Button` | *widgets/button/button.h* | `lv_btn_t` | *widgets/lv_btn.h* |
| `Calendar` | *widgets/calendar/calendar.h* | `lv_calendar_t` | *extra/widgets/calendar/lv_calendar.h* |
| `Canvas` | *widgets/canvas/canvas.h* | `lv_canvas_t` | *widgets/lv_canvas.h* |
| `Chart` | *widgets/chart/chart.h* | `lv_chart_t` | *extra/widgets/chart/lv_chart.h* |
| `Checkbox` | *widgets/checkbox/checkbox.h* | `lv_checkbox_t` | *widgets/lv_checkbox.h* |
| `ColorWheel` | *widgets/colorwheel/colorwheel.h* | `lv_colorwheel_t` | *extra/widgets/colorwheel/lv_colorwheel.h* |
| `Dropdown` | *widgets/dropdown/dropdown.h* | `lv_dropdown_t` | *widgets/lv_dropdown.h* |
| `Image` | *widgets/image/image.h* | `lv_image_t` | *widgets/lv_img.h* |
| `ImageButton` | *widgets/imgbtn/imgbtn.h* | `lv_imgbtn_t` | *extra/widgets/imgbtn/lv_imgbtn.h* |
| `Keyboard` | *widgets/keyboard/keyboard.h* | `lv_keyboard_t` | *extra/widgets/keyboard/lv_keyboard.h* |
| `Label` | *widgets/label/label.h* | `lv_label_t` | *widgets/lv_label.h* |
| `Led` | *widgets/led/led.h* | `lv_led_t` | *extra/widgets/led/lv_led.h* |
| `Line` | *widgets/line/line.h* | `lv_line_t` | *widgets/lv_line.h* |
| `List` | *widgets/list/list.h* | `lv_list_t` | *extra/widgets/list/lv_list.h* |
| `Menu` | *widgets/menu/menu.h* | `lv_menu_t` | *extra/widgets/menu/lv_menu.h* |
| `Meter` | *widgets/meter/meter.h* | `lv_meter_t` | *extra/widgets/meter/lv_meter.h* |
| `MessageBox` | *widgets/msgbox/msgbox.h* | `lv_msgbox_t` | *extra/widgets/msgbox/lv_msgbox.h* |
| `Roller` | *widgets/roller/roller.h* | `lv_roller_t` | *widgets/lv_roller.h* |
| `Slider` | *widgets/slider/slider.h* | `lv_slider_t` | *widgets/lv_slider.h* |
| `Span` | *widgets/span/span.h* | `lv_span_t` | *extra/widgets/span/lv_span.h* |
| `Spinbox` | *widgets/spinbox/spinbox.h* | `lv_spinbox_t` | *extra/widgets/spinbox/lv_spinbox.h* |
| `Spinner` | *widgets/spinner/spinner.h* | `lv_spinner_t` | *extra/widgets/spinner/lv_spinner.h* |
| `Switch` | *widgets/switch/switch.h* | `lv_switch_t` | *widgets/lv_switch.h* |
| `Table` | *widgets/table/table.h* | `lv_table_t` | *widgets/lv_table.h* |
| `Tabview` | *widgets/tabview/tabview.h* | `lv_tabview_t` | *extra/widgets/tabview/lv_tabview.h* |
| `TextArea` | *widgets/textarea/textarea.h* | `lv_textarea_t` | *widgets/lv_textarea.h* |
| `TileView` | *widgets/tileview/tileview.h* | `lv_tileview_t` | *extra/widgets/tileview/lv_tileview.h* |
| `Window` | *widgets/win/win.h* | `lv_win_t` | *extra/widgets/win/lv_win.h* |

I've included some useful functions that don't take a specific LVGL type as argument in namespaces. These are:
| Namespace | Content |
|-----------|---------|
| `lvgl::core::obj` | For now, contains the function `draw_part_check_type`, that allows checking the type of a drawable part. I may move other functions related to objects there in the future. |
| `lvgl::draw::mask` | This contains functions about masks. |
| `lvgl::misc::color` | Since `lv_color_t` is a `uint32_t` with some coating, I found inefficient to build a class around it. Therefore, you'll find color functions in there. |
| `lvgl::misc::palette` | Access to the three standard palettes is found here in a C++ way. |
| `lvgl::misc::txt` | This contains some of the text functions found in `lv_txt.h`. |

## How to use

First of all, you need LVGL in the include paths. As for lvglpp, unlike with LVGL, you need to include each header that corresponds to what you want to use. To illustrate what I mean, a typical program would be:
```cpp
#include "lvglpp/lvglpp.h" // for init
#include "lvglpp/core/display.h" // for Display
#include "lvglpp/core/indev.h" // for InputDevice
#include "lvglpp/widgets/button.h" // for Button
// ... add includes for widgets your want to use here
#include "lvglpp/misc/style.h" // for Style
// .. add includes for other classes you want to use (Animation, Timer, ...)

using namespace lvgl::core;
using namespace lvgl::misc;
using namespace lvgl::widgets;

void main() {
    // initialize LVGL
    lvgl::init();
    // place here display and input device initialization;
    // read examples in examples/lvglpp directory to see how.

    // create button on active display
    auto btn = Button(scr_act());
    btn.center();
    // ... initialize more things ...

    // main loop
    for (;;) {
        // I didn't implement ticks yet -> use base LVGL ones;
        // you need to call both of these to get LVGL to work, but
        // you should put them in two different threads, with lv_tick_inc
        // in a higher priority thread.
        lv_tick_inc(10);
        lv_task_handler();
        // add here a function to wait for 10ms
    }
}
```

### Displays, input devices, filesystems

I've included some basic examples in *examples/lvglpp*. Since I only tested my code with a rather basic display, I didn't write classes that make uses of callbacks for monochrome or special displays. However, it's possible to do it yourself in a simple way:
```cpp
class CustomDisplay : public Display {
private:
    // arguments should be the arguments of the callback without the 1st one (lv_disp_drv_t* drv)
    void callback_to_implement(arguments) {
        // Put here what your callback does.
    }

public:
    CustomDisplay(lv_coord_t hor_res, lv_coord_t ver_res, uint32_t fb_size)
        : Display(hor_res, ver_res, fb_size) {
        // you need to link the callback with the display driver here
        auto cb = [](lv_disp_drv_t* drv, other arguments) {
            auto obj = reinterpret_cast<CustomDisplay*>(drv->user_data);
            obj->callback_to_implement(other arguments);
        };
        this->lv_disp_drv.callback_to_implement = cb;
        this->update_driver();
    }
};
```

For input devices, I included specialized classes for each type of input device available. I didn't implement the `feedback_cb` callback though. If you need it, you can write a derived class following the same scheme as for displays.

There's also a commented example for a custom filesystem driver. It'd be possible to port the available drivers to C++ using this template. Note that this only makes sense if you need to access files directly (for images, you can just as well register a C driver that will be used under the hood).

## Accessing managed object

Through the `PointerWrapper` class, I provide several ways to access the managed LVGL object:
- `raw()` returns a reference to the object;
- `raw_ptr()` returns a pointer to the object;
- the dereference operator `*` (e.g. *obj) returns a reference to the object (equivalent to `raw()`);
- the pointer-to-member operator `->` gives access to the object's structure (e.g. obj->coords for a wrapped `lv_obj_t*` will yield `coords` field of type `lv_area_t`).

## A note on callbacks and child objects

A number of classes (e.g. objects, timers, animations) use callbacks for different purposes. To make them look C++-like, I used the `user_data` field, which (almost) every LVGL structure provides, to give access to the C++ callback (by storing a pointer to the class object containing the callback function, or a pointer to a structure containing the callback functions, or a pointer to the callback function itself). This avoids storing C++ objects in some kind of global storage, but comes with two limitations: 1) we cannot use the `user_data` field for anything else; 2) we need to re-instantiate a C++ object to feed the callback with, everytime the callback is called. In most cases, the additional complexity won't matter. Nonetheless, where speed matters, it's always possible to use raw C callbacks instead.

Another caveat comes with child objects. Several widgets, especially, provide functions to create elements. For instance, the `Tabview` class has a function `add_tab` that returns an `Object` giving access to the created tab. The `Tabview` instance manages the new tab and deletes it when it gets deleted. Therefore, it's important not to delete it otherwise. Since `Object` instances wrap a raw C pointer in a `unique_ptr`, this would happen if the tab object gets out of scope. Therefore, I introduced a property, `owns_ptr`, that can be set on construction, and tells if the object owns the wrapped pointer. If it doesn't, the pointer gets released in the object's destructor. One can also force releasing the wrapped pointer with `release_ptr`. This can be useful when defining complex objects with lots of children that won't need to be accessed after creation. This way, the C++ object can be deleted without affecting the element it has created, freeing memory. You'll find several examples that make use of this.

## Caveats

Because of the way wrappers are implemented, it is important to remember to store the elements that are displayed. If any instance of a C++ object gets out of scope, the wrapped element gets deleted too (unless you use `release_ptr` or it's a child element generated by a widget).

LVGL stores the relationship of objects and takes care of deleting children of objects getting deleted. This means that you can safely use `release_ptr` on sub-widgets. Conversely, nothing is stored about instances of other types, like styles, animations, timers, ... Therefore, you **must not** `release_ptr` one of those, of you won't have any possibility to free it up afterwards. For those, you should either provide some kind of storage (`std::vector`, class member variable, ...) or make them static.

The equivalent of `lv_obj_create` is the `Container` class, and not the `Object` class, which stores a `lv_obj_t` but doesn't initialize one. The distinction is made as I wanted to avoid this: `Object(Object & parent)`. This would be seen as the copy constructor by the compiler, which is unwise for a class as general as `Object`.

For C++-style callbacks, it is important to remember that any object obtained from within the callback by calling an accessor function (such as `Event::get_target`) creates a temporary object wrapping a raw pointer. This means that you cannot create derived classes that would carry data along. Every call to the callback gets fed with a newly created temporary object with, other than the raw pointer, default values. Moreover, you cannot pass data using the `user_data` field, as it is used internally to pass the C++-style callback. For such cases, you need to define a global variable to transfer data to or from the callback.

Just like LVGL, lvglpp is NOT thread-safe. Therefore, as for LVGL, it is necessary to prevent concurrent execution of `lv_task_handler()` and other functions (with the exception of callbacks called from within task handler, like events or timers). This is typically done with a mutex, like:
```cpp
#include <mutex>
#include <thread>
std::mutex mtx;

void task_handler_thread() {
    for (;;) {
        {
            const std::lock_guard<std::mutex> lock(mtx);
            lv_task_handler();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void another_thread() {
    for (;;) {
        mtx.lock();
        // place code calling LVGL functions here
        mtx.unlock();
    }
}
```
Be aware that objects that get deleted because they go out of scope must also be treated. The easiest way, if possible, is to create a `lock_guard` in the beginning of the scope. If you cannot do that, I suggest using the following method:
```cpp
void a_function(const Object & parent) {
    mtx.lock();
    auto cnt = std::make_unique<Container>(parent);
    cnt->remove_style_all();
    cnt->set_size(parent.get_width(), parent.get_height());
    // ... code that creates objects ...
    auto obj = AnyObjectType(*cnt);
    // ... 
    mtx.unlock();
    // a bit of safe code ...
    // ... time to terminate function
    // we remove cnt and its content in a safe way
    mtx.lock();
    cnt = nullptr;
    mtx.unlock();
}
```

## Footprint

As lvglpp is essentially a layer over LVGL, it of course increases the memory footprint. However, most wrapper classes have only two member variables: a pointer to the wrapped object and a bool. This makes an overhead of 12 bytes per wrapped object. Several items need to store more content (e.g. Animation and ButtonMatrix) and will therefore need a little more space. Naturally, the binary size will also increase depending on the number of functions that are in use. I'll try to quantify these values at some point.
If you're hunting for free bytes, I'd rather recommend to use the original library instead.

# API documentation

There is a documentation generated from docstrings in the *doc* folder. See [here](doc/html/index.html).
You can re-generate the doc using doxygen in the project folder.

# Examples

I adapted most of the examples provided with LVGL. You'll find them in the *examples* folder [here](examples/). For examples that involve images, you need to include the appropriate files from LVGL examples. Don't forget to initialize LVGL and define a screen and an input device.

