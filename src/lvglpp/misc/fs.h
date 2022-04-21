/** \file fs.h
 *  \brief Header file for C++ wrapper for LVGL file system functions.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::misc {

    class File;
    class Directory;

    /** \class FileSystem
     *  \brief Wraps a lv_fs_drv_t object. This is a base class to construct
     *  file system drivers for LVGL.
     */
    class FileSystem : public PointerWrapper<lv_fs_drv_t, lv_mem_free> {
    protected:
        /** \fn virtual bool ready_cb()
         *  \brief Tells if the file system is ready to use.
         *  \returns true if file system is ready, false otherwise.
         */
        virtual bool ready_cb() = 0;

        /** \fn virtual void * open_cb(const char * path, lv_fs_mode_t mode)
         *  \brief Opens a file on the file system.
         *  \param path: file path.
         *  \param mode: access mode.
         *  \returns pointer to the file descriptor, or nullptr if failed.
         */
        virtual void * open_cb(const char * path, lv_fs_mode_t mode) = 0;

        /** \fn virtual lv_fs_res_t close_cb(void * file_p)
         *  \brief Closes a file.
         *  \param file_p: pointer to the file descriptor.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t close_cb(void * file_p) = 0;

        /** \fn virtual lv_fs_res_t read_cb(void * file_p, void * buf, uint32_t btr, uint32_t * br)
         *  \brief Reads data from a file.
         *  \param file_p: pointer to the file descriptor.
         *  \param buf: pointer to the recipient data buffer.
         *  \param btr: number of bytes to read.
         *  \param br: number of bytes actually read.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t read_cb(void * file_p, void * buf, uint32_t btr, uint32_t * br) = 0;

        /** \fn virtual lv_fs_res_t write_cb(void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
         *  \brief Writes data to a file.
         *  \param file_p: pointer to the file descriptor.
         *  \param buf: pointer to the recipient data buffer.
         *  \param btw: number of bytes to write.
         *  \param bw: number of bytes actually written.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t write_cb(void * file_p, const void * buf, uint32_t btw, uint32_t * bw) = 0;

        /** \fn virtual lv_fs_res_t seek_cb(void * file_p, uint32_t pos, lv_fs_whence_t whence)
         *  \brief Moves access pointer within file.
         *  \param file_p: pointer to the file descriptor.
         *  \param pos: position to move to.
         *  \param whence: mode; absolute (LV_FS_SEEK_SET), relative (LV_FS_SEEK_CUR), 
         *  or absolute from end of file (LV_FS_SEEK_END).
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t seek_cb(void * file_p, uint32_t pos, lv_fs_whence_t whence) = 0;

        /** \fn virtual lv_fs_res_t tell_cb(void * file_p, uint32_t * pos_p)
         *  \brief Gets position of access pointer within file.
         *  \param file_p: pointer to the file descriptor.
         *  \param pos_p: resulting position.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t tell_cb(void * file_p, uint32_t * pos_p) = 0;

        /** \fn virtual void * dir_open_cb(const char * path)
         *  \brief Opens a directory on the file system.
         *  \param path: directory path.
         *  \returns pointer to the directory descriptor.
         */
        virtual void * dir_open_cb(const char * path) = 0;

        /** \fn virtual lv_fs_res_t dir_read_cb(void * rddir_p, char * fn)
         *  \brief Reads next entry from a directory.
         *  \param rddir_p: pointer to the directory descriptor.
         *  \param fn: pointer to the recipient buffer for entry path.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t dir_read_cb(void * rddir_p, char * fn) = 0;

        /** \fn virtual lv_fs_res_t dir_close_cb(void * rddir_p)
         *  \brief Closes a directory.
         *  \param rddir_p: pointer to the directory descriptor.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        virtual lv_fs_res_t dir_close_cb(void * rddir_p) = 0;

    public:
        FileSystem() = default;
        
        /** \fn FileSystem(char letter)
         *  \brief Constructor.
         *  \param letter: registration letter for LVGL.
         */
        FileSystem(char letter);

        /** \fn File open(const std::string & path, lv_fs_mode_t mode)
         *  \brief Opens a file.
         *  \param path: file path.
         *  \param mode: access mode.
         *  \returns file object.
         */
        File open(const std::string & path, lv_fs_mode_t mode);

        /** \fn Directory open_dir(const std::string & path)
         *  \brief Opens a directory.
         *  \param path: directory path.
         *  \returns directory object.
         */
        Directory open_dir(const std::string & path);

        /** \fn bool is_ready() const
         *  \brief Tells if file system is ready to use.
         *  \returns true if file system is ready, false otherwise.
         */
        bool is_ready() const;
    };

    /** \fn std::string get_filesystem_letters()
     *  \brief Gets registered file system letters.
     *  \returns a string containing registered file system letters.
     */
    std::string get_filesystem_letters();


    /** \class File
     *  \brief Wraps a lv_fs_file_t object.
     */
    class File : public PointerWrapper<lv_fs_file_t, lv_mem_free> {
    public:
        using PointerWrapper::PointerWrapper;

        /** \fn File()
         *  \brief Constructor.
         */
        File();

        /** \fn ~File()
         *  \brief Destructor.
         */
        ~File();

        /** \fn lv_fs_res_t close()
         *  \brief Closes file.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        lv_fs_res_t close();

        /** \fn std::string read(uint32_t btr)
         *  \brief Reads a number of bytes from file.
         *  \returns bytes read, or an empty string if failed.
         */
        std::string read(uint32_t btr);

        /** \fn uint32_t write(const std::string & data)
         *  \brief Writes data to file.
         *  \param data: data to write.
         *  \returns the amount of bytes written.
         */
        uint32_t write(const std::string & data);

        /** \fn lv_fs_res_t seek(uint32_t pos, lv_fs_whence_t whence)
         *  \brief Moves access pointer to given position.
         *  \param pos: position to move to.
         *  \param whence: mode; absolute (LV_FS_SEEK_SET), relative (LV_FS_SEEK_CUR), 
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        lv_fs_res_t seek(uint32_t pos, lv_fs_whence_t whence);

        /** \fn uint32_t tell()
         *  \brief Gets position of access pointer.
         *  \returns position of access pointer.
         */
        uint32_t tell();
    };


    /** \class Directory
     *  \brief Wraps a lv_fs_dir_t object.
     */
    class Directory : public PointerWrapper<lv_fs_dir_t, lv_mem_free> {
    public:
        using PointerWrapper::PointerWrapper;

        /** \fn Directory()
         *  \brief Constructor.
         */
        Directory();

        /** \fn ~Directory()
         *  \brief Destructor.
         */
        ~Directory();

        /** \fn lv_fs_res_t close()
         *  \brief Closes directory.
         *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
         */
        lv_fs_res_t close();

        /** \fn std::string read()
         *  \brief Reads next entry in directory.
         *  \returns path to next entry, or empty string if failed.
         */
        std::string read();
        
    };

}
#endif // LV_USE_USER_DATA