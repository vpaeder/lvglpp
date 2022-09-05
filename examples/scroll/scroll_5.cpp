#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void scroll_5() {
        static auto obj = Container(scr_act());
        obj.set_style_base_dir(LV_BASE_DIR_RTL, LV_PART_MAIN);
        obj.set_size(200, 100);
        obj.center();

        static auto label = Label(obj);
        label.set_text("میکروکُنترولر (به انگلیسی: Microcontroller) گونه‌ای ریزپردازنده است که دارای حافظهٔ دسترسی تصادفی (RAM) و حافظهٔ فقط‌خواندنی (ROM)، تایمر، پورت‌های ورودی و خروجی (I/O) و درگاه ترتیبی (Serial Port پورت سریال)، درون خود تراشه است، و می‌تواند به تنهایی ابزارهای دیگر را کنترل کند. به عبارت دیگر یک میکروکنترلر، مدار مجتمع کوچکی است که از یک CPU کوچک و اجزای دیگری مانند تایمر، درگاه‌های ورودی و خروجی آنالوگ و دیجیتال و حافظه تشکیل شده‌است.");
        label.set_width(400);
        labe.set_style_text_font(&lv_font_dejavu_16_persian_hebrew, 0);
    }
}