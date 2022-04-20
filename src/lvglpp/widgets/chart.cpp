/** \file chart.cpp
 *  \brief Implementation file for C++ wrapper for lv_chart_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "chart.h"
#if LV_USE_CHART != 0

namespace lvgl::widgets {

    void Chart::set_type(lv_chart_type_t type) {
        lv_chart_set_type(this->raw_ptr(), type);
    }

    void Chart::set_point_count(uint16_t cnt) {
        lv_chart_set_point_count(this->raw_ptr(), cnt);

    }

    void Chart::set_range(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max) {
        lv_chart_set_range(this->raw_ptr(), axis, min, max);
    }

    void Chart::set_update_mode(lv_chart_update_mode_t update_mode) {
        lv_chart_set_update_mode(this->raw_ptr(), update_mode);
    }

    void Chart::set_div_line_count(uint8_t hdiv, uint8_t vdiv) {
        lv_chart_set_div_line_count(this->raw_ptr(), hdiv, vdiv);
    }

    void Chart::set_zoom_x(uint16_t zoom_x) {
        lv_chart_set_zoom_x(this->raw_ptr(), zoom_x);
    }

    void Chart::set_zoom_y(uint16_t zoom_y) {
        lv_chart_set_zoom_y(this->raw_ptr(), zoom_y);
    }

    void Chart::set_axis_tick(lv_chart_axis_t axis, lv_coord_t major_len, lv_coord_t minor_len,
                        lv_coord_t major_cnt, lv_coord_t minor_cnt, bool label_en,
                        lv_coord_t draw_size) {
        lv_chart_set_axis_tick(this->raw_ptr(), axis, major_len, minor_len, major_cnt, minor_cnt, label_en, draw_size);
    }

    uint16_t Chart::get_zoom_x() const {
        return lv_chart_get_zoom_x(this->raw_ptr());
    }

    uint16_t Chart::get_zoom_y() const {
        return lv_chart_get_zoom_y(this->raw_ptr());
    }

    lv_chart_type_t Chart::get_type() const {
        return lv_chart_get_type(this->raw_ptr());
    }

    uint16_t Chart::get_point_count() const {
        return lv_chart_get_point_count(this->raw_ptr());
    }

    uint16_t Chart::get_x_start_point(lv_chart_series_t * ser) const {
        return lv_chart_get_x_start_point(this->raw_ptr(), ser);
    }

    lv_point_t Chart::get_point_pos_by_id(lv_chart_series_t * ser, uint16_t id) const {
        lv_point_t pt;
        lv_chart_get_point_pos_by_id(const_cast<lv_cls_ptr>(this->raw_ptr()), ser, id, &pt);
        return pt;

    }

    void Chart::refresh() {
        lv_chart_refresh(this->raw_ptr());
    }

    lv_chart_series_t * Chart::add_series(lv_color_t color, lv_chart_axis_t axis) {
        return lv_chart_add_series(this->raw_ptr(), color, axis);
    }

    void Chart::remove_series(lv_chart_series_t * ser) {
        lv_chart_remove_series(this->raw_ptr(), ser);
    }

    void Chart::hide_series(lv_chart_series_t * ser) {
        lv_chart_hide_series(this->raw_ptr(), ser, true);
    }

    void Chart::show_series(lv_chart_series_t * ser) {
        lv_chart_hide_series(this->raw_ptr(), ser, false);
    }

    void Chart::set_series_color(lv_chart_series_t * ser, lv_color_t color) {
        lv_chart_set_series_color(this->raw_ptr(), ser, color);
    }

    void Chart::set_x_start_point(lv_chart_series_t * ser, uint16_t id) {
        lv_chart_set_x_start_point(this->raw_ptr(), ser, id);
    }

    lv_chart_series_t * Chart::get_next_series(lv_chart_series_t * ser) const {
        return lv_chart_get_series_next(this->raw_ptr(), ser);
    }

    lv_chart_cursor_t * Chart::add_cursor(lv_color_t color, lv_dir_t dir) {
        return lv_chart_add_cursor(this->raw_ptr(), color, dir);
    }

    void Chart::set_cursor_pos(lv_chart_cursor_t * cursor, lv_point_t & pos) {
        lv_chart_set_cursor_pos(this->raw_ptr(), cursor, &pos);
    }

    void Chart::set_cursor_point(lv_chart_cursor_t * cursor, lv_chart_series_t * ser, uint16_t id) {
        lv_chart_set_cursor_point(this->raw_ptr(), cursor, ser, id);
    }

    void Chart::set_cursor_point(lv_chart_cursor_t * cursor, uint16_t id) {
        lv_chart_set_cursor_point(this->raw_ptr(), cursor, nullptr, id);
    }

    lv_point_t Chart::get_cursor_point(lv_chart_cursor_t * cursor) const {
        return lv_chart_get_cursor_point(const_cast<lv_cls_ptr>(this->raw_ptr()), cursor);
    }

    void Chart::set_all_value(lv_chart_series_t * ser, lv_coord_t value) {
        lv_chart_set_all_value(this->raw_ptr(), ser, value);
    }

    void Chart::set_next_y_value(lv_chart_series_t * ser, lv_coord_t value) {
        lv_chart_set_next_value(this->raw_ptr(), ser, value);
    }

    void Chart::set_next_xy_values(lv_chart_series_t * ser, lv_coord_t x_value, lv_coord_t y_value) {
        lv_chart_set_next_value2(this->raw_ptr(), ser, x_value, y_value);
    }

    void Chart::set_y_value_by_id(lv_chart_series_t * ser, uint16_t id, lv_coord_t value) {
        lv_chart_set_value_by_id(this->raw_ptr(), ser, id, value);
    }

    void Chart::set_xy_value_by_id(lv_chart_series_t * ser, uint16_t id, lv_coord_t x_value, lv_coord_t y_value) {
        lv_chart_set_value_by_id2(this->raw_ptr(), ser, id, x_value, y_value);
    }

    void Chart::set_ext_y_array(lv_chart_series_t * ser, std::vector<lv_coord_t> array) {
        lv_chart_set_ext_y_array(this->raw_ptr(), ser, array.data());
    }

    void Chart::set_ext_x_array(lv_chart_series_t * ser, std::vector<lv_coord_t> array) {
        lv_chart_set_ext_x_array(this->raw_ptr(), ser, array.data());
    }

    lv_coord_t * Chart::get_y_array(lv_chart_series_t * ser) const {
        return lv_chart_get_y_array(this->raw_ptr(), ser);
    }

    lv_coord_t * Chart::get_x_array(lv_chart_series_t * ser) const {
        return lv_chart_get_x_array(this->raw_ptr(), ser);
    }

    uint32_t Chart::get_selected_point() const {
        return lv_chart_get_pressed_point(this->raw_ptr());
    }

    lv_chart_series_t * Chart::get_series_first() const {
        return lv_chart_get_series_next(this->raw_ptr(), nullptr);
    }

    lv_chart_series_t * Chart::get_series_next(lv_chart_series_t * ser) const {
        return lv_chart_get_series_next(this->raw_ptr(), ser);
    }

}
#endif // LV_USE_CHART
