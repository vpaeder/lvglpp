/** \file table.cpp
 *  \brief Implementation file for C++ wrapper for lv_table_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "table.h"

namespace lvgl::widgets {

    Table::Table() {
        this->initialize();
    }

    Table::Table(Object & parent) {
        this->initialize(parent);
    }

    void Table::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_table_create(nullptr));
    }
    void Table::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_table_create(parent.raw_ptr()));
    }

    void Table::set_cell_value(uint16_t row, uint16_t col, const std::string & txt) {
        lv_table_set_cell_value(this->raw_ptr(), row, col, txt.c_str());
    }

    template <typename... Args> void Table::set_cell_value_fmt(uint16_t row, uint16_t col, const std::string & fmt, Args... args) {
        lv_table_set_cell_value_fmt(this->raw_ptr(), row, col, fmt.c_str(), args...);
    }

    void Table::set_row_cnt(uint16_t row_cnt) {
        lv_table_set_row_cnt(this->raw_ptr(), row_cnt);
    }

    void Table::set_col_cnt(uint16_t col_cnt) {
        lv_table_set_col_cnt(this->raw_ptr(), col_cnt);
    }

    void Table::set_col_width(uint16_t col_id, lv_coord_t w) {
        lv_table_set_col_width(this->raw_ptr(), col_id, w);
    }

    void Table::add_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) {
        lv_table_add_cell_ctrl(this->raw_ptr(), row, col, ctrl);
    }

    void Table::clear_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) {
        lv_table_clear_cell_ctrl(this->raw_ptr(), row, col, ctrl);
    }

    const std::shared_ptr<const char> Table::get_cell_value(uint16_t row, uint16_t col) const {
        return std::shared_ptr<const char>(lv_table_get_cell_value(
                                     const_cast<lv_cls_ptr>(this->raw_ptr()), row, col));
    }

    uint16_t Table::get_row_cnt() const {
        return lv_table_get_row_cnt(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t Table::get_col_cnt() const {
        return lv_table_get_col_cnt(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_coord_t Table::get_col_width(uint16_t col) const {
        return lv_table_get_col_width(const_cast<lv_cls_ptr>(this->raw_ptr()), col);
    }

    bool Table::has_cell_ctrl(uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl) const {
        return lv_table_has_cell_ctrl(const_cast<lv_cls_ptr>(this->raw_ptr()), row, col, ctrl);
    }

    std::tuple<uint16_t, uint16_t> Table::get_selected_cell() const {
        uint16_t row, col;
        lv_table_get_selected_cell(const_cast<lv_cls_ptr>(this->raw_ptr()), &row, &col);
        return std::tuple<uint16_t, uint16_t>(std::move(row), std::move(col));
    }

}