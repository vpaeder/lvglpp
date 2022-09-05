/** \file animimg.h
 *  \brief Header file for C++ wrapper for lv_animimg_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../draw/image.h"
#include "../../core/object.h"

#if LV_USE_ANIMIMG != 0

/** \namespace lvgl::widgets
 *  \brief LVGL widgets.
 */
namespace lvgl::widgets {

    using namespace lvgl::core;

    /** \class AnimatedImage
     *  \brief Wraps a lv_animimg_t object.
     */
    class AnimatedImage : public Widget<lv_animimg_create> {
    private:
        /** \property std::unique_ptr<lv_img_dsc_t*[]> dsc
         *  \brief A list of pointers to the animation images.
         */
        std::unique_ptr<lv_img_dsc_t*[]> dsc;
    
    public:
        using Widget::Widget;
        
        /** \fn void set_src(const std::vector<ImageDescriptor> & imgs)
         *  \brief Sets images.
         *  \param imgs: a list of images.
         */
        void set_src(const std::vector<ImageDescriptor> & imgs);

        /** \fn void start()
         *  \brief Starts animation.
         */
        void start();

        /** \fn void set_duration(uint32_t duration)
         *  \brief Sets the animation duration.
         *  \param duration: animation duration, in ms.
         */
        void set_duration(uint32_t duration);

        /** \fn void set_repeat_count(uint16_t count)
         *  \brief Sets the animation repeat count.
         *  \param count: repeat count.
         */
        void set_repeat_count(uint16_t count);

    };

}
#endif // LV_USE_ANIMIMG