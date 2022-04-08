/** \file anim.cpp
 *  \brief Implementation file for C++ wrapper for lv_anim_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "anim.h"

namespace lvgl::misc {

    Animation::Animation() {
        this->lv_obj = LvPointerType(new lv_anim_t{});
        lv_anim_init(this->raw_ptr());
    }

    template <class T> void Animation::set_var(T & var) {
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(&var));
    }

    void Animation::set_var(void * var) {
        lv_anim_set_var(this->raw_ptr(), var);
    }

    void Animation::set_exec_cb(lv_anim_exec_xcb_t exec_cb) {
        lv_anim_set_exec_cb(this->raw_ptr(), exec_cb);
    }

    void Animation::set_time(uint32_t duration) {
        lv_anim_set_time(this->raw_ptr(), duration);
    }

    void Animation::set_delay(uint32_t delay) {
        lv_anim_set_delay(this->raw_ptr(), delay);
    }

    void Animation::set_values(int32_t start, int32_t end) {
        lv_anim_set_values(this->raw_ptr(), start, end);
    }

    void Animation::set_custom_exec_cb(lv_anim_custom_exec_cb_t exec_cb) {
        lv_anim_set_custom_exec_cb(this->raw_ptr(), exec_cb);
    }

    void Animation::set_path_cb(lv_anim_path_cb_t path_cb) {
        lv_anim_set_path_cb(this->raw_ptr(), path_cb);
    }

    void Animation::set_start_cb(lv_anim_start_cb_t start_cb) {
        lv_anim_set_start_cb(this->raw_ptr(), start_cb);
    }

    void Animation::set_get_value_cb(lv_anim_get_value_cb_t get_value_cb) {
        lv_anim_set_get_value_cb(this->raw_ptr(), get_value_cb);
    }

    void Animation::set_ready_cb(lv_anim_ready_cb_t ready_cb) {
        lv_anim_set_ready_cb(this->raw_ptr(), ready_cb);
    }

    void Animation::set_reverse_time(uint32_t time) {
        lv_anim_set_playback_time(this->raw_ptr(), time);
    }

    void Animation::set_reverse_delay(uint32_t delay) {
        lv_anim_set_playback_delay(this->raw_ptr(), delay);
    }

    void Animation::set_repeat_count(uint16_t cnt) {
        lv_anim_set_repeat_count(this->raw_ptr(), cnt);
    }

    void Animation::set_repeat_delay(uint32_t delay) {
        lv_anim_set_repeat_delay(this->raw_ptr(), delay);
    }

    void Animation::set_early_apply(bool en) {
        lv_anim_set_early_apply(this->raw_ptr(), en);
    }

    template <class T> void Animation::set_user_data(T & user_data) {
        lv_anim_set_user_data(this->raw_ptr(), static_cast<void*>(&user_data));
    }

    void Animation::set_user_data(void * user_data) {
        lv_anim_set_user_data(this->raw_ptr(), user_data);
    }

    uint32_t Animation::get_delay() const {
        return lv_anim_get_delay(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint32_t Animation::get_playtime() const {
        return lv_anim_get_playtime(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    template <class T> T Animation::get_user_data() const {
        return *reinterpret_cast<T*>(lv_anim_get_user_data(this->raw_ptr()));
    }

    void * Animation::get_user_data() const {
        return lv_anim_get_user_data(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
    
    AnimationTimeline::AnimationTimeline() {
        this->lv_obj = LvPointerType(lv_anim_timeline_create());
    }

    void AnimationTimeline::add(uint32_t start_time, const Animation & anim) {
        lv_anim_timeline_add(this->raw_ptr(), start_time, const_cast<lv_anim_t*>(anim.raw_ptr()));
    }

    uint32_t AnimationTimeline::start() {
        return lv_anim_timeline_start(this->raw_ptr());
    }

    void AnimationTimeline::stop() {
        lv_anim_timeline_stop(this->raw_ptr());
    }

    void AnimationTimeline::set_reverse(bool reverse) {
        lv_anim_timeline_set_reverse(this->raw_ptr(), reverse);
    }

    void AnimationTimeline::set_progress(uint16_t progress) {
        lv_anim_timeline_set_progress(this->raw_ptr(), progress);
    }

    uint32_t AnimationTimeline::get_playtime() const {
        return lv_anim_timeline_get_playtime(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    bool AnimationTimeline::get_reverse() const {
        return lv_anim_timeline_get_reverse(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
}
