/** \file calendar.cpp
 *  \brief Implementation file for C++ wrapper for lv_calendar_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "calendar.h"
#if LV_USE_CALENDAR

namespace lvgl::widgets {
 
    void Calendar::set_today_date(uint32_t year, uint32_t month, uint32_t day) {
        lv_calendar_set_today_date(this->raw_ptr(), year, month, day);
    }

    void Calendar::set_displayed_month(uint32_t year, uint32_t month) {
        lv_calendar_set_showed_date(this->raw_ptr(), year, month);
    }

    void Calendar::set_highlighted_dates(std::vector<lv_calendar_date_t> highlighted) {
        lv_calendar_set_highlighted_dates(this->raw_ptr(), highlighted.data(), highlighted.size());
    }

    void Calendar::set_day_names(const std::vector<std::string> & day_names) {
        this->day_names = str_vector_to_char_array(day_names);
        // see ButtonMatrix::set_map for explanation as to why I consider this OK here.
        lv_calendar_set_day_names(this->raw_ptr(), (const char**)this->day_names.get());
    }

    Object Calendar::get_btnmatrix() const {
        return Object(lv_calendar_get_btnmatrix(this->raw_ptr()));
    }

    const lv_calendar_date_t Calendar::get_today_date() const {
        return *lv_calendar_get_today_date(this->raw_ptr());
    }

    const lv_calendar_date_t Calendar::get_displayed_month() const {
        return *lv_calendar_get_showed_date(this->raw_ptr());
    }

    std::vector<lv_calendar_date_t> Calendar::get_highlighted_dates() const {
        auto num = lv_calendar_get_highlighted_dates_num(this->raw_ptr());
        std::vector<lv_calendar_date_t> dates(num);
        auto lv_dates = lv_calendar_get_highlighted_dates(this->raw_ptr());
        for (size_t n=0; n<num; n++)
            dates.emplace_back(lv_dates[n]);
        return dates;
    }

    const std::shared_ptr<lv_calendar_date_t> Calendar::get_selected_date() const {
        auto date = std::make_shared<lv_calendar_date_t>();
        auto res = lv_calendar_get_pressed_date(this->raw_ptr(), date.get());
        if (res == LV_RES_INV) return nullptr;
        return date;
    }
 
    Object Calendar::header_arrow_create() {
        return Object(lv_calendar_header_arrow_create(this->raw_ptr()));

    }

    Object Calendar::header_dropdown_create() {
        return Object(lv_calendar_header_dropdown_create(this->raw_ptr()));
    }
 
}
#endif // LV_USE_CALENDAR
