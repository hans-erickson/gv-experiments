//
//  MIT License
//  
//  Copyright (c) 2022 Hans Erickson
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//  

#if !defined(GV_OBJECT_IMPL_H)
#define GV_OBJECT_IMPL_H

#include "../object.h"

#include <cgraph.h>

namespace gv
{
    template<typename T>
    inline auto
    create_non_owned_ptr(T* ptr)
    {
        return std::shared_ptr<T>(ptr, [](void*){});
    }
    
    template<>
    struct object::native_pointer_traits<object>
    {
        using pointer_type = void*;
    };

    struct object::constructor_arg_t
    {
        template<typename T>
        static auto
        create_impl_ptr(T* t)
        {
            impl_t* ptr = reinterpret_cast<impl_t*>(t);
            std::shared_ptr<T> t_ptr { create_non_owned_ptr(t) };
            return std::shared_ptr<impl_t>(t_ptr, ptr);
        }

        template<typename T>
        constructor_arg_t(T* t)
            : ptr_{create_impl_ptr(t)}
        {
        }

        std::shared_ptr<impl_t> ptr_;
    };

    // The implementation gets stored as a shared pointer
    // to this type. What we actually want to store, though,
    // is that native pointer type.
    struct object::impl_t
    {
    };
}

#endif // !defined(GV_OBJECT_IMPL_H)
