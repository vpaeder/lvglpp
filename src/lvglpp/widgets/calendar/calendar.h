/** \file calendar.h
 *  \brief Header file for C++ wrapper for lv_calendar_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_CALENDAR

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Calendar
     *  \brief Wraps a lv_calendar_t object.
     */
    class Calendar : public Widget<lv_calendar_create> {
    private:
        /** \property RawDblArray<char> day_names
         *  \brief Days names.
         */
        RawDblArray<char> day_names;

    public:
        using Widget::Widget;

        /** \fn void set_today_date(uint32_t year, uint32_t month, uint32_t day)
         *  \brief Sets today's date.
         *  \param year: today's year.
         *  \param month: today's month (1 to 12).
         *  \param day: today's day of the month (1 to 31).
         */
        void set_today_date(uint32_t year, uint32_t month, uint32_t day);

        /** \fn void set_displayed_month(uint32_t year, uint32_t month)
         *  \brief Sets displayed month.
         *  \param year: month's year.
         *  \param month: month (1 to 12).
         */
        void set_displayed_month(uint32_t year, uint32_t month);

        /** \fn void set_highlighted_dates(std::vector<lv_calendar_date_t> highlighted)
         *  \brief Sets highlighted dates.
         *  \param highlighted: highlighted dates.
         */
        void set_highlighted_dates(std::vector<lv_calendar_date_t> highlighted);

        /** \fn void set_day_names(const std::vector<std::string> & day_names)
         *  \brief Sets days names.
         *  \param day_names: a 7-item array with days names ("Sun", "Mon", ...)
         */
        void set_day_names(const std::vector<std::string> & day_names);

        /** \fn Object get_btnmatrix() const
         *  \brief Gets calendar's button matrix object.
         *  \returns object wrapping button matrix instance.
         */
        Object get_btnmatrix() const;

        /** \fn const lv_calendar_date_t get_today_date() const
         *  \brief Gets today's date.
         *  \returns pointer to today's date.
         */
        const lv_calendar_date_t get_today_date() const;

        /** \fn const lv_calendar_date_t get_displayed_month() const
         *  \brief Gets displayed month.
         *  \returns pointer to first day of displayed month.
         */
        const lv_calendar_date_t get_displayed_month() const;

        /** \fn std::vector<lv_calendar_date_t> get_highlighted_dates() const;
         *  \brief Gets highlighted dates.
         *  \returns a list of pointers to highlighted dates.
         */
        std::vector<lv_calendar_date_t> get_highlighted_dates() const;

        /** \fn const std::shared_ptr<lv_calendar_date_t> get_selected_date() const
         *  \brief Gets selected date.
         *  \returns a pointer to selected date.
         */
        const std::shared_ptr<lv_calendar_date_t> get_selected_date() const;

        /** \fn Object header_arrow_create()
         *  \brief Creates arrows on calendar header.
         *  \returns object representing arrows.
         */
        Object header_arrow_create();

        /** \fn Object header_dropdown_create()
         *  \brief Creates dropdown on calendar header.
         *  \returns object representing dropdown.
         */
        Object header_dropdown_create();
        
    };

}
#endif // LV_USE_CALENDAR
