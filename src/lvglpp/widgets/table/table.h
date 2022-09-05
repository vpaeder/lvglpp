/** \file table.h
 *  \brief Header file for C++ wrapper for lv_table_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"
#include <tuple>

#if LV_USE_TABLE != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Table
     *  \brief Wraps a lv_table_t object.
     */
    class Table : public Widget<lv_table_create> {
    public:
        using Widget::Widget;
        
        /** \fn void set_cell_value(uint16_t row, uint16_t col, const std::string & txt)
         *  \brief Sets table cell value.
         *  \param row: cell row index.
         *  \param col: cell column index.
         *  \param txt: cell value.
         */
        void set_cell_value(uint16_t row, uint16_t col, const std::string & txt);

        /** \fn template <typename... Args> void set_cell_value_fmt(uint16_t row, uint16_t col, const std::string & fmt, Args... args)
         *  \brief Sets table cell value with a format string.
         *  \tparam Args: classes of format placeholder arguments.
         *  \param row: cell row index.
         *  \param col: cell column index.
         *  \param fmt: cell format string.
         *  \param args: format placeholder arguments.
         */
        template <typename... Args> void set_cell_value_fmt(uint16_t row, uint16_t col, const std::string & fmt, Args... args) {
            lv_table_set_cell_value_fmt(this->raw_ptr(), row, col, fmt.c_str(), args...);
        }

        /** \fn void set_row_cnt(uint16_t row_cnt)
         *  \brief Sets row count.
         *  \param row_cnt: row count.
         */
        void set_row_cnt(uint16_t row_cnt);

        /** \fn void set_col_cnt(uint16_t col_cnt)
         *  \brief Sets column count.
         *  \param col_cnt: column count.
         */
        void set_col_cnt(uint16_t col_cnt);

        /** \fn void set_col_width(uint16_t col_id, lv_coord_t w)
         *  \brief Sets given column width.
         *  \param col_id: column index.
         *  \param w: column pixel width.
         */
        void set_col_width(uint16_t col_id, lv_coord_t w);

        /** \fn void add_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl)
         *  \brief Adds control bits to a cell.
         *  \param row: row index.
         *  \param col: column index.
         *  \param ctrl: OR-ed combination of lv_table_cell_ctrl_t values.
         */
        void add_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);

        /** \fn void clear_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl)
         *  \brief Removes control bits from a cell.
         *  \param row: row index.
         *  \param col: column index.
         *  \param ctrl: OR-ed combination of lv_table_cell_ctrl_t values.
         */
        void clear_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl);

        /** \fn const std::shared_ptr<const char> get_cell_value(uint16_t row, uint16_t col) const
         *  \brief Gets cell content.
         *  \param row: row index.
         *  \param col: column index.
         *  \returns pointer to the cell content string.
         */
        const std::shared_ptr<const char> get_cell_value(uint16_t row, uint16_t col) const;

        /** \fn uint16_t get_row_cnt() const
         *  \brief Gets number of rows.
         *  \returns number of table rows.
         */
        uint16_t get_row_cnt() const;

        /** \fn uint16_t get_col_cnt() const
         *  \brief Gets number of columns.
         *  \returns number of table columns.
         */
        uint16_t get_col_cnt() const;

        /** \fn lv_coord_t get_col_width(uint16_t col) const
         *  \brief Gets given column width.
         *  \param col: column index.
         *  \returns column pixel width.
         */
        lv_coord_t get_col_width(uint16_t col) const;

        /** \fn bool has_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) const
         *  \brief Tells if cell has given control bits.
         *  \param row: row index.
         *  \param col: column index.
         *  \param ctrl: OR-ed combination of lv_table_cell_ctrl_t values.
         *  \returns true if cell has control bits, false otherwise.
         */
        bool has_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) const;

        /** \fn std::tuple<uint16_t, uint16_t> get_selected_cell() const
         *  \brief Gets row and column indices of selected cell.
         *  \returns row and column indices of selected cell.
         */
        std::tuple<uint16_t, uint16_t> get_selected_cell() const;

    };

}
#endif // LV_USE_TABLE