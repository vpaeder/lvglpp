/** \file calendar.h
 *  \brief Header file for C++ wrapper for lv_calendar_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Calendar
     *  \brief Wraps a lv_calendar_t object.
     */
    class Calendar : public Object {
    private:
        /** \property RawDblArray<char> day_names
         *  \brief Days names.
         */
        RawDblArray<char> day_names;

    protected:
        /** \fn void initialize()
         *  \brief Initialize object.
         */
        void initialize() override;
        /** \fn void initialize(Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        void initialize(Object & parent) override;
    
    public:
        /** \fn Calendar()
         *  \brief Default constructor.
         */
        Calendar();
        /** \fn Calendar(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        Calendar(Object & parent);

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

        /** \fn const std::shared_ptr<const lv_calendar_date_t> get_today_date() const
         *  \brief Gets today's date.
         *  \returns pointer to today's date.
         */
        const std::shared_ptr<const lv_calendar_date_t> get_today_date() const;

        /** \fn const std::shared_ptr<const lv_calendar_date_t> get_displayed_month() const
         *  \brief Gets displayed month.
         *  \returns pointer to first day of displayed month.
         */
        const std::shared_ptr<const lv_calendar_date_t> get_displayed_month() const;

        /** \fn std::vector< std::shared_ptr<lv_calendar_date_t> > get_highlighted_dates() const;
         *  \brief Gets highlighted dates.
         *  \returns a list of pointers to highlighted dates.
         */
        std::vector<std::shared_ptr<lv_calendar_date_t>> get_highlighted_dates() const;

        /** \fn const std::shared_ptr<lv_calendar_date_t> get_selected_date() const
         *  \brief Gets selected date.
         *  \returns a pointer to selected date.
         */
        const std::shared_ptr<lv_calendar_date_t> get_selected_date() const;
    };

}
