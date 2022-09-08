/** \file imgbtn.cpp
 *  \brief Implementation file for C++ wrapper for lv_imgbtn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "imgbtn.h"
#if LV_USE_IMGBTN != 0

#include "../../draw/image.h"

namespace lvgl::widgets {

    void ImageButton::set_src_left_img(lv_imgbtn_state_t state, const ImageDescriptor & src) {
        reinterpret_cast<lv_imgbtn_t*>(this->raw_ptr())->img_src_left[state] = src.raw_ptr();
    }

    void ImageButton::set_src_left_str(lv_imgbtn_state_t state, const std::string & src) {
        reinterpret_cast<lv_imgbtn_t*>(this->raw_ptr())->img_src_left[state] = src.c_str();
    }

    void ImageButton::set_src_mid_img(lv_imgbtn_state_t state, const ImageDescriptor & src) {
        reinterpret_cast<lv_imgbtn_t*>(this->raw_ptr())->img_src_mid[state] = src.raw_ptr();
    }

    void ImageButton::set_src_mid_str(lv_imgbtn_state_t state, const std::string & src) {
        reinterpret_cast<lv_imgbtn_t*>(this->raw_ptr())->img_src_mid[state] = src.c_str();
    }

    void ImageButton::set_src_right_img(lv_imgbtn_state_t state, const ImageDescriptor & src) {
        reinterpret_cast<lv_imgbtn_t*>(this->raw_ptr())->img_src_right[state] = src.raw_ptr();
    }

    void ImageButton::set_src_right_str(lv_imgbtn_state_t state, const std::string & src) {
        reinterpret_cast<lv_imgbtn_t*>(this->raw_ptr())->img_src_right[state] = src.c_str();
    }

    void ImageButton::set_state(lv_imgbtn_state_t state) {
        lv_imgbtn_set_state(this->raw_ptr(), state);
    }

    lv_img_src_t ImageButton::get_src_left_type(lv_imgbtn_state_t state) const {
        return lv_img_src_get_type(
            reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_left[state]);
    }

    lv_img_src_t ImageButton::get_src_mid_type(lv_imgbtn_state_t state) const {
        return lv_img_src_get_type(
            reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_mid[state]);
    }

    lv_img_src_t ImageButton::get_src_right_type(lv_imgbtn_state_t state) const {
        return lv_img_src_get_type(
            reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_right[state]);
    }

    const ImageDescriptor ImageButton::get_src_left_img(lv_imgbtn_state_t state) const {
        assert(this->get_src_left_type(state) == LV_IMG_SRC_VARIABLE);
        return ImageDescriptor(
            const_cast<lv_img_dsc_t*>(reinterpret_cast<const lv_img_dsc_t*>(
                reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_left[state]
            )
        ));
    }

    const std::string ImageButton::get_src_left_str(lv_imgbtn_state_t state) const {
        auto src_type = this->get_src_left_type(state);
        assert(src_type == LV_IMG_SRC_FILE || src_type == LV_IMG_SRC_SYMBOL);
        return std::string(
            const_cast<char*>(reinterpret_cast<const char*>(
                reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_left[state]
            )
        ));
    }

    const ImageDescriptor ImageButton::get_src_mid_img(lv_imgbtn_state_t state) const {
        assert(this->get_src_mid_type(state) == LV_IMG_SRC_VARIABLE);
        return ImageDescriptor(
            const_cast<lv_img_dsc_t*>(reinterpret_cast<const lv_img_dsc_t*>(
                reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_mid[state]
            )
        ));
    }

    const std::string ImageButton::get_src_mid_str(lv_imgbtn_state_t state) const {
        auto src_type = this->get_src_mid_type(state);
        assert(src_type == LV_IMG_SRC_FILE || src_type == LV_IMG_SRC_SYMBOL);
        return std::string(
            const_cast<char*>(reinterpret_cast<const char*>(
                reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_mid[state]
            )
        ));
    }

    const ImageDescriptor ImageButton::get_src_right_img(lv_imgbtn_state_t state) const {
        assert(this->get_src_right_type(state) == LV_IMG_SRC_VARIABLE);
        return ImageDescriptor(
            const_cast<lv_img_dsc_t*>(reinterpret_cast<const lv_img_dsc_t*>(
                reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_right[state]
            )
        ));
    }

    const std::string ImageButton::get_src_right_str(lv_imgbtn_state_t state) const {
        auto src_type = this->get_src_right_type(state);
        assert(src_type == LV_IMG_SRC_FILE || src_type == LV_IMG_SRC_SYMBOL);
        return std::string(
            const_cast<char*>(reinterpret_cast<const char*>(
                reinterpret_cast<const lv_imgbtn_t*>(this->raw_ptr())->img_src_right[state]
            )
        ));
    }

}
#endif // LV_USE_IMGBTN