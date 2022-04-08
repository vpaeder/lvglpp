/** \file timer.h
 *  \brief Header file for C++ wrapper for LVGL timer functions.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_thin_wrapper.h"

namespace lvgl::misc {

    /** \class Timer
     *  \brief Wraps a lv_timer_t object. This is a base class to construct
     *  timers for LVGL. Create a derived class and override the callback function
     *  to define the timer behaviour.
     */
    class Timer : public ThinPointerWrapper<lv_timer_t, lv_timer_del> {
    protected:
        /** \fn virtual void callback(lv_timer_t * timer)
         *  \brief Function called periodically during execution.
         *  \param timer: pointer to timer instance.
         */
        virtual void callback(lv_timer_t * timer) = 0;

        /** \fn void set_callback()
         *  \brief Used internally to set callback function.
         */
        void set_callback();

    public:
        using ThinPointerWrapper::ThinPointerWrapper;

        /** \fn Timer()
         *  \brief Default constructor.
         */
        Timer();

        /** \fn Timer(uint32_t period)
         *  \brief Constructor with parameters.
         *  \param period: timer period, in ms.
         */
        Timer(uint32_t period);

        /** \fn void pause()
         *  \brief Pauses timer execution.
         */
        void pause();

        /** \fn void resume()
         *  \brief Resumes timer execution.
         */
        void resume();

        /** \fn void set_period(uint32_t period)
         *  \brief Sets timer period.
         *  \param period: timer period, in ms.
         */
        void set_period(uint32_t period);

        /** \fn void set_ready()
         *  \brief Sets timer as ready.
         */
        void set_ready();

        /** \fn void set_repeat_count(int32_t repeat_count)
         *  \brief Sets timer repetition count.
         *  \param repeat_count: number of times timer callback gets called.
         */
        void set_repeat_count(int32_t repeat_count);

        /** \fn void reset()
         *  \brief Resets timer.
         */
        void reset();

    };


     /** \class GenericTimer
     *  \brief This is a timer class used to wrap lv_timer_t instances
     *  returned from LVGL functions. The C++ callback isn't used here.
     */
   class GenericTimer : public Timer {
    protected:
        /** \fn virtual void callback(lv_timer_t * timer)
         *  \brief Function called periodically during execution.
         *  \param timer: pointer to timer instance.
         */
        void callback(lv_timer_t * timer) override {}
    };

}