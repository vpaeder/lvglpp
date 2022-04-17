/** \file desc.h
 *  \brief Header file for C++ wrapper for LVGL draw descriptors.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../misc/area.h"
#include "../misc/color.h"
#include "../font/font.h"
#include "image.h"

/** \namespace lvgl::draw
 *  \brief LVGL draw components.
 */
namespace lvgl::draw {
    
    using namespace lvgl::misc;
    using namespace lvgl::font;

    /** \class RectangleDrawDescriptor
     *  \brief Wraps a lv_draw_rect_dsc_t object.
     */
    class RectangleDrawDescriptor : public PointerWrapper<lv_draw_rect_dsc_t, lv_mem_free> {
    public:
        /** \fn RectangleDrawDescriptor()
         *  \brief Default constructor.
         */
        RectangleDrawDescriptor();

        /** \fn void draw(lv_draw_ctx_t * draw_ctx, const Area & coords)
         *  \brief Draws a rectangle using a draw context.
         *  \param draw_ctx: draw context.
         *  \param coords: rectangle coordinates.
         */
        void draw(lv_draw_ctx_t * draw_ctx, const Area & coords);

    };


    /** \class LabelDrawDescriptor
     *  \brief Wraps a lv_draw_label_dsc_t object.
     */
    class LabelDrawDescriptor : public PointerWrapper<lv_draw_label_dsc_t, lv_mem_free> {
    public:
        /** \fn LabelDrawDescriptor()
         *  \brief Default constructor.
         */
        LabelDrawDescriptor();

        /** \fn void draw(lv_draw_ctx_t * ctx, const Area & coords, const std::string & txt, lv_draw_label_hint_t * hint)
         *  \brief Draws a text using a draw context.
         *  \param ctx: draw context.
         *  \param coords: area where to draw.
         *  \param txt: text string.
         *  \param hint: draw label hints object (this is used to speed up
         *  rendering of long texts).
         */
        void draw(lv_draw_ctx_t * ctx, const Area & coords, const std::string & txt, lv_draw_label_hint_t * hint);

        /** \fn void draw_letter(lv_draw_ctx_t * ctx, const lv_point_t & pos, uint32_t letter)
         *  \brief Draws a letter using a draw context.
         *  \param ctx: draw context.
         *  \param pos: position.
         *  \param letter: character index.
         */
        void draw_letter(lv_draw_ctx_t * ctx, const lv_point_t & pos, uint32_t letter);

    };


    /** \class ImageDrawDescriptor
     *  \brief Wraps a lv_draw_img_dsc_t object.
     */
    class ImageDrawDescriptor : public PointerWrapper<lv_draw_img_dsc_t, lv_mem_free> {
    public:
        ImageDrawDescriptor();

        /** \fn void draw(lv_draw_ctx_t * ctx, const Area & coords, const ImageBuffer & img)
         *  \brief Draws an image using a draw context.
         *  \param ctx: draw context.
         *  \param coords: area where to draw.
         *  \param img: image buffer.
         */
        void draw(lv_draw_ctx_t * ctx, const Area & coords, const ImageDescriptor & img);
        // TODO: void draw_decoded
    };

    /** \class LineDrawDescriptor
     *  \brief Wraps a lv_draw_line_dsc_t object.
     */
    class LineDrawDescriptor : public PointerWrapper<lv_draw_line_dsc_t, lv_mem_free> {
    public:
        /** \fn LineDrawDescriptor()
         *  \brief Default constructor.
         */
        LineDrawDescriptor();

        /** \fn void draw(lv_draw_ctx_t * ctx, const lv_point_t & point1, const lv_point_t & point2)
         *  \brief Draws an line using a draw context.
         *  \param ctx: draw context.
         *  \param point1: start point.
         *  \param point2: end point.
         */
        void draw(lv_draw_ctx_t * ctx, const lv_point_t & point1, const lv_point_t & point2);
    };

    /** \class ArcDrawDescriptor
     *  \brief Wraps a lv_draw_arc_dsc_t object.
     */
    class ArcDrawDescriptor : public PointerWrapper<lv_draw_arc_dsc_t, lv_mem_free> {
    public:
        /** \fn ArcDrawDescriptor()
         *  \brief Default constructor.
         */
        ArcDrawDescriptor();

        /** \fn void draw(lv_draw_ctx_t * ctx, const lv_point_t & center, uint16_t radius,  uint16_t start_angle, uint16_t end_angle)
         *  \brief Draws an arc using a draw context.
         *  \param ctx: draw context.
         *  \param center: arc centre.
         *  \param radius: arc radius.
         *  \param start_angle: start angle.
         *  \param end_angle: end angle.
         */
        void draw(lv_draw_ctx_t * ctx, const lv_point_t & center, uint16_t radius,  uint16_t start_angle, uint16_t end_angle);
    };

}
