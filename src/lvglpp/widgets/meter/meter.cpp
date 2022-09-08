/** \file meter.cpp
 *  \brief Implementation file for C++ wrapper for lv_meter_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "meter.h"
#if LV_USE_METER != 0

#include "../../draw/image.h"

namespace lvgl::widgets {

    lv_meter_scale_t* Meter::add_scale() {
        return lv_meter_add_scale(this->raw_ptr());
    }

    void Meter::set_scale_ticks(lv_meter_scale_t* scale, uint16_t cnt,
                                uint16_t width, uint16_t len, lv_color_t color) {
        lv_meter_set_scale_ticks(this->raw_ptr(), scale, cnt, width, len, color);
    }

    void Meter::set_scale_major_ticks(lv_meter_scale_t* scale, uint16_t nth,
                                      uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap) {
        lv_meter_set_scale_major_ticks(this->raw_ptr(), scale, nth, width, len, color, label_gap);
    }
    
    void Meter::set_scale_range(lv_meter_scale_t* scale, int32_t min,
                                int32_t max, uint32_t angle_range, uint32_t rotation) {
        lv_meter_set_scale_range(this->raw_ptr(), scale, min, max, angle_range, rotation);
    }
    
    lv_meter_indicator_t* Meter::add_needle_line(lv_meter_scale_t* scale,
                                                 uint16_t width, lv_color_t color,
                                                 int16_t r_mod) {
        return lv_meter_add_needle_line(this->raw_ptr(), scale, width, color, r_mod);
    }
    
    lv_meter_indicator_t* Meter::add_needle_img(lv_meter_scale_t* scale,
                                                const ImageDescriptor & src,
                                                lv_coord_t pivot_x, lv_coord_t pivot_y) {
        return lv_meter_add_needle_img(this->raw_ptr(), scale, src.raw_ptr(), pivot_x, pivot_y);
    }

    lv_meter_indicator_t* Meter::add_needle_img(lv_meter_scale_t* scale,
                                                const std::string & src,
                                                lv_coord_t pivot_x, lv_coord_t pivot_y) {
        return lv_meter_add_needle_img(this->raw_ptr(), scale, src.c_str(), pivot_x, pivot_y);
    }

    lv_meter_indicator_t* Meter::add_arc(lv_meter_scale_t* scale,
                                         uint16_t width, lv_color_t color,
                                         int16_t r_mod) {
        return lv_meter_add_arc(this->raw_ptr(), scale, width, color, r_mod);
    }
    
    lv_meter_indicator_t* Meter::add_scale_lines(lv_meter_scale_t* scale,
                                                 lv_color_t color_start, lv_color_t color_end,
                                                 bool local, int16_t width_mod) {
        return lv_meter_add_scale_lines(this->raw_ptr(), scale, color_start, color_end, local, width_mod);
    }
    
    void Meter::set_indicator_value(lv_meter_indicator_t* indic, int32_t value) {
        lv_meter_set_indicator_value(this->raw_ptr(), indic, value);
    }

    void Meter::set_indicator_start_value(lv_meter_indicator_t* indic, int32_t value) {
        lv_meter_set_indicator_start_value(this->raw_ptr(), indic, value);
    }

    void Meter::set_indicator_end_value(lv_meter_indicator_t* indic, int32_t value) {
        lv_meter_set_indicator_end_value(this->raw_ptr(), indic, value);
    }

}
#endif // LV_USE_METER
