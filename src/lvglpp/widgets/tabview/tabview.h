/** \file tabview.h
 *  \brief Header file for C++ wrapper for lv_tabview_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_TABVIEW

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Tabview
     *  \brief Wraps a lv_tabview_t object.
     */
    class Tabview : public Object {
    protected:
        /** \fn void initialize(lv_dir_t tab_pos, lv_coord_t tab_size)
         *  \brief Initialize object with parameters.
         *  \param tab_pos: orientation of tabs (LV_DIR_TOP/BOTTOM/LEFT/RIGHT).
         *  \param tab_size: tab size.
         */
        void initialize(lv_dir_t tab_pos, lv_coord_t tab_size);
        /** \fn void initialize(Object & parent, lv_dir_t tab_pos, lv_coord_t tab_size);
         *  \brief Initialize object with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param tab_pos: orientation of tabs (LV_DIR_TOP/BOTTOM/LEFT/RIGHT).
         *  \param tab_size: tab size.
         */
        void initialize(Object & parent, lv_dir_t tab_pos, lv_coord_t tab_size);
    
    public:
        Tabview() = delete;
        Tabview(Object & parent) = delete;
        /** \fn Tabview(lv_dir_t tab_pos, lv_coord_t tab_size);
         *  \brief Constructor with parameters.
         *  \param tab_pos: orientation of tabs (LV_DIR_TOP/BOTTOM/LEFT/RIGHT).
         *  \param tab_size: tab size.
         */
        Tabview(lv_dir_t tab_pos, lv_coord_t tab_size);
        /** \fn Tabview(Object & parent, lv_dir_t tab_pos, lv_coord_t tab_size)
         *  \brief Constructor with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param tab_pos: orientation of tabs (LV_DIR_TOP/BOTTOM/LEFT/RIGHT).
         *  \param tab_size: tab size.
         */
        Tabview(Object & parent, lv_dir_t tab_pos, lv_coord_t tab_size);

        /** \fn Object add_tab(const std::string & name)
         *  \brief Adds a tab with given name.
         *  \param name: tab name.
         *  \returns object for new tab.
         */
        Object add_tab(const std::string & name);

        /** \fn void rename_tab(uint32_t tab_id, const char * new_name)
         *  \brief Rename tab at given index.
         *  \param tab_id: tab index.
         *  \param new_name: new tab name.
         */
        void rename_tab(uint32_t tab_id, const char * new_name);
        /** \fn void rename_tab(uint32_t tab_id, const std::string & new_name)
         *  \brief Rename tab at given index.
         *  \param tab_id: tab index.
         *  \param new_name: new tab name.
         */
        void rename_tab(uint32_t tab_id, const std::string & new_name);

        /** \fn Object get_content()
         *  \brief Gets current tab content.
         *  \returns object for tab content.
         */
        Object get_content();

        /** \fn Object get_tab_btns()
         *  \brief Gets tab buttons.
         *  \returns object for tab buttons.
         */
        Object get_tab_btns();

        /** \fn void set_act(uint32_t id, lv_anim_enable_t anim_en)
         *  \brief Sets current tab by index.
         *  \param id: tab index.
         *  \param anim_en: if LV_ANIM_ON, tab change is animated;
         *  if LV_ANIM_OFF, tab change is immediate.
         */
        void set_act(uint32_t id, lv_anim_enable_t anim_en);

        /** \fn uint16_t get_tab_act()
         *  \brief Gets current tab index.
         *  \returns tab index.
         */
        uint16_t get_tab_act();
        
    };

}
#endif // LV_USE_TABVIEW