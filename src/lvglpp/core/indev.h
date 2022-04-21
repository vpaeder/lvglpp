/** \file indev.h
 *  \brief Header file for C++ wrapper for lv_indev_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "display.h"
#include "../misc/timer.h"
#include "../lv_wrapper.h"

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::core {

    class Group;
    class Object;

    /** \class InputDevice
     *  \brief Wraps a lv_indev_t object. This is a base class to define
     *  specialized input devices.
     */
    class InputDevice : public PointerWrapper<lv_indev_t, lv_indev_delete> {
    protected:
        /** \property lv_indev_drv_t indev_drv
         *  \brief Input device driver instance.
         */
        lv_indev_drv_t indev_drv;

        /** \property virtual void read(lv_indev_data_t * data)
         *  \brief Callback to read touchpad data.
         *  \param data: a pointer to the target data structure.
         */
        virtual void read(lv_indev_data_t * data) {}
    
        /** \fn void set_type(lv_indev_type_t type)
         *  \brief Sets the device type.
         *  \param type: code for device type (LV_INDEV_TYPE_POINTER/KEYPAD/BUTTON/ENCODER).
         */
        void set_type(lv_indev_type_t type);

        /** \fn void update_driver()
         *  \brief Updates driver with stored values.
         */
        void update_driver();

    public:
        using PointerWrapper::PointerWrapper;

        /** \fn InputDevice()
         *  \brief Default constructor.
         */
        InputDevice();

        /** \fn void set_display(lv_disp_t * disp)
         *  \brief Sets the associated display.
         *  \param disp: pointer to a lv_disp_t instance.
         */
        void set_display(lv_disp_t * disp);

        /** \fn void set_display(Display & disp)
         *  \brief Sets the associated display.
         *  \param disp: Display instance.
         */
        void set_display(Display & disp);

        /** \fn void enable(bool en)
         *  \brief Enables/disables input device.
         *  \param en: if true, device is enabled.
         */
        void enable(bool en);

        /** \fn lv_indev_type_t get_type() const
         *  \brief Gets input device type.
         *  \returns code for input device type.
         */
        lv_indev_type_t get_type() const;

        /** \fn void reset(const Object & obj)
         *  \brief Resets input device following a trigger from given object.
         *  \param obj: object issuing trigger.
         */
        void reset(const Object & obj);

        /** \fn void reset_long_press()
         *  \brief Resets device's long press state.
         */
        void reset_long_press();

        /** \fn lv_dir_t get_gesture_dir() const
         *  \brief Gets current gesture direction.
         *  \returns code for gesture direction.
         */
        lv_dir_t get_gesture_dir() const;

        /** \fn void wait_release()
         *  \brief Waits until next release event.
         */
        void wait_release();

    };


    /** \fn template <class T> T indev_get_act()
     *  \brief Gets active input device.
     *  \tparam T: type of input device.
     *  \returns input device object.
     */
    template <class T> T indev_get_act() {
        return T(lv_indev_get_act(), false);
    }


    /** \class PointerInputDevice
     *  \brief Input device with a pointer (touchpad, mouse, ...).
     */
    class PointerInputDevice : public InputDevice {
    public:
        using InputDevice::InputDevice;
        /** \fn PointerInputDevice()
         *  \brief Default constructor.
         */
        PointerInputDevice();

        /** \fn void set_cursor(const Object & cursor)
         *  \brief Sets device cursor.
         *  \param cursor: object that will be used as cursor.
         */
        void set_cursor(const Object & cursor);

        /** \fn lv_point_t get_point() const
         *  \brief Gets the last recorded point.
         *  \returns point object.
         */
        lv_point_t get_point() const;

        /** \fn lv_dir_t get_scroll_dir() const
         *  \brief Gets scroll direction.
         *  \returns code for scroll direction.
         */
        lv_dir_t get_scroll_dir() const;

        /** \fn Object get_scroll_obj() const
         *  \brief Gets scrolled object.
         *  \returns scrolled object.
         */
        Object get_scroll_obj() const;

        /** \fn lv_point_t get_vect() const
         *  \brief Gets the direction vector.
         *  \returns direction vector.
         */
        lv_point_t get_vect() const;

    };

    /** \class ButtonInputDevice
     *  \brief Input device with a discrete number of fixed buttons.
     */
    class ButtonInputDevice : public PointerInputDevice {
    private:
        /** \property std::unique_ptr<lv_point_t[]> points
         *  \brief A pointer to the coordinate points corresponding to the buttons.
         */
        std::unique_ptr<lv_point_t[]> points;

    public:
        using PointerInputDevice::PointerInputDevice;
        /** \fn ButtonInputDevice()
         *  \brief Default constructor.
         */
        ButtonInputDevice();

        /** \fn void set_button_points(const std::vector<lv_point_t> & points)
         *  \brief Sets the coordinates that the buttons correspond to.
         *  \param points: coordinates points.
         */
        void set_button_points(const std::vector<lv_point_t> & points);
    };

    /** \class KeypadInputDevice
     *  \brief Input device with keys.
     */
    class KeypadInputDevice : public InputDevice {
    public:
        using InputDevice::InputDevice;
        /** \fn KeypadInputDevice()
         *  \brief Default constructor.
         */
        KeypadInputDevice();

        /** \fn void set_group(const Group & group)
         *  \brief Sets the destination group of keypad events.
         *  \param group: group instance.
         */
        void set_group(const Group & group);

        /** \fn uint32_t get_key() const
         *  \brief Gets key pressed last.
         *  \returns index of key.
         */
        uint32_t get_key() const;

    };


    /** \class EncoderInputDevice
     *  \brief Input device with encoder features.
     */
    class EncoderInputDevice : public InputDevice {
    public:
        using InputDevice::InputDevice;
        /** \fn EncoderInputDevice()
         *  \brief Default constructor.
         */
        EncoderInputDevice();
    };

}
#endif // LV_USE_USER_DATA