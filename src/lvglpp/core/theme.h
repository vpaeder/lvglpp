/** \file theme.h
 *  \brief Header file for C++ wrapper for LVGL themes.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */

#include "../lv_wrapper.h"

namespace lvgl::core {

    class Object;

    /** \class Theme
     *  \brief Wraps a lv_theme_t object.
     */
    class Theme : public PointerWrapper<lv_theme_t, lv_mem_free> {
    public:
        using PointerWrapper::PointerWrapper;

        /** \typedef ThemeApplyCb
         *  \brief Type of function for theme apply callback.
         */
        using ThemeApplyCb = void(*)(Theme &, Object & obj);

        /** \fn Theme()
         *  \brief Default constructor.
         */
        Theme();
        
        /** \fn void set_parent(Theme & parent)
         *  \brief Sets the theme's parent.
         *  \param parent: parent theme.
         */
        void set_parent(Theme & parent);

#if LV_USE_USER_DATA
        /** \fn void set_apply_cb(ThemeApplyCb apply_cb)
         *  \brief Sets the function called when the theme is applied to an object.
         *  \param apply_cb: callback function pointer.
         */
        void set_apply_cb(ThemeApplyCb apply_cb);
#endif // LV_USE_USER_DATA

        /** \fn void set_apply_cb(lv_theme_apply_cb_t apply_cb)
         *  \brief Sets the function called when the theme is applied to an object.
         *  \param apply_cb: callback function pointer.
         */
        void set_apply_cb(lv_theme_apply_cb_t apply_cb);
    };

    /** \fn Theme get_active_theme()
     *  \brief Gets active theme on currently active display.
     *  \returns theme object.
     */
    Theme get_active_theme();

    /** \fn void set_active_theme(Theme & th)
     *  \brief Sets active theme on currently active display.
     *  \param th: theme object.
     */
    void set_active_theme(Theme & th);

}
