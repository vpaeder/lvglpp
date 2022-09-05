/** \file imgbtn.h
 *  \brief Header file for C++ wrapper for lv_imgbtn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_IMGBTN != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class ImageButton
     *  \brief Wraps a lv_imgbtn_t object.
     */
    class ImageButton : public Widget<lv_imgbtn_create> {
    public:
        using Widget::Widget;
        
        /** \fn void set_src_left_img(lv_imgbtn_state_t state, const ImageDescriptor & src)
         *  \brief Sets source of left image for given state from image buffer.
         *  \param state: button state.
         *  \param src: source image descriptor.
         */
        void set_src_left_img(lv_imgbtn_state_t state, const ImageDescriptor & src);

        /** \fn void set_src_left_str(lv_imgbtn_state_t state, const std::string & src)
         *  \brief Sets source of left image for given state from path or symbol name.
         *  \param state: button state.
         *  \param src: source image descriptor.
         */
        void set_src_left_str(lv_imgbtn_state_t state, const std::string & src);

        /** \fn void set_src_mid_img(lv_imgbtn_state_t state, const ImageDescriptor & src)
         *  \brief Sets source of middle image for given state from image buffer.
         *  \param state: button state.
         *  \param src: source image descriptor.
         */
        void set_src_mid_img(lv_imgbtn_state_t state, const ImageDescriptor & src);

        /** \fn void set_src_mid_str(lv_imgbtn_state_t state, const std::string & src)
         *  \brief Sets source of middle image for given state from path or symbol name.
         *  \param state: button state.
         *  \param src: source image descriptor.
         */
        void set_src_mid_str(lv_imgbtn_state_t state, const std::string & src);

        /** \fn void set_src_right_img(lv_imgbtn_state_t state, const ImageDescriptor & src)
         *  \brief Sets source of right image for given state from image buffer.
         *  \param state: button state.
         *  \param src: source image descriptor.
         */
        void set_src_right_img(lv_imgbtn_state_t state, const ImageDescriptor & src);

        /** \fn void set_src_right_str(lv_imgbtn_state_t state, const std::string & src)
         *  \brief Sets source of right image for given state from path or symbol name.
         *  \param state: button state.
         *  \param src: source image descriptor.
         */
        void set_src_right_str(lv_imgbtn_state_t state, const std::string & src);

        /** \fn void set_state(lv_imgbtn_state_t state)
         *  \brief Sets button state.
         *  \param state: code for button state.
         */
        void set_state(lv_imgbtn_state_t state);

        /** \fn lv_img_src_t get_src_left_type(lv_imgbtn_state_t state) const
         *  \brief Gets type of left image source for given state.
         *  \param state: code for button state.
         *  \returns code for image source.
         */
        lv_img_src_t get_src_left_type(lv_imgbtn_state_t state) const;

        /** \fn lv_img_src_t get_src_mid_type(lv_imgbtn_state_t state) const
         *  \brief Gets type of middle image source for given state.
         *  \param state: code for button state.
         *  \returns code for image source.
         */
        lv_img_src_t get_src_mid_type(lv_imgbtn_state_t state) const;

        /** \fn lv_img_src_t get_src_right_type(lv_imgbtn_state_t state) const
         *  \brief Gets type of right image source for given state.
         *  \param state: code for button state.
         *  \returns code for image source.
         */
        lv_img_src_t get_src_right_type(lv_imgbtn_state_t state) const;

        /** \fn const ImageDescriptor get_src_left_img(lv_imgbtn_state_t state) const
         *  \brief Gets left image source descriptor for given button state.
         *  \param state: code for button state.
         *  \returns the left image source descriptor.
         */
        const ImageDescriptor get_src_left_img(lv_imgbtn_state_t state) const;

        /** \fn const std::string get_src_left_str(lv_imgbtn_state_t state) const
         *  \brief Gets left image source path or symbol name for given button state.
         *  \param state: code for button state.
         *  \returns the left image source path or symbol name.
         */
        const std::string get_src_left_str(lv_imgbtn_state_t state) const;

        /** \fn const ImageDescriptor get_src_mid_img(lv_imgbtn_state_t state) const
         *  \brief Gets middle image source descriptor for given button state.
         *  \param state: code for button state.
         *  \returns the middle image source descriptor.
         */
        const ImageDescriptor get_src_mid_img(lv_imgbtn_state_t state) const;

        /** \fn const std::string get_src_mid_str(lv_imgbtn_state_t state) const
         *  \brief Gets middle image source path or symbol name for given button state.
         *  \param state: code for button state.
         *  \returns the middle image source path or symbol name.
         */
        const std::string get_src_mid_str(lv_imgbtn_state_t state) const;

        /** \fn const ImageDescriptor get_src_right_img(lv_imgbtn_state_t state) const
         *  \brief Gets right image source descriptor for given button state.
         *  \param state: code for button state.
         *  \returns the right image source descriptor.
         */
        const ImageDescriptor get_src_right_img(lv_imgbtn_state_t state) const;

        /** \fn const std::string get_src_right_str(lv_imgbtn_state_t state) const
         *  \brief Gets right image source path or symbol name for given button state.
         *  \param state: code for button state.
         *  \returns the right image source path or symbol name.
         */
        const std::string get_src_right_str(lv_imgbtn_state_t state) const;
    };

}
#endif // LV_USE_IMGBTN