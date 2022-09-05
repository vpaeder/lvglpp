#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/span/span.h" // for Span
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void span_1() {
        static auto spangrp = SpanGroup(scr_act());
        spangrp.set_width(300);
        spangrp.set_height(300);
        spangrp.center();

        static Style style;
        style.set_border_width(1);
        style.set_border_color(palette::main(Color::Orange));
        style.set_pad_all(2);

        spangrp.add_style(style, LV_PART_MAIN);
        spangrp.set_align(LV_TEXT_ALIGN_LEFT);
        spangrp.set_overflow(LV_SPAN_OVERFLOW_CLIP);
        spangrp.set_indent(20);
        spangrp.set_mode(LV_SPAN_MODE_BREAK);

        auto span1 = spangrp.new_span();
        span1.set_text("China is a beautiful country.");
        auto span1_style = span1.get_style();
        span1_style.set_text_color(palette::main(Color::Red));
        span1_style.set_text_decor(LV_TEXT_DECOR_STRIKETHROUGH | LV_TEXT_DECOR_UNDERLINE);
        span1_style.set_text_opa(LV_OPA_50);

        auto span2 = spangrp.new_span();
        span2.set_text_static("good good study, day day up.");
        auto span2_style = span2.get_style();
    #if LV_FONT_MONTSERRAT_24
        span2_style.set_text_font(&lv_font_montserrat_24);
    #endif
        span2_style.set_text_color(palette::main(Color::Green));

        auto span3 = spangrp.new_span();
        span3.set_text_static("LVGL is an open-source graphics library.");
        span3.get_style().set_text_color(palette::main(Color::Blue));

        auto span4 = spangrp.new_span();
        span4.set_text_static("the boy no name.");
        auto span4_style = span4.get_style();
        span4_style.set_text_color(palette::main(Color::Green));
    #if LV_FONT_MONTSERRAT_20
        span4_style.set_text_font(&lv_font_montserrat_20);
    #endif
        span4_style.set_text_decor(LV_TEXT_DECOR_UNDERLINE);

        auto span5 = spangrp.new_span();
        span5.set_text("I have a dream that hope to come true.");

        spangrp.refresh_mode();
    }
}