/** \file lv_thin_wrapper.h
 *  \brief Thin C++ wrapper template classes around LVGL objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include <memory>
#include <functional>
#include "lvgl.h"

/** \namespace lvgl
 *  \brief LVGL C++ wrappers.
 */
namespace lvgl {

    /** \typedef template <typename Class> using RawDblArray
     *  \brief A unique_ptr wrapping a raw double array with custom deleter.
     *  \param Class: array type.
     */
    template <typename Class>
    using RawDblArray = std::unique_ptr<Class*, std::function<void(Class**)>>;

    /** \brief Generates a deleter function for a double array of given type and size.
     *  \tparam Class: array type.
     *  \param size: array size (1st dimension).
     *  \returns a deleter function for double arrays of given type and size.
     */
    template <typename Class> std::function<void(Class**)> RawDblArrayDeleter(size_t size) {
        return [size](Class** obj) {
            std::for_each(obj, obj + size, std::default_delete<Class[]>());
            delete[] obj;
        };
    }

    /** \fn template <typename Class> RawDblArray<Class> make_double_array(size_t size)
     *  \brief Creates a double array of given type and size wrapped in a unique_ptr.
     *  \tparam Class: array type.
     *  \param size: array size (1st dimension).
     *  \returns unique_ptr wrapping a double array of given type.
     */
    template <typename Class> RawDblArray<Class> make_double_array(size_t size) {
        return RawDblArray<Class>(new Class*[size], RawDblArrayDeleter<Class>(size));
    }

    /** \fn static RawDblArray<char> str_vector_to_char_array(const std::vector<std::string> & arr)
     *  \brief Conversion function from string vector to double char array.
     *  \param arr: string vector.
     *  \returns a double char array with a copy of the content of input array.
     */
    static RawDblArray<char> str_vector_to_char_array(const std::vector<std::string> & arr) {
        auto raw_arr = make_double_array<char>(arr.size());
        for (size_t n=0; n<arr.size(); n++) {
            raw_arr.get()[n] = static_cast<char*>(malloc(arr[n].size()));
            std::copy(arr[n].begin(), arr[n].end(), raw_arr.get()[n]);
        }
        return raw_arr;
    }

    /** \typedef template <auto DeleterFunction> CustomDeleter
     *  \brief Wraps a C deleter function for use with smart pointers.
     * 
     *  This relies on the behaviour of the call operator that assumes
     *  that the left-hand side argument should be a function, and therefore
     *  gets cast to function pointer. At the same time, the integral_constant
     *  instance gives the wrapped value type as its own type.
     * 
     *  \tparam DeleterFunction: C deleter function.
     */
    template <auto DeleterFunction>
    using CustomDeleter = std::integral_constant<std::decay_t<decltype(DeleterFunction)>, DeleterFunction>;
    
    /** \typedef template <typename WrappedType, auto DeleterFunction> LvPointer
     *  \brief A unique pointer that wraps an object and defines a deleter from a deleter function.
     *  \tparam WrappedType: object type.
     *  \tparam DeleterFunction: deleter function.
     */
    template <typename WrappedType, auto DeleterFunction>
    using LvPointer = std::unique_ptr<WrappedType, CustomDeleter<DeleterFunction> >;

    /** \brief Template class meant to wrap C LVGL objects for C++.
     * 
     *  This wrapper holds an instance as a class member.
     * 
     *  \tparam LvClass: LVGL object type.
     */
    template <typename LvClass> class ThinWrapper {
    protected:
        /** \property LvClass lv_obj
         *  \brief Wrapped object.
         */
        LvClass lv_obj;

        /** \typedef LvWrapperType
         *  \brief A short hand for the wrapper class type ThinWrapper<LvClass>
         */
        using LvWrapperType = ThinWrapper<LvClass>;

    public:

        /** \fn ThinWrapper()
         *  \brief Default constructor.
         */
        ThinWrapper() = default;

        /** \fn ThinWrapper(const LvClass & obj)
         *  \brief Copy conversion function with LvClass argument
         */
        ThinWrapper(const LvClass & obj) {
            this->lv_obj = obj;
        }

        /** \fn ThinWrapper(const ThinWrapper<LvClass> & obj)
         *  \brief Copy constructor
         */
        ThinWrapper(const ThinWrapper<LvClass> & obj) = default;

        /** \fn ThinWrapper & operator=(const ThinWrapper<LvClass> & obj)
         *  \brief Copy assignment operator
         */
        ThinWrapper & operator=(const ThinWrapper<LvClass> & obj) = default;

        /** \fn ThinWrapper(LvClass && obj)
         *  \brief Move conversion function with LvClass argument (take ownership of obj)
         */
        ThinWrapper(LvClass && obj) {
            this->lv_obj = std::forward<LvClass>(obj);
            obj = LvClass();
        }

        /** \fn ThinWrapper(ThinWrapper<LvClass> && obj)
         *  \brief Move constructor
         */
        ThinWrapper(ThinWrapper<LvClass> && obj) = default;

        /** \fn ThinWrapper & operator=(ThinWrapper<LvClass> && obj)
         *  \brief Move assignment operator
         */
        ThinWrapper & operator=(ThinWrapper<LvClass> && obj) = default;

        /** \fn LvClass & raw()
         *  \brief Access to owned raw LvClass object.
         *  \returns a reference to the owned LvClass object.
         */
        LvClass & raw() {
            return this->lv_obj;
        }

        /** \fn const LvClass & raw() const
         *  \brief Access to owned raw LvClass object (const version).
         *  \returns a const reference to the owned LvClass object.
         */
        const LvClass & raw() const {
            return this->lv_obj;
        }

        /** \fn LvClass & raw_ptr()
         *  \brief Access to owned raw LvClass object (pointer version).
         *  \returns a pointer to the owned LvClass object.
         */
        LvClass * raw_ptr() {
            return &(this->lv_obj);
        }

        /** \fn const LvClass & raw_ptr() const
         *  \brief Access to owned raw LvClass object (const pointer version).
         *  \returns a const pointer to the owned LvClass object.
         */
        const LvClass * raw_ptr() const {
            return &(this->lv_obj);
        }
    };
    

    /** \brief Template class meant to wrap C LVGL objects for C++.
     *  
     *  This wrapper stores a pointer to an object and provides the
     *  possibility to specify a deleter function. It is important to
     *  define a constructor that allocates memory for the C object.
     *  
     *  \tparam LvClass: LVGL type.
     *  \tparam lv_deleter: deleter function.
     */
    template <typename LvClass, auto lv_deleter> class ThinPointerWrapper {
    protected:
        /** \typedef LvPointerType
         *  \brief A shorthand for the wrapped object pointer type LvPointer<LvClass, lv_deleter>
         */
        using LvPointerType = LvPointer<LvClass, lv_deleter>;

        /** \typedef LvWrapperType
         *  \brief A shorthand for the wrapper class type ThinPointerWrapper<LvClass, lv_deleter>
         */
        using LvWrapperType = ThinPointerWrapper<LvClass, lv_deleter>;

        /** \typedef lv_cls_ptr
         *  \brief A shorthand for LvClass* available to casting operators.
         */
        using lv_cls_ptr = LvClass*;

        /** \property LvPointerType lv_obj
         *  \brief Pointer to the managed C LVGL object.
         */
        LvPointerType lv_obj;

    public:
        /** \fn ThinPointerWrapper()
         *  \brief Default constructor.
         */
        ThinPointerWrapper() = default;

        // no copy constructor and copy assignment operator
        ThinPointerWrapper(const LvPointerType & obj) = delete;
        ThinPointerWrapper & operator=(const LvPointerType & obj) = delete;

        /** \fn ThinPointerWrapper(LvClass * obj)
         *  \brief Wrapping function with LvClass* argument.
         */
        ThinPointerWrapper(LvClass * obj) {
            this->lv_obj = LvPointerType(obj);
        }

        /** \fn ThinPointerWrapper(LvPointerType && obj)
         *  \brief Move-wrapping function with LvPointerType argument.
         */
        ThinPointerWrapper(LvPointerType && obj) {
            this->lv_obj = std::move(obj);
            obj = nullptr;
        }

        /** \fn ThinPointerWrapper(ThinPointerWrapper<LvClass, lv_deleter> && obj)
         *  \brief Move constructor.
         */
        ThinPointerWrapper(LvWrapperType && obj) = default;

        /** \fn ThinPointerWrapper & operator=(ThinPointerWrapper<LvClass, lv_deleter> && obj)
         *  \brief Move assignment operator.
         */
        ThinPointerWrapper & operator=(LvWrapperType && obj) {
            this->lv_obj = LvPointerType(obj.raw_ptr());
            obj.lv_obj = nullptr;
            return *this;
        }

        /** \fn LvClass & raw()
         *  \brief Access to owned raw LvClass object.
         *  \returns a reference to the owned LvClass object.
         */
        LvClass & raw() {
            return *this->lv_obj.get();
        }

        /** \fn const LvClass & raw() const
         *  \brief Access to owned raw LvClass object (const version).
         *  \returns a const reference to the owned LvClass object.
         */
        const LvClass & raw() const {
            return *this->lv_obj.get();
        }

        /** \fn LvClass & raw_ptr()
         *  \brief Access to owned raw LvClass object (pointer version).
         *  \returns a pointer to the owned LvClass object.
         */
        LvClass * raw_ptr() {
            return this->lv_obj.get();
        }

        /** \fn const LvClass & raw_ptr() const
         *  \brief Access to owned raw LvClass object (const pointer version).
         *  \returns a const pointer to the owned LvClass object.
         */
        const LvClass * raw_ptr() const {
            return this->lv_obj.get();
        }
    };

}
