/** \file msgbox.cpp
 *  \brief Implementation file for C++ wrapper for lv_msgbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "msgbox.h"
#if LV_USE_MSGBOX

namespace lvgl::widgets {

    MessageBox::MessageBox(const std::string & title, const std::string & txt,
                           const std::vector<std::string> & btn_txts,
                           bool add_close_btn) {
        this->initialize(title, txt, btn_txts, add_close_btn);
    }

    MessageBox::MessageBox(Object & parent, const std::string & title, const std::string & txt,
                           const std::vector<std::string> & btn_txts,
                           bool add_close_btn) {
        this->initialize(parent, title, txt, btn_txts, add_close_btn);
    }

    void MessageBox::initialize(const std::string & title, const std::string & txt,
                                const std::vector<std::string> & btn_txts,
                                bool add_close_btn) {
        const char ** btxts = nullptr;
        if (btn_txts.size()>0) {
            this->btn_txts = str_vector_to_char_array(btn_txts);
            btxts = (const char**)this->btn_txts.get(); // see ButtonMatrix::set_map for explanation
        }
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(
            lv_msgbox_create(nullptr,
                             title.c_str(),
                             txt.c_str(),
                             btxts,
                             add_close_btn)
        );
        
    }

    void MessageBox::initialize(Object & parent, const std::string & title, const std::string & txt,
                                const std::vector<std::string> & btn_txts,
                                bool add_close_btn) {
        const char ** btxts = nullptr;
        if (btn_txts.size()>0) {
            this->btn_txts = str_vector_to_char_array(btn_txts);
            btxts = (const char**)this->btn_txts.get(); // see ButtonMatrix::set_map for explanation
        }
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(
            lv_msgbox_create(parent.raw_ptr(),
                             title.c_str(),
                             txt.c_str(),
                             btxts,
                             add_close_btn)
        );
    }

    Object MessageBox::get_title() const {
        return Object(lv_msgbox_get_title(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    Object MessageBox::get_close_btn() const {
        return Object(lv_msgbox_get_close_btn(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    Object MessageBox::get_text() const {
        return Object(lv_msgbox_get_text(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    Object MessageBox::get_content() const {
        return Object(lv_msgbox_get_content(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    Object MessageBox::get_btns() const {
        return Object(lv_msgbox_get_btns(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    uint16_t MessageBox::get_active_btn() const {
        return lv_msgbox_get_active_btn(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    std::string MessageBox::get_active_btn_text() const {
        return std::string(lv_msgbox_get_active_btn_text(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    void MessageBox::close() {
        lv_msgbox_close(this->raw_ptr());
    }

    void MessageBox::close_async() {
        lv_msgbox_close_async(this->raw_ptr());
    }

}
#endif // LV_USE_MSGBOX