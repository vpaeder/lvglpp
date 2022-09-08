/** \file indev.h
 *  \brief Implementation file for C++ wrapper for lv_indev_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "indev.h"
#include "group.h"
#include "object.h"

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::core {

    InputDevice::InputDevice() {
        lv_indev_drv_init(&(this->indev_drv));
        this->indev_drv.user_data = static_cast<void*>(this);
        this->indev_drv.read_cb = [](lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
            auto obj = reinterpret_cast<InputDevice*>(indev_drv->user_data);
            obj->read(data);
        };
        this->lv_obj = LvPointerType(lv_indev_drv_register(&(this->indev_drv)));
    }

    void InputDevice::update_driver() {
        lv_indev_drv_update(this->raw_ptr(), &this->indev_drv);
    }

    void InputDevice::set_display(lv_disp_t * disp) {
        this->indev_drv.disp = disp;
        this->update_driver();
    }

    void InputDevice::set_display(Display & disp) {
        this->set_display(disp.raw_ptr());
    }

    void InputDevice::set_type(lv_indev_type_t type) {
        this->indev_drv.type = type;
        this->update_driver();
    }

    void InputDevice::enable(bool en) {
        lv_indev_enable(this->raw_ptr(), en);
    }

    lv_indev_type_t InputDevice::get_type() const {
        return lv_indev_get_type(this->raw_ptr());
    }

    void InputDevice::reset(const Object & obj) {
        lv_indev_reset(this->raw_ptr(), const_cast<lv_obj_t*>(obj.raw_ptr()));
    }

    void InputDevice::reset_long_press() {
        lv_indev_reset_long_press(this->raw_ptr());
    }

    lv_dir_t InputDevice::get_gesture_dir() const {
        return lv_indev_get_gesture_dir(this->raw_ptr());
    }

    void InputDevice::wait_release() {
        lv_indev_wait_release(this->raw_ptr());
    }


    PointerInputDevice::PointerInputDevice() {
        this->set_type(LV_INDEV_TYPE_POINTER);
    }

    void PointerInputDevice::set_cursor(const Object & cursor) {
        lv_indev_set_cursor(this->raw_ptr(), const_cast<lv_obj_t*>(cursor.raw_ptr()));
    }

    lv_point_t PointerInputDevice::get_point() const {
        lv_point_t pt{};
        lv_indev_get_point(this->raw_ptr(), &pt);
        return pt;
    }

    lv_dir_t PointerInputDevice::get_scroll_dir() const {
        return lv_indev_get_scroll_dir(this->raw_ptr());
    }

    Object PointerInputDevice::get_scroll_obj() const {
        return Object(lv_indev_get_scroll_obj(this->raw_ptr()), false);
    }

    lv_point_t PointerInputDevice::get_vect() const {
        lv_point_t pt{};
        lv_indev_get_vect(this->raw_ptr(), &pt);
        return pt;
    }


    ButtonInputDevice::ButtonInputDevice() {
        this->set_type(LV_INDEV_TYPE_BUTTON);
    }

    void ButtonInputDevice::set_button_points(const std::vector<lv_point_t> & points) {
        this->points = std::make_unique<lv_point_t[]>(points.size());
        std::copy(points.begin(), points.end(), this->points.get());
        lv_indev_set_button_points(this->raw_ptr(), this->points.get());
    }


    KeypadInputDevice::KeypadInputDevice() {
        this->set_type(LV_INDEV_TYPE_KEYPAD);
    }

    void KeypadInputDevice::set_group(const Group & group) {
         lv_indev_set_group(this->raw_ptr(), const_cast<lv_group_t*>(group.raw_ptr()));
   }

    uint32_t KeypadInputDevice::get_key() const {
        return lv_indev_get_key(this->raw_ptr());
    }


    EncoderInputDevice::EncoderInputDevice() {
        this->set_type(LV_INDEV_TYPE_ENCODER);
    }

}
#endif // LV_USE_USER_DATA