/** \file menu.h
 *  \brief Header file for C++ wrapper for lv_menu_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_MENU

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Menu
     *  \brief Wraps a lv_menu_t object.
     */
    class Menu : public Widget<lv_menu_create> {
    public:
        using Widget::Widget;
        
        /** \fn Object page_create(const std::string & title)
         *  \brief Creates a menu page object.
         *  \param title: page title.
         *  \returns page object instance.
         */
        Object page_create(const std::string & title = "");

        /** \fn Object cont_create(Object & parent)
         *  \brief Creates a menu content object.
         *  \param parent: parent object.
         *  \returns menu content object instance.
         */
        Object cont_create(Object & parent);

        /** \fn Object section_create(Object & parent)
         *  \brief Creates a menu section object.
         *  \param parent: parent object.
         *  \returns menu section object instance.
         */
        Object section_create(Object & parent);

        /** \fn Object separator_create(Object & parent)
         *  \brief Creates a menu separator object.
         *  \param parent: parent object.
         *  \returns menu separator object instance.
         */
        Object separator_create(Object & parent);

        /** \fn void set_page(const Object & page)
         *  \brief Sets menu page to display in main area.
         *  \param page: page object instance to display.
         */
        void set_page(const Object & page);

        /** \fn void clear_page()
         *  \brief Clears menu page.
         */
        void clear_page();

        /** \fn void set_sidebar_page(const Object & page)
         *  \brief Sets menu page to display in sidebar.
         *  \param page: page object instance to display.
         */
        void set_sidebar_page(const Object & page);

        /** \fn void clear_sidebar_page()
         *  \brief Clears sidebar page.
         */
        void clear_sidebar_page();

        /** \fn void set_mode_header(lv_menu_mode_header_t mode_header)
         *  \brief Sets header behaviour.
         *  \param mode_header: mode header code (LV_MENU_HEADER_TOP_FIXED/TOP_UNFIXED/BOTTOM_FIXED).
         */
        void set_mode_header(lv_menu_mode_header_t mode_header);

        /** \fn void set_mode_root_back_btn(lv_menu_mode_root_back_btn_t mode_root_back_btn)
         *  \brief Enables/disables back button.
         *  \param mode_root_back_btn: LV_MENU_ROOT_BACK_BTN_DISABLED/ENABLED
         */
        void set_mode_root_back_btn(lv_menu_mode_root_back_btn_t mode_root_back_btn);

        /** \fn void set_load_page_event(const Object & obj, const Object & page)
         *  \brief Assigns a page to an menu item's event. This makes that the page
         *  gets displayed when menu item is pressed.
         *  \param obj: menu item object.
         *  \param page: page object.
         */
        void set_load_page_event(const Object & obj, const Object & page);

        /** \fn Object get_cur_main_page() const
         *  \brief Gets current page displayed in main section.
         *  \returns page object displayed in main section.
         */
        Object get_cur_main_page() const;

        /** \fn Object get_cur_sidebar_page() const
         *  \brief Gets current page displayed in sidebar.
         *  \returns page object displayed in sidebar.
         */
        Object get_cur_sidebar_page() const;

        /** \fn Object get_main_header() const
         *  \brief Gets header of main section.
         *  \returns object displayed as header of main section.
         */
        Object get_main_header() const;

        /** \fn Object get_main_header_back_btn() const
         *  \brief Gets back button of header section.
         *  \returns button object for back button of header section.
         */
        Object get_main_header_back_btn() const;

        /** \fn Object get_sidebar_header() const
         *  \brief Gets header of sidebar.
         *  \returns object displayed as header of sidebar.
         */
        Object get_sidebar_header() const;

        /** \fn Object get_sidebar_header_back_btn() const
         *  \brief Gets back button of sidebar.
         *  \returns button object for back button of sidebar.
         */
        Object get_sidebar_header_back_btn() const;

        /** \fn bool back_btn_is_root(const Object & obj) const
         *  \brief Tells if given back button is at menu root.
         *  \param obj: back button object.
         *  \returns true if given object is the root back button, false otherwise.
         */
        bool back_btn_is_root(const Object & obj) const;

        /** \fn void clear_history()
         *  \brief Clears menu history.
         */
        void clear_history();

    };

}
#endif // LV_USE_MENU