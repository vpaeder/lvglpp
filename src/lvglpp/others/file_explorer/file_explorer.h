/** \file file_explorer.h
 *  \brief Header file for C++ wrapper for lv_file_explorer_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_FILE_EXPLORER != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class FileExplorer
     *  \brief Wraps a lv_file_explorer_t object.
     */
    class FileExplorer : public Widget<lv_file_explorer_create> {
    public:
        using Widget::Widget;

#if LV_FILE_EXPLORER_QUICK_ACCESS
        /** \brief Set quick access path.
         *  \param dir: quick access icon code.
         *  \param path: directory path.
         */
        void set_quick_access_path(lv_file_explorer_dir_t dir, const char * path);
        /** \brief Set quick access path.
         *  \param dir: quick access icon code.
         *  \param path: directory path.
         */
        void set_quick_access_path(lv_file_explorer_dir_t dir, const std::string & path);
#endif // LV_FILE_EXPLORER_QUICK_ACCESS

        /** \brief Set sorting strategy.
         *  \param sort: sorting strategy code.
         */
        void set_sort(lv_file_explorer_sort_t sort);

        /** \brief Get selected file name.
         *  \returns selected file name.
         */
        const std::string get_selected_file_name() const;

        /** \brief Get current path.
         *  \returns current path.
         */
        const std::string get_current_path() const;

        /** \brief Get object for file explorer header.
         *  \returns pointer to header object.
         */
        lv_obj_t * get_header() const;

        /** \brief Get object for file explorer quick access area.
         *  \returns pointer to quick access area object.
         */
        lv_obj_t * get_quick_access_area() const;

        /** \brief Get object for file explorer path label.
         *  \returns pointer to path label object.
         */
        lv_obj_t * get_path_label() const;

        /** \brief Get object for file explorer places list.
         *  \returns pointer to places list object.
         */
        lv_obj_t * get_places_list() const;

        /** \brief Get object for file explorer device list.
         *  \returns pointer to device list object.
         */
        lv_obj_t * get_device_list() const;

        /** \brief Get object for file explorer file table.
         *  \returns pointer to file table object.
         */
        lv_obj_t * get_file_table() const;

        /** \brief Get file explorer sorting strategy.
         *  \returns code for sorting strategy.
         */
        lv_file_explorer_sort_t get_sort() const;

        /** \brief Open directory.
         *  \param dir: directory path.
         */
        void open_dir(const char * dir);
        /** \brief Open directory.
         *  \param dir: directory path.
         */
        void open_dir(const std::string & dir);
    };

}
#endif // LV_USE_FILE_EXPLORER