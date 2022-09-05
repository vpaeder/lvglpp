/** \file anim.cpp
 *  \brief Implementation file for C++ wrapper for lv_anim_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "anim.h"

namespace lvgl::misc {
    
    Animation::Animation() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_anim_init(this->raw_ptr());
    }

    void Animation::set_var(void * var) {
        lv_anim_set_var(this->raw_ptr(), var);
    }

    void Animation::set_exec_cb(lv_anim_exec_xcb_t exec_cb) {
        // if this assertion is true, this means we have used the template version
        // of set_var or any of the callback setters; we therefore
        // need to use the template version of set_exec_cb
        assert(this != this->raw_ptr()->var);
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
        assert(this != this->raw_ptr()->var);
        lv_anim_set_custom_exec_cb(this->raw_ptr(), exec_cb);
    }

    void Animation::set_custom_exec_cb(CustomExecCb exec_cb) {
        using CustomCbType = Callback<void, Animation&, int32_t>;
        this->custom_exec_cb = std::make_shared<CustomCbType>(exec_cb);
        auto f = [](lv_anim_t * lv_obj, int32_t val) {
            auto anim = reinterpret_cast<Animation*>(lv_obj->var);
            if (anim->custom_exec_cb != nullptr) {
                auto cb = *std::dynamic_pointer_cast<CustomCbType>(anim->custom_exec_cb);
                cb(*anim, val);
            }
        };
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        lv_anim_set_custom_exec_cb(this->raw_ptr(), f);
    }

    void Animation::set_path_cb(lv_anim_path_cb_t path_cb) {
        assert(this != this->raw_ptr()->var);
        lv_anim_set_path_cb(this->raw_ptr(), path_cb);
    }

    void Animation::set_path_cb(PathCb path_cb) {
        using PathCbType = Callback<int32_t, const Animation&>;
        this->path_cb = std::make_shared<PathCbType>(path_cb);
        auto f = [](const lv_anim_t * lv_obj) -> int32_t {
            auto anim = reinterpret_cast<Animation*>(lv_obj->var);
            if (anim->path_cb != nullptr) {
                auto cb = *std::dynamic_pointer_cast<PathCbType>(anim->path_cb);
                return cb(*anim);
            }
            return 0;
        };
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        lv_anim_set_path_cb(this->raw_ptr(), f);
    }

    void Animation::set_start_cb(lv_anim_start_cb_t start_cb) {
        assert(this != this->raw_ptr()->var);
        lv_anim_set_start_cb(this->raw_ptr(), start_cb);
    }

    void Animation::set_start_cb(StartCb start_cb) {
        using StartCbType = Callback<void, Animation&>;
        this->start_cb = std::make_shared<StartCbType>(start_cb);
        auto f = [](lv_anim_t * lv_obj) {
            auto anim = reinterpret_cast<Animation*>(lv_obj->var);
            if (anim->start_cb != nullptr) {
                auto cb = *std::dynamic_pointer_cast<StartCbType>(anim->start_cb);
                cb(*anim);
            }
        };
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        lv_anim_set_start_cb(this->raw_ptr(), f);
    }

    void Animation::set_get_value_cb(lv_anim_get_value_cb_t get_value_cb) {
        assert(this != this->raw_ptr()->var);
        lv_anim_set_get_value_cb(this->raw_ptr(), get_value_cb);
    }

    void Animation::set_get_value_cb(GetValueCb get_value_cb) {
        using GetValueCbType = Callback<int32_t, Animation&>;
        this->get_value_cb = std::make_shared<GetValueCbType>(get_value_cb);
        auto f = [](lv_anim_t * lv_obj) -> int32_t {
            auto anim = reinterpret_cast<Animation*>(lv_obj->var);
            if (anim->get_value_cb != nullptr) {
                auto cb = *std::dynamic_pointer_cast<GetValueCbType>(anim->get_value_cb);
                return cb(*anim);
            }
            return 0;
        };
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        lv_anim_set_get_value_cb(this->raw_ptr(), f);
    }

    void Animation::set_ready_cb(lv_anim_ready_cb_t ready_cb) {
        assert(this != this->raw_ptr()->var);
        lv_anim_set_ready_cb(this->raw_ptr(), ready_cb);
    }

    void Animation::set_ready_cb(ReadyCb ready_cb) {
        using ReadyCbType = Callback<void, Animation&>;
        this->ready_cb = std::make_shared<ReadyCbType>(ready_cb);
        auto f = [](lv_anim_t * lv_obj) {
            auto anim = reinterpret_cast<Animation*>(lv_obj->var);
            if (anim->ready_cb != nullptr) {
                auto cb = *std::dynamic_pointer_cast<ReadyCbType>(anim->ready_cb);
                cb(*anim);
            }
        };
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        lv_anim_set_ready_cb(this->raw_ptr(), f);
    }

    void Animation::set_deleted_cb(lv_anim_deleted_cb_t deleted_cb) {
        assert(this != this->raw_ptr()->var);
        lv_anim_set_deleted_cb(this->raw_ptr(), deleted_cb);
    }

    void Animation::set_deleted_cb(DeletedCb deleted_cb) {
        using DeletedCbType = Callback<void, Animation&>;
        this->deleted_cb = std::make_shared<DeletedCbType>(deleted_cb);
        auto f = [](lv_anim_t * lv_obj) {
            auto anim = reinterpret_cast<Animation*>(lv_obj->var);
            if (anim->deleted_cb != nullptr) {
                auto cb = *std::dynamic_pointer_cast<DeletedCbType>(anim->deleted_cb);
                cb(*anim);
            }
        };
        lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        lv_anim_set_deleted_cb(this->raw_ptr(), f);
    }

    void Animation::set_playback_time(uint32_t time) {
        lv_anim_set_playback_time(this->raw_ptr(), time);
    }

    void Animation::set_playback_delay(uint32_t delay) {
        lv_anim_set_playback_delay(this->raw_ptr(), delay);
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

#if LV_USE_USER_DATA
    void Animation::set_user_data(void * user_data) {
        lv_anim_set_user_data(this->raw_ptr(), user_data);
    }

    void * Animation::get_user_data() const {
        return lv_anim_get_user_data(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
#endif // LV_USE_USER_DATA

    void Animation::start() {
        lv_anim_start(this->raw_ptr());
    }

    uint32_t Animation::get_delay() const {
        return lv_anim_get_delay(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint32_t Animation::get_playtime() const {
        return lv_anim_get_playtime(const_cast<lv_cls_ptr>(this->raw_ptr()));
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
