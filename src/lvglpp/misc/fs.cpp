/** \file fs.cpp
 *  \brief Implementation file for C++ wrapper for LVGL file system functions.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "fs.h"

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::misc {
    FileSystem::FileSystem(char letter) {
        LV_LOG_INFO("initializing file system for letter %c", letter);
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_fs_drv_init(this->raw_ptr());
        this->lv_obj->letter = letter;
        //this->lv_obj->cache_size = 1024;
        this->lv_obj->user_data = static_cast<void*>(this);
        // define callbacks
        auto f_ready = [] (lv_cls_ptr drv) -> bool {
            LV_LOG_INFO("calling ready callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->ready_cb();
        };
        auto f_open = [](lv_cls_ptr drv, const char * path, lv_fs_mode_t mode) -> void* {
            LV_LOG_INFO("calling open callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->open_cb(path, mode);
        };
        auto f_close = [](lv_cls_ptr drv, void * file_p) -> lv_fs_res_t {
            LV_LOG_INFO("calling close callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->close_cb(file_p);
        };
        auto f_read = [](lv_cls_ptr drv, void * file_p, void * buf, uint32_t btr, uint32_t * br) -> lv_fs_res_t {
            LV_LOG_INFO("calling read callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->read_cb(file_p, buf, btr, br);
        };
        auto f_write = [](lv_cls_ptr drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw) -> lv_fs_res_t {
            LV_LOG_INFO("calling write callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->write_cb(file_p, buf, btw, bw);
        };
        auto f_seek = [](lv_cls_ptr drv, void * file_p, uint32_t pos, lv_fs_whence_t whence) -> lv_fs_res_t {
            LV_LOG_INFO("calling seek callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->seek_cb(file_p, pos, whence);
        };
        auto f_tell = [](lv_cls_ptr drv, void * file_p, uint32_t * pos_p) -> lv_fs_res_t {
            LV_LOG_INFO("calling tell callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->tell_cb(file_p, pos_p);
        };
        auto f_dir_open = [](lv_cls_ptr drv, const char * path) -> void* {
            LV_LOG_INFO("calling dir open callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->dir_open_cb(path);
        };
        auto f_dir_read = [](lv_cls_ptr drv, void * rddir_p, char * fn) -> lv_fs_res_t {
            LV_LOG_INFO("calling dir read callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->dir_read_cb(rddir_p, fn);
        };
        auto f_dir_close = [](lv_cls_ptr drv, void * rddir_p) -> lv_fs_res_t {
            LV_LOG_INFO("calling dir close callback.");
            auto obj = reinterpret_cast<FileSystem*>(drv->user_data);
            return obj->dir_close_cb(rddir_p);
        };
        this->lv_obj->ready_cb = f_ready;
        this->lv_obj->open_cb = f_open;
        this->lv_obj->close_cb = f_close;
        this->lv_obj->read_cb = f_read;
        this->lv_obj->write_cb = f_write;
        this->lv_obj->seek_cb = f_seek;
        this->lv_obj->tell_cb = f_tell;
        this->lv_obj->dir_open_cb = f_dir_open;
        this->lv_obj->dir_read_cb = f_dir_read;
        this->lv_obj->dir_close_cb = f_dir_close;

        lv_fs_drv_register(this->raw_ptr());
    }

    File FileSystem::open(const std::string & path, lv_fs_mode_t mode) {
        LV_LOG_INFO("opening file %s", path.c_str());
        auto f = lv_cls_alloc<lv_fs_file_t>();
        lv_fs_open(f, path.c_str(), mode);
        return File(f);
    }

    Directory FileSystem::open_dir(const std::string & path) {
        LV_LOG_INFO("opening directory %s", path.c_str());
        auto d = lv_cls_alloc<lv_fs_dir_t>();
        lv_fs_dir_open(d, path.c_str());
        return Directory(d);
    }

    bool FileSystem::is_ready() const {
        LV_LOG_INFO("checking if ready");
        return lv_fs_is_ready(this->lv_obj->letter);
    }


    std::string get_filesystem_letters() {
        std::string buf(26,'\0');
        lv_fs_get_letters(&buf[0]);
        return buf;
    }


    File::File() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
    }

    File::~File() {
        LV_LOG_INFO("closing file.");
        if (this->lv_obj->file_d != nullptr)
            this->close();
    }

    lv_fs_res_t File::close() {
        return lv_fs_close(this->raw_ptr());
    }

    std::string File::read(uint32_t btr) {
        std::string buf(btr, '\0');
        uint32_t nr;
        auto res = lv_fs_read(this->raw_ptr(), reinterpret_cast<void*>(&buf[0]), btr, &nr);
        if (res != LV_FS_RES_OK) return std::string{};
        return buf;
    }

    uint32_t File::write(const std::string & data) {
        uint32_t bw;
        lv_fs_write(this->raw_ptr(),
                    reinterpret_cast<const void*>(data.c_str()), data.size(), &bw);
        return bw;
    }

    lv_fs_res_t File::seek(uint32_t pos, lv_fs_whence_t whence) {
        return lv_fs_seek(this->raw_ptr(), pos, whence);
    }

    uint32_t File::tell() {
        uint32_t pos;
        if (lv_fs_tell(this->raw_ptr(), &pos) != LV_FS_RES_OK)
            return 0;
        return pos;
    }


    Directory::Directory() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
    }

    Directory::~Directory() {
        if (this->lv_obj->dir_d != nullptr)
            this->close();
    }

    lv_fs_res_t Directory::close() {
        return lv_fs_dir_close(this->raw_ptr());
    }

    std::string Directory::read() {
        std::string res(256,'\0');
        if (lv_fs_dir_read(this->raw_ptr(), &res[0]) != LV_FS_RES_OK)
            return std::string{};
        return res;
    }

}
#endif // LV_USE_USER_DATA