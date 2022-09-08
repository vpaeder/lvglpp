/** \file list.cpp
 *  \brief Implementation file for C++ wrapper for lv_list_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "list.h"
#if LV_USE_LIST

#include "../label/label.h"
#include "../button/button.h"
#include "../../draw/image.h"

namespace lvgl::widgets {

    Label List::add_text(const std::string & txt) {
        return Label(lv_list_add_text(this->raw_ptr(), txt.c_str()), false);
    }

    Button List::add_btn(const std::string & icon, const std::string & txt) {
        return Button(lv_list_add_btn(this->raw_ptr(), icon.c_str(), txt.c_str()), false);
    }

    Button List::add_btn(const ImageDescriptor & icon, const std::string & txt) {
        return Button(lv_list_add_btn(this->raw_ptr(), icon.raw_ptr(), txt.c_str()), false);
    }

    Button List::add_btn(const std::string & txt) {
        return Button(lv_list_add_btn(this->raw_ptr(), nullptr, txt.c_str()), false);
    }

    std::string List::get_btn_text(const Button & btn) const {
        return std::string(lv_list_get_btn_text(const_cast<lv_cls_ptr>(this->raw_ptr()),
                                                const_cast<lv_obj_t*>(btn.raw_ptr())));
    }

}
#endif // LV_USE_LIST