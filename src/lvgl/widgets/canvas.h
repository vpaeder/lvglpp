/** \file canvas.h
 *  \brief Header file for C++ wrapper for lv_canvas_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Canvas
     *  \brief Wraps a lv_canvas_t object.
     */
    class Canvas : public Widget<lv_canvas_create> {
    public:
        using Widget::Widget;

        /** \fn void set_buffer(std::shared_ptr<void> buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf)
         *  \brief Sets buffer in which canvas data will be stored.
         *  \param buf: pointer to buffer.
         *  \param w: canvas width.
         *  \param h: canvas height.
         *  \param cf: color format.
         */
        void set_buffer(std::shared_ptr<void> buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf);

        /** \fn void set_px_color(lv_coord_t x, lv_coord_t y, lv_color_t c)
         *  \brief Sets pixel color.
         *  \param x: pixel x coordinate.
         *  \param y: pixel y coordinate.
         *  \param c: color.
         */
        void set_px_color(lv_coord_t x, lv_coord_t y, lv_color_t c);

        /** \fn void set_px_opa(lv_coord_t x, lv_coord_t y, lv_opa_t opa)
         *  \brief Sets pixel opacity.
         *  \param x: pixel x coordinate.
         *  \param y: pixel y coordinate.
         *  \param opa: pixel opacity (0=transparent, 255=opaque).
         */
        void set_px_opa(lv_coord_t x, lv_coord_t y, lv_opa_t opa);

        /** \fn void set_palette(uint8_t id, lv_color_t c)
         *  \brief Sets palette color (if color format is indexed).
         *  \param id: color index.
         *  \param c: color.
         */
        void set_palette(uint8_t id, lv_color_t c);

        /** \fn lv_color_t get_px(lv_coord_t x, lv_coord_t y) const
         *  \brief Gets pixel color.
         *  \param x: pixel x coordinate.
         *  \param y: pixel y coordinate.
         *  \returns pixel color.
         */
        lv_color_t get_px(lv_coord_t x, lv_coord_t y) const;

        /** \fn std::shared_ptr<lv_img_dsc_t> get_img() const
         *  \brief Gets canvas content as an image descriptor.
         *  \returns pointer to the image descriptor representing canvas content.
         */
        std::shared_ptr<lv_img_dsc_t> get_img() const;

        /** \fn void copy_buf(const std::shared_ptr<void> to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h)
         *  \brief Copies an area of the canvas buffer.
         *  \param to_copy: target buffer.
         *  \param x: left coordinate of the area.
         *  \param y: top coordinate of the area.
         *  \param w: width of the area.
         *  \param h: height of the area.
         */
        void copy_buf(const std::shared_ptr<void> to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h);

        /** \fn void transform(int16_t angle, uint16_t zoom, lv_coord_t offset_x, lv_coord_t offset_y, int32_t pivot_x, int32_t pivot_y, bool antialias)
         *  \brief Transforms canvas content with given parameters.
         *  \param angle: rotation angle.
         *  \param zoom: zoom factor.
         *  \param offset_x: translation offset in x direction.
         *  \param offset_y: translation offset in y direction.
         *  \param pivot_x: x coordinate of centre of rotation.
         *  \param pivot_y: y coordinate of centre of rotation.
         *  \param antialias: if true, enables antialias.
         */
        void transform(int16_t angle, uint16_t zoom, lv_coord_t offset_x, lv_coord_t offset_y, int32_t pivot_x, int32_t pivot_y, bool antialias);

        /** \fn void blur_hor(uint16_t r)
         *  \brief Applies horizontal blur on the whole canvas.
         *  \param r: blur radius.
         */
        void blur_hor(uint16_t r);
        /** \fn void blur_hor(const Area & area, uint16_t r)
         *  \brief Applies horizontal blur on an area of the canvas.
         *  \param area: canvas area.
         *  \param r: blur radius.
         */
        void blur_hor(const Area & area, uint16_t r);

        /** \fn void blur_ver(uint16_t r)
         *  \brief Applies vertical blur on the whole canvas.
         *  \param r: blur radius.
         */
        void blur_ver(uint16_t r);
        /** \fn void blur_ver(const Area & area, uint16_t r)
         *  \brief Applies vertical blur on an area of the canvas.
         *  \param area: canvas area.
         *  \param r: blur radius.
         */
        void blur_ver(const Area & area, uint16_t r);

        /** \fn void fill_bg(lv_color_t & color, lv_opa_t opa)
         *  \brief Fill canvas with given color.
         *  \param color: color.
         *  \param opa: opacity.
         */
        void fill_bg(lv_color_t & color, lv_opa_t opa);

        /** \fn void draw_rect(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, const RectangleDrawDescriptor & draw_dsc)
         *  \brief Draws a rectangle on the canvas.
         *  \param x: left coordinate of the rectangle.
         *  \param y: top coordinate of the rectangle.
         *  \param w: width of the rectangle.
         *  \param h: height of the rectangle.
         *  \param draw_dsc: rectangle descriptor.
         */
        void draw_rect(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, const RectangleDrawDescriptor & draw_dsc);

        /** \fn void draw_text(lv_coord_t x, lv_coord_t y, lv_coord_t max_w, LabelDrawDescriptor & draw_dsc, const std::string & txt)
         *  \brief Draws some text on the canvas.
         *  \param x: left coordinate of the text.
         *  \param y: top coordinate of the text.
         *  \param max_w: maximum width of the text (the text will be wrapped to fit within this width).
         *  \param draw_dsc: text descriptor.
         *  \param txt: text string.
         */
        void draw_text(lv_coord_t x, lv_coord_t y, lv_coord_t max_w, LabelDrawDescriptor & draw_dsc, const std::string & txt);

        /** \fn void draw_img(lv_coord_t x, lv_coord_t y, const void * src, const ImageDrawDescriptor & draw_dsc)
         *  \brief Draws an image on the canvas.
         *  \param x: left coordinate of the image.
         *  \param y: top coordinate of the image.
         *  \param src: image buffer.
         *  \param draw_dsc: image descriptor.
         */
        void draw_img(lv_coord_t x, lv_coord_t y, const void * src, const ImageDrawDescriptor & draw_dsc);

        /** \fn void draw_line(const std::vector<lv_point_t> & points, uint32_t point_cnt, const LineDrawDescriptor & draw_dsc)
         *  \brief Draws a line on the canvas.
         *  \param points: an array of points describing the line.
         *  \param point_cnt: number of points.
         *  \param draw_dsc: line descriptor.
         */
        void draw_line(const std::vector<lv_point_t> & points, uint32_t point_cnt, const LineDrawDescriptor & draw_dsc);

        /** \fn void draw_polygon(const std::vector<lv_point_t> & points, uint32_t point_cnt, const RectangleDrawDescriptor & draw_dsc)
         *  \brief Draws a polygon on the canvas.
         *  \param points: an array of points describing the polygon.
         *  \param point_cnt: number of points.
         *  \param draw_dsc: polygon descriptor.
         */
        void draw_polygon(const std::vector<lv_point_t> & points, uint32_t point_cnt, const RectangleDrawDescriptor & draw_dsc);

        /** \fn void draw_arc(lv_coord_t x, lv_coord_t y, lv_coord_t r, int32_t start_angle, int32_t end_angle, const ArcDrawDescriptor & draw_dsc)
         *  \brief Draws an arc on the canvas.
         *  \param x: left coordinate of the arc.
         *  \param y: top coordinate of the arc.
         *  \param r: arc radius.
         *  \param start_angle: start angle.
         *  \param end_angle: end angle.
         *  \param draw_dsc: arc descriptor.
         */
        void draw_arc(lv_coord_t x, lv_coord_t y, lv_coord_t r, int32_t start_angle, int32_t end_angle, const ArcDrawDescriptor & draw_dsc);

    };

}
