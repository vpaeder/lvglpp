/** \file event.cpp
 *  \brief Implementation file for C++ wrapper for LVGL events.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "../misc/anim.h"
#include "event.h"
#include "object.h"
#include "indev.h"

namespace lvgl::core {

    lv_event_code_t Event::get_code() const {
        return lv_event_get_code(const_cast<lv_event_t*>(this->raw_ptr()));
    }

#if LV_USE_USER_DATA
    void * Event::get_user_data() const {
        return lv_event_get_user_data(const_cast<lv_event_t*>(this->raw_ptr()));
    }
#endif // LV_USE_USER_DATA

    void Event::stop_bubbling() {
        lv_event_stop_bubbling(this->raw_ptr());
    }

    void Event::stop_processing() {
        lv_event_stop_processing(this->raw_ptr());
    }

    uint32_t Event::register_id() {
        return lv_event_register_id();
    }

#if LV_USE_USER_DATA
    InputDevice Event::get_indev() const {
        return InputDevice(lv_event_get_indev(const_cast<lv_event_t*>(this->raw_ptr())), false);
    }
#else
    lv_indev_t * Event::get_indev() const {
        return lv_event_get_indev(const_cast<lv_event_t*>(this->raw_ptr()));
    }
#endif // LV_USE_USER_DATA

    lv_obj_draw_part_dsc_t* Event::get_draw_part_dsc() const {
        return lv_event_get_draw_part_dsc(const_cast<lv_event_t*>(this->raw_ptr()));
    }

    lv_draw_ctx_t* Event::get_draw_ctx() const {
        return lv_event_get_draw_ctx(const_cast<lv_event_t*>(this->raw_ptr()));
    }

    const Area Event::get_old_size() const {
        return Area(const_cast<lv_area_t*>(
            lv_event_get_old_size(const_cast<lv_event_t*>(this->raw_ptr()))));
    }

    uint32_t Event::get_key() const {
        return lv_event_get_key(const_cast<lv_event_t*>(this->raw_ptr()));
    }

    Animation Event::get_scroll_anim() const {
        return Animation(
            lv_event_get_scroll_anim(const_cast<lv_event_t*>(this->raw_ptr())));
    }

    void Event::set_ext_draw_size(lv_coord_t size) {
        lv_event_set_ext_draw_size(this->raw_ptr(), size);
    }

    lv_point_t* Event::get_self_size_info() const {
        return lv_event_get_self_size_info(const_cast<lv_event_t*>(this->raw_ptr()));
    }

    lv_hit_test_info_t* Event::get_hit_test_info() const {
        return lv_event_get_hit_test_info(const_cast<lv_event_t*>(this->raw_ptr()));
    }

    const Area Event::get_cover_area() const {
        return Area(const_cast<lv_area_t*>(
            lv_event_get_cover_area(const_cast<lv_event_t*>(this->raw_ptr()))));
    }

    void Event::set_cover_res(lv_cover_res_t res) {
        lv_event_set_cover_res(this->raw_ptr(), res);
    }

}