/** \file timer.cpp
 *  \brief Implementation file for C++ wrapper for LVGL timer functions.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "timer.h"

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::misc {

        Timer::Timer() {
            this->lv_obj = LvPointerType(lv_timer_create_basic());
            this->set_callback();
        }

        Timer::Timer(uint32_t period) {
            this->lv_obj = LvPointerType(lv_timer_create_basic());
            this->set_callback();
            this->set_period(period);
        }

        void Timer::set_callback() {
            auto f = [] (lv_timer_t * timer) {
                auto obj = reinterpret_cast<Timer*>(timer->user_data);
                obj->callback(*obj);
            };
            this->raw_ptr()->user_data = static_cast<void*>(this);
            lv_timer_set_cb(this->raw_ptr(), f);
        }

        void Timer::set_callback(TimerCb timer_cb) {
            auto f = [] (lv_timer_t * timer) {
                auto cb = reinterpret_cast<TimerCb>(timer->user_data);
                auto t = Timer(timer, false);
                cb(t);
            };
            this->raw_ptr()->user_data = reinterpret_cast<void*>(timer_cb);
            lv_timer_set_cb(this->raw_ptr(), f);
        }

        void Timer::pause() {
            lv_timer_pause(this->raw_ptr());
        }

        void Timer::resume() {
            lv_timer_resume(this->raw_ptr());
        }

        void Timer::set_period(uint32_t period) {
            lv_timer_set_period(this->raw_ptr(), period);
        }

        void Timer::set_ready() {
            lv_timer_ready(this->raw_ptr());
        }

        void Timer::set_repeat_count(int32_t repeat_count) {
            lv_timer_set_repeat_count(this->raw_ptr(), repeat_count);
        }

        void Timer::reset() {
            lv_timer_reset(this->raw_ptr());
        }

}
#endif // LV_USE_USER_DATA
