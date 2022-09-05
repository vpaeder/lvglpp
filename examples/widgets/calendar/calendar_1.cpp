#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/calendar/calendar.h" // for Calendar
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    
    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_current_target<Calendar>();

        if(code == LV_EVENT_VALUE_CHANGED) {
            auto date = obj.get_selected_date();
            if(date != nullptr) {
                LV_LOG_USER("Clicked date: %02d.%02d.%d", date->day, date->month, date->year);
            }
        }
    }

    void calendar_1() {
        auto root = scr_act();
        static auto calendar = Calendar(scr_act());
        calendar.set_size(185, 185);
        calendar.align(LV_ALIGN_CENTER, 0, 27);
        calendar.add_event_cb(event_handler, LV_EVENT_ALL);

        calendar.set_today_date(2021, 02, 23);
        calendar.set_displayed_month(2021, 02);

        /*Highlight a few days*/
        static std::vector<lv_calendar_date_t> highlighted_days(3);       /*Only its pointer will be saved so should be static*/
        highlighted_days[0].year = 2021;
        highlighted_days[0].month = 02;
        highlighted_days[0].day = 6;

        highlighted_days[1].year = 2021;
        highlighted_days[1].month = 02;
        highlighted_days[1].day = 11;

        highlighted_days[2].year = 2022;
        highlighted_days[2].month = 02;
        highlighted_days[2].day = 22;

        calendar.set_highlighted_dates(highlighted_days);

    #if LV_USE_CALENDAR_HEADER_DROPDOWN
        auto dropdown = calendar.header_dropdown_create();
    #elif LV_USE_CALENDAR_HEADER_ARROW
        auto header = calendar.header_arrow_create();
    #endif
        calendar.set_displayed_month(2021, 10);
    }
}