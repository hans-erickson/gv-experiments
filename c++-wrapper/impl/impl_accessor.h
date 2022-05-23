//
//  MIT License
//  
//  Copyright (c) 2021 Hans Erickson
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

#if !defined(GV_IMPL_ACCESSOR_H)
#define GV_IMPL_ACCESSOR_H


namespace gv
{
    /*
    struct object::factory_t
    {
        void* ptr = nullptr;
    };
    */

    /*struct context::impl_t
    {
        impl_t() : gvc(gvContext()) {}

        ~impl_t() { gvFreeContext(gvc); }
	
        GVC_t* gvc = nullptr;
    };
    */

    template<typename ObjectTraits>
    struct impl_traits;

    template<typename ObjectT> requires std::derived_from<ObjectT, object>
    auto native_handle_cast(const ObjectT& o)
    {
        using pointer_t = typename impl_traits<ObjectT>::pointer_t;
        return o.impl_->obj;
    }

    /*
    template<typename ObjectT> requires std::derived_from<ObjectT, object>
    struct object::native_handle
    {
        using pointer_t = typename impl_traits<ObjectT>::pointer_t;
        
        native_handle(ObjectT& o)
            : obj(reinterpret_cast<pointer_t>(o.impl_->obj))
        {
        }

        native_handle(const ObjectT& o)
            : obj(reinterpret_cast<pointer_t>(o.impl_->obj))
        {
        }

        native_handle(pointer_t ptr)
            : obj(ptr)
        {
        }
        
        operator pointer_t() const
        {
            return obj;
        }

        pointer_t obj = nullptr;
    };
    */

    /*
    template<>
    struct impl_accessor_t<context>
    {
        using pointer_t = GVC_t*;
        
        impl_accessor_t(context& o)
            : obj(o.impl_->gvc)
        {
        }

        impl_accessor_t(const context& o)
            : obj(o.impl_->gvc)
        {
        }

        operator pointer_t() const
        {
            return obj;
        }

        pointer_t obj = nullptr;
    };
    */
}

#endif // GV_IMPL_ACCESSOR_H