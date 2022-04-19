/* This example shows how to write a filesystem driver the C++ way */
#include "lvglpp/lvglpp.h"
#include "lvglpp/misc/fs.h"


class CustomFileSystem : public lvgl::misc::FileSystem {
private:
    /** \fn bool ready_cb()
     *  \brief Tells if the file system is ready to use.
     *  \returns true if file system is ready, false otherwise.
     */
    bool ready_cb() override {
        // place here the code to check if the file system is ready
        return true;
    }

    /** \fn void * open_cb(const char * path, lv_fs_mode_t mode)
     *  \brief Opens a file on the file system.
     *  \param path: file path.
     *  \param mode: access mode.
     *  \returns pointer to the file descriptor, or nullptr if failed.
     */
    void * open_cb(const char * path, lv_fs_mode_t mode) override {
        // write here what you need to do to open a file;
        // you can produce any kind of file descriptor, but you need
        // to return a raw pointer to it, cast to void*. Don't forget
        // to store the file descriptor somewhere until you close the file.
        return static_cast<void*>(fd_pointer);
    }

    /** \fn lv_fs_res_t close_cb(void * file_p)
     *  \brief Closes a file.
     *  \param file_p: pointer to the file descriptor.
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t close_cb(void * file_p) override {
        // write here what to do to close a file; the file descriptor
        // you obtained in open_cb will be fed here as void*. You need
        // to cast it back to the right type first.
        auto fd_pointer = reinterpret_cast<good_ptr_type*>(file_p);
        // assess if closing was succesful; if not, you can pick a reason from
        // the lv_fs_res_t enum type.
        return result;
    }

    /** \fn lv_fs_res_t read_cb(void * file_p, void * buf, uint32_t btr, uint32_t * br)
     *  \brief Reads data from a file.
     *  \param file_p: pointer to the file descriptor.
     *  \param buf: pointer to the recipient data buffer.
     *  \param btr: number of bytes to read.
     *  \param br: number of bytes actually read.
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t read_cb(void * file_p, void * buf, uint32_t btr, uint32_t * br) override {
        // place here the code to read from an open file;
        // as above, you need first to cast the file descriptor pointer to the right type
        auto fd_pointer = reinterpret_cast<good_ptr_type*>(file_p);
        // you then need to fill buffer buf with read bytes; you can return an error
        // code if an error occurred.
        return result;
    }

    /** \fn lv_fs_res_t write_cb(void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
     *  \brief Writes data to a file.
     *  \param file_p: pointer to the file descriptor.
     *  \param buf: pointer to the recipient data buffer.
     *  \param btw: number of bytes to write.
     *  \param bw: number of bytes actually written.
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t write_cb(void * file_p, const void * buf, uint32_t btw, uint32_t * bw) override {
        // write here the code to write to an open file;
        // as above, you need first to cast the file descriptor pointer to the right type
        auto fd_pointer = reinterpret_cast<good_ptr_type*>(file_p);
        // you can then write the content of buf into the file;
        // assess if you need to return a success or error code
        return result;
    }

    /** \fn lv_fs_res_t seek_cb(void * file_p, uint32_t pos, lv_fs_whence_t whence)
     *  \brief Moves access pointer within file.
     *  \param file_p: pointer to the file descriptor.
     *  \param pos: position to move to.
     *  \param whence: mode; absolute (LV_FS_SEEK_SET), relative (LV_FS_SEEK_CUR), 
     *  or absolute from end of file (LV_FS_SEEK_END).
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t seek_cb(void * file_p, uint32_t pos, lv_fs_whence_t whence) override {
        // place here what to do to move inside a file;
        // as above, you need first to cast the file descriptor pointer to the right type
        auto fd_pointer = reinterpret_cast<good_ptr_type*>(file_p);
        // seek through file and return a result code
        return result;
    }

    /** \fn lv_fs_res_t tell_cb(void * file_p, uint32_t * pos_p)
     *  \brief Gets position of access pointer within file.
     *  \param file_p: pointer to the file descriptor.
     *  \param pos_p: resulting position.
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t tell_cb(void * file_p, uint32_t * pos_p) override {
        // write here the function that retrieves the current position in the file;
        // as above, you need first to cast the file descriptor pointer to the right type
        auto fd_pointer = reinterpret_cast<good_ptr_type*>(file_p);
        // place file position in pos_p; return appropriate result code
        return result;
    }

    /** \fn void * dir_open_cb(const char * path)
     *  \brief Opens a directory on the file system.
     *  \param path: directory path.
     *  \returns pointer to the directory descriptor.
     */
    void * dir_open_cb(const char * path) override {
        // fill this callback with the code to open a directory;
        // this is what will be called prior to listing the dir content;
        // you can produce any kind of directory descriptor, but you need
        // to return a raw pointer to it, cast to void*. Don't forget
        // to store the directory descriptor somewhere until you close it.
        return static_cast<void*>(dir_pointer);
    }

    /** \fn lv_fs_res_t dir_read_cb(void * rddir_p, char * fn)
     *  \brief Reads next entry from a directory.
     *  \param rddir_p: pointer to the directory descriptor.
     *  \param fn: pointer to the recipient buffer for entry path.
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t dir_read_cb(void * rddir_p, char * fn) override {
        // write here the code to read a directory content;
        // this should read the next file in the directory;
        // as for files, you need first to cast the directory descriptor pointer
        // to the right type
        auto dd_pointer = reinterpret_cast<good_ptr_type*>(rddir_p);
        // place the file name in fn; for a directory, add a / in front;
        // when reaching then end, leave fn empty;
        // return appropriate result code
        return result;
    }

    /** \fn lv_fs_res_t dir_close_cb(void * rddir_p)
     *  \brief Closes a directory.
     *  \param rddir_p: pointer to the directory descriptor.
     *  \returns result code: LV_FS_RES_OK if successful, LV_RES_* otherwise.
     */
    lv_fs_res_t dir_close_cb(void * rddir_p) override {
        // place here what needs to be done to close a directory;
        // as above, you need first to cast the directory descriptor pointer
        // to the right type
        auto dd_pointer = reinterpret_cast<good_ptr_type*>(rddir_p);
        // try to close directory and return appropriate result code
        return result;
    }

public:
    CustomFileSystem(char letter) : FileSystem(letter) {
        // if necessary, you can define a custom constructor; you must
        // call FileSystem(letter) from within your custom constructor
        // to initialize the driver properly
    }
};


void main() {
   // initialize LVGL
    lvgl::init();
    // create filesystem object associated with letter A
    static auto fs = CustomFileSystem("A");
}
