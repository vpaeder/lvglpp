/** \file button.cpp
 *  \brief Implementation file for C++ wrapper for lv_chart_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "chart.h"

namespace lvgl::widgets {

    Chart::Chart() {
        this->initialize();
    }

    Chart::Chart(Object & parent) {
        this->initialize(parent);
    }

    void Chart::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_chart_create(nullptr));
    }
    void Chart::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_chart_create(parent.raw_ptr()));
    }

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

    uint16_t Chart::get_x_start_point(std::shared_ptr<lv_chart_series_t> ser) const {
        return lv_chart_get_x_start_point(this->raw_ptr(), ser.get());
    }

    lv_point_t Chart::get_point_pos_by_id(std::shared_ptr<lv_chart_series_t> ser, uint16_t id) const {
        lv_point_t pt;
        lv_chart_get_point_pos_by_id(const_cast<lv_cls_ptr>(this->raw_ptr()), ser.get(), id, &pt);
        return pt;

    }

    void Chart::refresh() {
        lv_chart_refresh(this->raw_ptr());
    }

    std::shared_ptr<lv_chart_series_t> Chart::add_series(lv_color_t color, lv_chart_axis_t axis) {
        return std::shared_ptr<lv_chart_series_t>(lv_chart_add_series(this->raw_ptr(), color, axis));
    }

    void Chart::remove_series(std::shared_ptr<lv_chart_series_t> ser) {
        lv_chart_remove_series(this->raw_ptr(), ser.get());
    }

    void Chart::hide_series(std::shared_ptr<lv_chart_series_t> ser) {
        lv_chart_hide_series(this->raw_ptr(), ser.get(), true);
    }

    void Chart::show_series(std::shared_ptr<lv_chart_series_t> ser) {
        lv_chart_hide_series(this->raw_ptr(), ser.get(), false);
    }

    void Chart::set_series_color(std::shared_ptr<lv_chart_series_t> ser, lv_color_t color) {
        lv_chart_set_series_color(this->raw_ptr(), ser.get(), color);
    }

    void Chart::set_x_start_point(std::shared_ptr<lv_chart_series_t> ser, uint16_t id) {
        lv_chart_set_x_start_point(this->raw_ptr(), ser.get(), id);
    }

    std::shared_ptr<lv_chart_series_t> Chart::get_next_series(std::shared_ptr<lv_chart_series_t> ser) const {
        return std::shared_ptr<lv_chart_series_t>(lv_chart_get_series_next(this->raw_ptr(), ser.get()));
    }

    std::shared_ptr<lv_chart_cursor_t> Chart::add_cursor(lv_color_t color, lv_dir_t dir) {
        return std::shared_ptr<lv_chart_cursor_t>(lv_chart_add_cursor(this->raw_ptr(), color, dir));
    }

    void Chart::set_cursor_pos(std::shared_ptr<lv_chart_cursor_t> cursor, lv_point_t & pos) {
        lv_chart_set_cursor_pos(this->raw_ptr(), cursor.get(), &pos);
    }

    void Chart::set_cursor_point(std::shared_ptr<lv_chart_cursor_t> cursor, std::shared_ptr<lv_chart_series_t> ser, uint16_t id) {
        lv_chart_set_cursor_point(this->raw_ptr(), cursor.get(), ser.get(), id);
    }

    lv_point_t Chart::get_cursor_point(std::shared_ptr<lv_chart_cursor_t> cursor) const {
        return lv_chart_get_cursor_point(const_cast<lv_cls_ptr>(this->raw_ptr()), cursor.get());
    }

    void Chart::set_all_value(std::shared_ptr<lv_chart_series_t> ser, lv_coord_t value) {
        lv_chart_set_all_value(this->raw_ptr(), ser.get(), value);
    }

    void Chart::set_next_y_value(std::shared_ptr<lv_chart_series_t> ser, lv_coord_t value) {
        lv_chart_set_next_value(this->raw_ptr(), ser.get(), value);
    }

    void Chart::set_next_xy_value(std::shared_ptr<lv_chart_series_t> ser, lv_coord_t x_value, lv_coord_t y_value) {
        lv_chart_set_next_value2(this->raw_ptr(), ser.get(), x_value, y_value);
    }

    void Chart::set_y_value_by_id(std::shared_ptr<lv_chart_series_t> ser, uint16_t id, lv_coord_t value) {
        lv_chart_set_value_by_id(this->raw_ptr(), ser.get(), id, value);
    }

    void Chart::set_xy_value_by_id(std::shared_ptr<lv_chart_series_t> ser, uint16_t id, lv_coord_t x_value, lv_coord_t y_value) {
        lv_chart_set_value_by_id2(this->raw_ptr(), ser.get(), id, x_value, y_value);
    }

    void Chart::set_ext_y_array(std::shared_ptr<lv_chart_series_t> ser, std::vector<lv_coord_t> array) {
        lv_chart_set_ext_y_array(this->raw_ptr(), ser.get(), array.data());
    }

    void Chart::set_ext_x_array(std::shared_ptr<lv_chart_series_t> ser, std::vector<lv_coord_t> array) {
        lv_chart_set_ext_x_array(this->raw_ptr(), ser.get(), array.data());
    }

    uint32_t Chart::get_selected_point() const {
        return lv_chart_get_pressed_point(this->raw_ptr());
    }

}