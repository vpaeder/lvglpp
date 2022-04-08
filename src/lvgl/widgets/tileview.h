/** \file tileview.h
 *  \brief Header file for C++ wrapper for lv_tileview_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Tileview
     *  \brief Wraps a lv_tileview_t object.
     */
    class Tileview : public Object {
    protected:
        /** \fn void initialize()
         *  \brief Initialize object.
         */
        void initialize() override;
        /** \fn void initialize(Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        void initialize(Object & parent) override;
    
    public:
        /** \fn Tileview()
         *  \brief Default constructor.
         */
        Tileview();
        /** \fn Tileview(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        Tileview(Object & parent);

        /** \fn Object add_tile(uint8_t col_id, uint8_t row_id, lv_dir_t dir)
         *  \brief Adds tile with given parameters.
         *  \param col_id: column index.
         *  \param row_id: row index.
         *  \param dir: OR-ed combination of allowed swiping directions.
         *  \returns new tile object.
         */
        Object add_tile(uint8_t col_id, uint8_t row_id, lv_dir_t dir);

        /** \fn void set_tile(Object & tile_obj, lv_anim_enable_t anim_en)
         *  \brief Sets tile to given tile object.
         *  \param tile_obj: object to scroll to.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void set_tile(Object & tile_obj, lv_anim_enable_t anim_en);
        
        /** \fn void set_tile_by_id(uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en)
         *  \brief Sets tile to given position.
         *  \param col_id: column index.
         *  \param row_id: row index.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void set_tile_by_id(uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en);

        /** \fn Object get_tile_act() const
         *  \brief Gets current tile.
         *  \returns current tile object.
         */
        Object get_tile_act() const;
    };

}
