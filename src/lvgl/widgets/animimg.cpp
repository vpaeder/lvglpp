/** \file animimg.cpp
 *  \brief Implementation file for C++ wrapper for lv_animimg_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "animimg.h"

namespace lvgl::widgets {

    AnimatedImage::AnimatedImage() {
        this->initialize();
    }

    AnimatedImage::AnimatedImage(Object & parent) {
        this->initialize(parent);
    }

    void AnimatedImage::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_animimg_create(nullptr));
    }
    void AnimatedImage::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_animimg_create(parent.raw_ptr()));
    }

    void AnimatedImage::set_src(const std::vector<ImageDescriptor> & imgs) {
        this->dsc = std::make_unique<lv_img_dsc_t*[]>(imgs.size());
        for (size_t n=0; n<imgs.size(); n++) {
            // note that dsc doesn't store const lv_img_dsc_t* because lv_animimg_set_src
            // requires non-const
            this->dsc[n] = const_cast<lv_img_dsc_t*>(imgs[n].raw_ptr());
        }
        lv_animimg_set_src(this->raw_ptr(), this->dsc.get(), imgs.size());
    }

    void AnimatedImage::start() {
        lv_animimg_start(this->raw_ptr());
    }

    void AnimatedImage::set_duration(uint32_t duration) {
        lv_animimg_set_duration(this->raw_ptr(), duration);
    }

    void AnimatedImage::set_repeat_count(uint16_t count) {
        lv_animimg_set_repeat_count(this->raw_ptr(), count);
    }
}
