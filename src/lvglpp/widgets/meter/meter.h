/** \file meter.h
 *  \brief Header file for C++ wrapper for lv_meter_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_METER != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Meter
     *  \brief Wraps a lv_meter_t object.
     */
    class Meter : public Widget<lv_meter_create> {
    public:
        using Widget::Widget;

        /** \fn lv_meter_scale_t* add_scale()
         *  \brief Creates a new scale for the meter.
         *  \returns a pointer to the new scale object.
         */
        lv_meter_scale_t* add_scale();

        /** \fn void set_scale_ticks(lv_meter_scale_t* scale, uint16_t cnt,
         *                           uint16_t width, uint16_t len, lv_color_t color);
         *  \brief Sets the ticks of a scale.
         *  \param scale: pointer to a scale object.
         *  \param cnt: number of ticks.
         *  \param width: width of tick lines.
         *  \param len: length of tick lines.
         *  \param color: tick color.
         */
        void set_scale_ticks(lv_meter_scale_t* scale, uint16_t cnt,
                             uint16_t width, uint16_t len, lv_color_t color);

        /** \fn void set_scale_major_ticks(lv_meter_scale_t* scale, uint16_t nth,
         *                                 uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap);
         *  \brief Sets the major ticks of a scale.
         *  \param scale: pointer to a scale object.
         *  \param nth: makes every nth tick a major tick.
         *  \param width: width of tick lines.
         *  \param len: length of tick lines.
         *  \param color: tick color.
         *  \param label_gap: gap between the tick and the label.
         */
        void set_scale_major_ticks(lv_meter_scale_t* scale, uint16_t nth,
                                   uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap);
        
        /** \fn void set_scale_range(lv_meter_scale_t* scale, int32_t min,
         *                           int32_t max, uint32_t angle_range, uint32_t rotation);
         *  \brief Sets the range of a scale.
         *  \param scale: pointer to a scale object.
         *  \param min: scale minimum.
         *  \param max: scale maximum.
         *  \param angle_range: angular range.
         *  \param rotation: angular offset from 3 o'clock position.
         */
        void set_scale_range(lv_meter_scale_t* scale, int32_t min,
                             int32_t max, uint32_t angle_range, uint32_t rotation);
        
        /** \fn lv_meter_indicator_t* add_needle_line(lv_meter_scale_t* scale,
         *                                            uint16_t width, lv_color_t color, int16_t r_mod);
         *  \brief Adds a needle line indicator to the meter.
         *  \param scale: pointer to a scale object.
         *  \param width: line width.
         *  \param color: line color.
         *  \param r_mod: radius modifier to compute line length
         *  \returns a pointer to the indicator object.
         */
        lv_meter_indicator_t* add_needle_line(lv_meter_scale_t* scale,
                                              uint16_t width, lv_color_t color, int16_t r_mod);
        
        /** \fn lv_meter_indicator_t* add_needle_img(lv_meter_scale_t* scale,
         *                                           const ImageDescriptor & src,
         *                                           lv_coord_t pivot_x, lv_coord_t pivot_y);
         *  \brief Adds a needle image indicator to the meter.
         *  \param scale: pointer to a scale object.
         *  \param src: pointer to an image buffer.
         *  \param pivot_x: horizontal coordinate of pivot point.
         *  \param pivot_y: vertical coordinate of pivot point.
         *  \returns a pointer to the indicator object.
         */
        lv_meter_indicator_t* add_needle_img(lv_meter_scale_t* scale,
                                             const ImageDescriptor & src,
                                             lv_coord_t pivot_x, lv_coord_t pivot_y);

        /** \fn lv_meter_indicator_t* add_needle_img(lv_meter_scale_t* scale,
         *                                           const std::string & src,
         *                                           lv_coord_t pivot_x, lv_coord_t pivot_y);
         *  \brief Adds a needle image indicator to the meter.
         *  \param scale: pointer to a scale object.
         *  \param src: pointer to an image path.
         *  \param pivot_x: horizontal coordinate of pivot point.
         *  \param pivot_y: vertical coordinate of pivot point.
         *  \returns a pointer to the indicator object.
         */
        lv_meter_indicator_t* add_needle_img(lv_meter_scale_t* scale,
                                             const std::string & src,
                                             lv_coord_t pivot_x, lv_coord_t pivot_y);

        /** \fn lv_meter_indicator_t* add_arc(lv_meter_scale_t* scale,
         *                                    uint16_t width, lv_color_t color,
         *                                    int16_t r_mod);
         *  \brief Adds an arc indicator to the meter.
         *  \param scale: pointer to a scale object.
         *  \param width: arc width.
         *  \param color: arc color.
         *  \param r_mod: radius modifier to compute arc's outer radius.
         *  \returns a pointer to the indicator object.
         */
        lv_meter_indicator_t* add_arc(lv_meter_scale_t* scale,
                                      uint16_t width, lv_color_t color,
                                      int16_t r_mod);
        
        /** \fn lv_meter_indicator_t* add_scale_lines(lv_meter_scale_t* scale,
         *                                            lv_color_t color_start, lv_color_t color_end,
         *                                            bool local, int16_t width_mod);
         *  \brief Adds an indicator with scale lines to the meter.
         *  \param scale: pointer to a scale object.
         *  \param color_start: start color.
         *  \param color_end: end color.
         *  \param local: if true, color gradient is calculated between indicator's
         *                start and end values; if false, scale min and max values
         *                are used.
         *  \param width_mod: modifies the width of the tick lines.
         *  \returns a pointer to the indicator object.
         */
        lv_meter_indicator_t* add_scale_lines(lv_meter_scale_t* scale,
                                              lv_color_t color_start, lv_color_t color_end,
                                              bool local, int16_t width_mod);
        
        /** \fn void set_indicator_value(lv_meter_indicator_t* indic, int32_t value)
         *  \brief Sets the value of an indicator.
         *  \param indic: pointer to an indicator object.
         *  \param value: value to set.
         */
        void set_indicator_value(lv_meter_indicator_t* indic, int32_t value);

        /** \fn void set_indicator_start_value(lv_meter_indicator_t* indic, int32_t value)
         *  \brief Sets the start value of an indicator.
         *  \param indic: pointer to an indicator object.
         *  \param value: value to set.
         */
        void set_indicator_start_value(lv_meter_indicator_t* indic, int32_t value);

        /** \fn void set_indicator_end_value(lv_meter_indicator_t* indic, int32_t value)
         *  \brief Sets the end value of an indicator.
         *  \param indic: pointer to an indicator object.
         *  \param value: value to set.
         */
        void set_indicator_end_value(lv_meter_indicator_t* indic, int32_t value);

    };

}
#endif // LV_USE_METER
