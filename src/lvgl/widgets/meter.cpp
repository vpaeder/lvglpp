/** \file meter.cpp
 *  \brief Implementation file for C++ wrapper for lv_meter_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "meter.h"

namespace lvgl::widgets {

    Meter::Meter() {
        this->initialize();
    }

    Meter::Meter(Object & parent) {
        this->initialize(parent);
    }

    void Meter::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_meter_create(nullptr));
    }
    void Meter::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_meter_create(parent.raw_ptr()));
    }

    std::shared_ptr<lv_meter_scale_t> Meter::add_scale() {
        return std::shared_ptr<lv_meter_scale_t>(lv_meter_add_scale(this->raw_ptr()));
    }

    void Meter::set_scale_ticks(std::shared_ptr<lv_meter_scale_t> scale, uint16_t cnt,
                                uint16_t width, uint16_t len, lv_color_t color) {
        lv_meter_set_scale_ticks(this->raw_ptr(), scale.get(), cnt, width, len, color);
    }

    void Meter::set_scale_major_ticks(std::shared_ptr<lv_meter_scale_t> scale, uint16_t nth,
                                      uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap) {
        lv_meter_set_scale_major_ticks(this->raw_ptr(), scale.get(), nth, width, len, color, label_gap);
    }
    
    void Meter::set_scale_range(std::shared_ptr<lv_meter_scale_t> scale, int32_t min,
                                int32_t max, uint32_t angle_range, uint32_t rotation) {
        lv_meter_set_scale_range(this->raw_ptr(), scale.get(), min, max, angle_range, rotation);
    }
    
    std::shared_ptr<lv_meter_indicator_t> Meter::add_needle_line(std::shared_ptr<lv_meter_scale_t> scale,
                                                                 uint16_t width, lv_color_t color,
                                                                 int16_t r_mod) {
        return std::shared_ptr<lv_meter_indicator_t>(
            lv_meter_add_needle_line(this->raw_ptr(), scale.get(), width, color, r_mod));
    }
    
    std::shared_ptr<lv_meter_indicator_t> Meter::add_needle_img(std::shared_ptr<lv_meter_scale_t> scale,
                                                                std::shared_ptr<void> src,
                                                                lv_coord_t pivot_x, lv_coord_t pivot_y) {
        return std::shared_ptr<lv_meter_indicator_t>(
            lv_meter_add_needle_img(this->raw_ptr(), scale.get(), src.get(), pivot_x, pivot_y));
    }
    
    std::shared_ptr<lv_meter_indicator_t> Meter::add_arc(std::shared_ptr<lv_meter_scale_t> scale,
                                                         uint16_t width, lv_color_t color,
                                                         int16_t r_mod) {
        return std::shared_ptr<lv_meter_indicator_t>(
            lv_meter_add_arc(this->raw_ptr(), scale.get(), width, color, r_mod));
    }
    
    std::shared_ptr<lv_meter_indicator_t> Meter::add_scale_lines(std::shared_ptr<lv_meter_scale_t> scale,
                                                                 lv_color_t color_start, lv_color_t color_end,
                                                                 bool local, int16_t width_mod) {
        return std::shared_ptr<lv_meter_indicator_t>(
            lv_meter_add_scale_lines(this->raw_ptr(), scale.get(), color_start, color_end, local, width_mod));
    }
    
    void Meter::set_indicator_value(std::shared_ptr<lv_meter_indicator_t> indic, int32_t value) {
        lv_meter_set_indicator_value(this->raw_ptr(), indic.get(), value);
    }

    void Meter::set_indicator_start_value(std::shared_ptr<lv_meter_indicator_t> indic, int32_t value) {
        lv_meter_set_indicator_start_value(this->raw_ptr(), indic.get(), value);
    }

    void Meter::set_indicator_end_value(std::shared_ptr<lv_meter_indicator_t> indic, int32_t value) {
        lv_meter_set_indicator_end_value(this->raw_ptr(), indic.get(), value);
    }

}