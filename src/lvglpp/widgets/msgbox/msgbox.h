/** \file msgbox.h
 *  \brief Header file for C++ wrapper for lv_msgbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"
#include <string>
#include <vector>

#if LV_USE_MSGBOX

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class MessageBox
     *  \brief Wraps a lv_msgbox_t object.
     */
    class MessageBox : public Object {
    private:
        /** \property RawDblArray<char> btn_txts
         *  \brief Button texts.
         */
        RawDblArray<char> btn_txts;

    protected:
        /** \fn void initialize(const std::string & title, const std::string & txt,
         *                      const std::vector<std::string> & btn_txts,
         *                      bool add_close_btn)
         *  \brief Initialize object with parameters.
         *  \param title: message box title.
         *  \param txt: message box text.
         *  \param btn_txts: button texts.
         *  \param add_close_btn: if true, adds a close button.
         */
        void initialize(const std::string & title, const std::string & txt,
                        const std::vector<std::string> & btn_txts,
                        bool add_close_btn);
        /** \fn void initialize(Object & parent, const std::string & title,
         *                      const std::string & txt, const std::vector<std::string> & btn_txts,
         *                      bool add_close_btn)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         *  \param title: message box title.
         *  \param txt: message box text.
         *  \param btn_txts: button texts.
         *  \param add_close_btn: if true, adds a close button.
         */
        void initialize(Object & parent, const std::string & title, const std::string & txt,
                        const std::vector<std::string> & btn_txts,
                        bool add_close_btn);
    
    public:
        using Object::Object;
        
        MessageBox() = delete;
        MessageBox(Object & parent) = delete;
        /** \fn MessageBox(const std::string & title, const std::string & txt,
         *                 const std::vector<std::string> & btn_txts,
         *                 bool add_close_btn)
         *  \brief Constructor with parameters.
         *  \param title: message box title.
         *  \param txt: message box text.
         *  \param btn_txts: button texts.
         *  \param add_close_btn: if true, adds a close button.
         */
        MessageBox(const std::string & title, const std::string & txt,
                   const std::vector<std::string> & btn_txts,
                   bool add_close_btn);
        /** \fn MessageBox(Object & parent, const std::string & title,
         *                 const std::string & txt, const std::vector<std::string> & btn_txts,
         *                 bool add_close_btn)
         *  \brief Constructor with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param title: message box title.
         *  \param txt: message box text.
         *  \param btn_txts: button texts.
         *  \param add_close_btn: if true, adds a close button.
         */
        MessageBox(Object & parent, const std::string & title, const std::string & txt,
                   const std::vector<std::string> & btn_txts,
                   bool add_close_btn);

        /** \fn Object get_title() const
         *  \brief Gets object for title element.
         *  \returns object for title element.
         */
        Object get_title() const;

        /** \fn Object get_close_btn() const
         *  \brief Gets object for close button.
         *  \returns object for close button.
         */
        Object get_close_btn() const;

        /** \fn Object get_text() const
         *  \brief Gets object for text.
         *  \returns object for text.
         */
        Object get_text() const;

        /** \fn Object get_content() const
         *  \brief Gets object for content.
         *  \returns object for content.
         */
        Object get_content() const;

        /** \fn Object get_btns() const
         *  \brief Gets object for buttons.
         *  \returns object for buttons.
         */
        Object get_btns() const;

        /** \fn uint16_t get_active_btn() const
         *  \brief Gets active button.
         *  \returns active button index.
         */
        uint16_t get_active_btn() const;

        /** \fn std::string get_active_btn_text() const
         *  \brief Gets active button text.
         *  \returns active button text string.
         */
        std::string get_active_btn_text() const;

        /** \fn void close()
         *  \brief Closes message box.
         */
        void close();

        /** \fn void close_async()
         *  \brief Closes message box asynchronously.
         */
        void close_async();
    };

}
#endif // LV_USE_MSGBOX