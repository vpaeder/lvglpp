/** \file button.h
 *  \brief Header file for C++ wrapper for lv_chart_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_CHART != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Chart
     *  \brief Wraps a lv_chart_t object.
     */
    class Chart : public Widget<lv_chart_create> {
    public:
        using Widget::Widget;

        /** \fn void set_type(lv_chart_type_t type)
         *  \brief Sets chart type.
         *  \param type: chart type (LV_CHART_TYPE_NONE/LINE/BAR/SCATTER).
         */
        void set_type(lv_chart_type_t type);

        /** \fn void set_point_count(uint16_t cnt)
         *  \brief Sets chart's number of points.
         *  \param cnt: number of points.
         */
        void set_point_count(uint16_t cnt);

        /** \fn void set_range(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max)
         *  \brief Sets axis range.
         *  \param axis: chart axis (LV_CHART_AXIS_PRIMARY_X/PRIMARY_Y/SECONDARY_X/SECONDARY_Y).
         *  \param min: minimum value.
         *  \param max: maximum value.
         */
        void set_range(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max);

        /** \fn void set_update_mode(lv_chart_update_mode_t update_mode)
         *  \brief Sets update mode.
         *  \param update_mode: update mode (LV_CHART_UPDATE_MODE_SHIFT/CIRCULAR).
         */
        void set_update_mode(lv_chart_update_mode_t update_mode);

        /** \fn void set_div_line_count(uint8_t hdiv, uint8_t vdiv)
         *  \brief Sets number of grid lines.
         *  \param hdiv: horizontal grid lines.
         *  \param vdiv: vertical grid lines.
         */
        void set_div_line_count(uint8_t hdiv, uint8_t vdiv);

        /** \fn void set_zoom_x(uint16_t zoom_x)
         *  \brief Sets zoom factor for x direction.
         *  \param zoom_x: zoom factor (256 = no zoom, 512 = double, 128 = half, ...).
         */
        void set_zoom_x(uint16_t zoom_x);

        /** \fn void set_zoom_y(uint16_t zoom_y)
         *  \brief Sets zoom factor for y direction.
         *  \param zoom_y: zoom factor (256 = no zoom, 512 = double, 128 = half, ...).
         */
        void set_zoom_y(uint16_t zoom_y);

        /** \fn void set_axis_tick(lv_chart_axis_t axis, lv_coord_t major_len, lv_coord_t minor_len,
         *                         lv_coord_t major_cnt, lv_coord_t minor_cnt, bool label_en,
         *                         lv_coord_t draw_size);
         *  \brief Sets tick properties on given axis.
         *  \param axis: chart axis (LV_CHART_AXIS_PRIMARY_X/PRIMARY_Y/SECONDARY_X/SECONDARY_Y).
         *  \param major_len: length of major ticks.
         *  \param minor_len: length of minor ticks.
         *  \param major_cnt: number of major ticks.
         *  \param minor_cnt: number of minor ticks.
         *  \param label_en: if true, enable label on major ticks.
         *  \param draw_size: extra space added next to axis to draw ticks.
         */
        void set_axis_tick(lv_chart_axis_t axis, lv_coord_t major_len, lv_coord_t minor_len,
                           lv_coord_t major_cnt, lv_coord_t minor_cnt, bool label_en,
                           lv_coord_t draw_size);

        /** \fn uint16_t get_zoom_x() const
         *  \brief Gets zoom factor for x direction.
         *  \returns zoom factor.
         */
        uint16_t get_zoom_x() const;

        /** \fn uint16_t get_zoom_y() const
         *  \brief Gets zoom factor for y direction.
         *  \returns zoom factor.
         */
        uint16_t get_zoom_y() const;

        /** \fn lv_chart_type_t get_type() const
         *  \brief Gets chart type.
         *  \returns code for chart type.
         */
        lv_chart_type_t get_type() const;

        /** \fn uint16_t get_point_count() const
         *  \brief Gets number of points on chart.
         *  \returns number of points.
         */
        uint16_t get_point_count() const;

        /** \fn uint16_t get_x_start_point(lv_chart_series_t * ser) const
         *  \brief Gets first point of given series displayed on chart.
         *  \param ser: pointer to a series instance.
         *  \returns index of first point displayed.
         */
        uint16_t get_x_start_point(lv_chart_series_t * ser) const;

        /** \fn lv_point_t get_point_pos_by_id(lv_chart_series_t * ser, uint16_t id) const;
         *  \brief Gets coordinates of point with given index.
         *  \param ser: pointer to a series instance.
         *  \param id: index of point.
         *  \returns coordinates of point.
         */
        lv_point_t get_point_pos_by_id(lv_chart_series_t * ser, uint16_t id) const;

        /** \fn void refresh()
         *  \brief Marks chart for refresh.
         */
        void refresh();

        /** \fn lv_chart_series_t * add_series(lv_color_t color, lv_chart_axis_t axis)
         *  \brief Adds one series with given color on given axis.
         *  \param color: series display color.
         *  \param axis: the y axis hosting the series (LV_CHART_AXIS_PRIMARY_Y/SECONDARY_Y).
         *  \returns pointer to the new series instance.
         */
        lv_chart_series_t * add_series(lv_color_t color, lv_chart_axis_t axis);

        /** \fn void remove_series(lv_chart_series_t * ser)
         *  \brief Removes given series from chart.
         *  \param ser: pointer to a series instance.
         */
        void remove_series(lv_chart_series_t * ser);

        /** \fn void hide_series(lv_chart_series_t * ser)
         *  \brief Hides given series.
         *  \param ser: pointer to a series instance.
         */
        void hide_series(lv_chart_series_t * ser);

        /** \fn void show_series(lv_chart_series_t * ser)
         *  \brief Makes given series visible.
         *  \param ser: pointer to a series instance.
         */
        void show_series(lv_chart_series_t * ser);

        /** \fn void set_series_color(lv_chart_series_t * ser, lv_color_t color)
         *  \brief Sets series color.
         *  \param ser: pointer to a series instance.
         *  \param color: desired color.
         */
        void set_series_color(lv_chart_series_t * ser, lv_color_t color);

        /** \fn void set_x_start_point(lv_chart_series_t * ser, uint16_t id)
         *  \brief Defines which point of given series is considered as first point.
         *  \param ser: pointer to a series instance.
         *  \param id: index of first point.
         */
        void set_x_start_point(lv_chart_series_t * ser, uint16_t id);

        /** \fn lv_chart_series_t * get_next_series(lv_chart_series_t * ser) const
         *  \brief Gets series following given series.
         *  \param ser: pointer to a series instance.
         *  \returns a pointer to the next series.
         */
        lv_chart_series_t * get_next_series(lv_chart_series_t * ser) const;

        /** \fn lv_chart_cursor_t * add_cursor(lv_color_t color, lv_dir_t dir)
         *  \brief Adds a cursor to the chart.
         *  \param color: cursor color.
         *  \param dir: OR-ed combination of lv_dir_t values.
         *  \returns a pointer to the new cursor instance.
         */
        lv_chart_cursor_t * add_cursor(lv_color_t color, lv_dir_t dir);

        /** \fn void set_cursor_pos(lv_chart_cursor_t * cursor, const lv_point_t & pos)
         *  \brief Sets cursor position.
         *  \param cursor: pointer to a cursor instance.
         *  \param pos: coordinates.
         */
        void set_cursor_pos(lv_chart_cursor_t * cursor, lv_point_t & pos);

        /** \fn void set_cursor_point(lv_chart_cursor_t * cursor, lv_chart_series_t * ser, uint16_t id)
         *  \brief Sets cursor position on series point.
         *  \param cursor: pointer to a cursor instance.
         *  \param ser: pointer to a series instance.
         *  \param id: index of point.
         */
        void set_cursor_point(lv_chart_cursor_t * cursor, lv_chart_series_t * ser, uint16_t id);

        /** \fn void set_cursor_point(lv_chart_cursor_t * cursor, uint16_t id)
         *  \brief Sets cursor position on given point of first series.
         *  \param cursor: pointer to a cursor instance.
         *  \param id: index of point.
         */
        void set_cursor_point(lv_chart_cursor_t * cursor, uint16_t id);

        /** \fn lv_point_t get_cursor_point(lv_chart_cursor_t * cursor) const
         *  \brief Gets coordinates of given cursor.
         *  \param cursor: pointer to a cursor instance.
         *  \returns coordinates of cursor.
         */
        lv_point_t get_cursor_point(lv_chart_cursor_t * cursor) const;

        /** \fn void set_all_value(lv_chart_series_t * ser, lv_coord_t value);
         *  \brief Sets all points of a series to the given value.
         *  \param ser: pointer to a series instance.
         *  \param value: value to set.
         */
        void set_all_value(lv_chart_series_t * ser, lv_coord_t value);

        /** \fn void set_next_y_value(lv_chart_series_t * ser, lv_coord_t value)
         *  \brief Sets next point's y coordinate of a series to given value.
         *  \param ser: pointer to a series instance.
         *  \param value: value to set.
         */
        void set_next_y_value(lv_chart_series_t * ser, lv_coord_t value);

        /** \fn void set_next_xy_values(lv_chart_series_t * ser, lv_coord_t x_value, lv_coord_t y_value)
         *  \brief Sets next point of a series to given values.
         *  \param ser: pointer to a series instance.
         *  \param x_value: value along x axis.
         *  \param y_value: value along y axis.
         */
        void set_next_xy_values(lv_chart_series_t * ser, lv_coord_t x_value, lv_coord_t y_value);

        /** \fn void set_y_value_by_id(lv_chart_series_t * ser, uint16_t id, lv_coord_t value)
         *  \brief For given series, sets y coordinate of point with given index to given value.
         *  \param ser: pointer to a series instance.
         *  \param id: point index.
         *  \param value: value to set.
         */
        void set_y_value_by_id(lv_chart_series_t * ser, uint16_t id, lv_coord_t value);

        /** \fn void set_xy_value_by_id(lv_chart_series_t * ser, uint16_t id, lv_coord_t value)
         *  \brief For given series, sets coordinates of point with given index to given value.
         *  \param ser: pointer to a series instance.
         *  \param id: point index.
         *  \param x_value: value along x axis.
         *  \param y_value: value along y axis.
         */
        void set_xy_value_by_id(lv_chart_series_t * ser, uint16_t id, lv_coord_t x_value, lv_coord_t y_value);

        /** \fn void set_ext_y_array(lv_chart_series_t * ser, std::vector<lv_coord_t> array)
         *  \brief Sets series y values from given array.
         *  \param ser: pointer to a series instance.
         *  \param array: values to set.
         */
        void set_ext_y_array(lv_chart_series_t * ser, std::vector<lv_coord_t> array);

        /** \fn void set_ext_x_array(lv_chart_series_t * ser, std::vector<lv_coord_t> array)
         *  \brief Sets series x values from given array.
         *  \param ser: pointer to a series instance.
         *  \param array: values to set.
         */
        void set_ext_x_array(lv_chart_series_t * ser, std::vector<lv_coord_t> array);

        /** \fn lv_coord_t * get_y_array(lv_chart_series_t * ser) const
         *  \brief Gets y values from given series.
         *  \param ser: pointer to a series instance.
         *  \returns pointer to array with y values.
         */
        lv_coord_t * get_y_array(lv_chart_series_t * ser) const;

        /** \fn lv_coord_t * get_x_array(lv_chart_series_t * ser) const
         *  \brief Gets x values from given series.
         *  \param ser: pointer to a series instance.
         *  \returns pointer to array with x values.
         */
        lv_coord_t * get_x_array(lv_chart_series_t * ser) const;

        /** \fn uint32_t get_selected_point() const
         *  \brief Gets the index of the selected point.
         *  \returns index of selected point.
         */
        uint32_t get_selected_point() const;

        /** \fn lv_chart_series_t * get_series_first() const
         *  \brief Gets first series.
         *  \returns pointer to first series.
         */
        lv_chart_series_t * get_series_first() const;

        /** \fn lv_chart_series_t * get_series_next(lv_chart_series_t * ser) const
         *  \brief Gets series following given one.
         *  \param ser: pointer to series.
         *  \returns pointer to following series.
         */
        lv_chart_series_t * get_series_next(lv_chart_series_t * ser) const;

    };

}
#endif // LV_USE_CHART
