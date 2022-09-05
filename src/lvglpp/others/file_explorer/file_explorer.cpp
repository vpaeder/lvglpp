/** \file file_explorer.cpp
 *  \brief Implementation file for C++ wrapper for lv_file_explorer_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "file_explorer.h"
#if LV_USE_FILE_EXPLORER != 0

namespace lvgl::widgets {

#if LV_FILE_EXPLORER_QUICK_ACCESS
        void FileExplorer::set_quick_access_path(lv_file_explorer_dir_t dir, const char * path) {
            lv_file_explorer_set_quick_access_path(this->raw_ptr(), dir, path);
        }
        void FileExplorer::set_quick_access_path(lv_file_explorer_dir_t dir, const std::string & path) {
            lv_file_explorer_set_quick_access_path(this->raw_ptr(), dir, path.c_str());
        }
#endif // LV_FILE_EXPLORER_QUICK_ACCESS

        void FileExplorer::set_sort(lv_file_explorer_sort_t sort) {
            lv_file_explorer_set_sort(this->raw_ptr(), sort);
        }

        const std::string FileExplorer::get_selected_file_name() const {
            return std::string(lv_file_explorer_get_selected_file_name(
                const_cast<lv_cls_ptr>(this->raw_ptr()))
            );
        }

        const std::string FileExplorer::get_current_path() const {
            return std::string(
                lv_file_explorer_get_current_path(const_cast<lv_cls_ptr>(this->raw_ptr()))
            );
        }

        lv_obj_t * FileExplorer::get_header() const {
            return lv_file_explorer_get_header(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        lv_obj_t * FileExplorer::get_quick_access_area() const {
            return lv_file_explorer_get_quick_access_area(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        lv_obj_t * FileExplorer::get_path_label() const {
            return lv_file_explorer_get_path_label(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        lv_obj_t * FileExplorer::get_places_list() const {
            return lv_file_explorer_get_places_list(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        lv_obj_t * FileExplorer::get_device_list() const {
            return lv_file_explorer_get_device_list(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        lv_obj_t * FileExplorer::get_file_table() const {
            return lv_file_explorer_get_file_table(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        lv_file_explorer_sort_t FileExplorer::get_sort() const {
            return lv_file_explorer_get_sort(const_cast<lv_cls_ptr>(this->raw_ptr()));
        }

        void FileExplorer::open_dir(const char * dir) {
            lv_file_explorer_open_dir(this->raw_ptr(), dir);
        }
        void FileExplorer::open_dir(const std::string & dir) {
            lv_file_explorer_open_dir(this->raw_ptr(), dir.c_str());
        }
}
#endif // LV_USE_FILE_EXPLORER