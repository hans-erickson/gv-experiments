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

#include "edge_impl.h"

#include "object_impl.h"

#include <memory>

namespace gv
{
    template<>
    struct object::forward_iterator<edge>::impl_t
    {
        static edge
        create_edge(Agedge_t* ptr)
        {
            return edge { object::constructor_arg_t { ptr }  };
        }

        impl_t(const constructor_arg_t& iter_arg)
            : iter_arg_(iter_arg),
              e_(create_edge(iter_arg_.first()))
        {
        }

        void first()
        {
            e_ = create_edge(iter_arg_.first());
        }

        void next()
        {
            e_ = create_edge(iter_arg_.next(get_native_ptr(&e_)));
        }
        
        constructor_arg_t iter_arg_;

        edge e_;
    };


    // Rule of five members
    template<>
    object::forward_iterator<edge>::forward_iterator(const forward_iterator& other)
        : impl_(std::make_unique<impl_t>(*other.impl_))
    {}

    template<>
    object::forward_iterator<edge>::forward_iterator(forward_iterator&& other)
        : impl_(std::move(impl_))
    {}

    template<>
    object::forward_iterator<edge>::~forward_iterator() = default;

    template<>
    object::forward_iterator<edge>&
    object::forward_iterator<edge>::operator=(const forward_iterator& other)
    {
        impl_ = std::make_unique<impl_t>(*other.impl_);
        return *this;
    }

    template<>
    object::forward_iterator<edge>&
    object::forward_iterator<edge>::operator=(forward_iterator&& other)
    {
        impl_ = std::move(other.impl_);
        return *this;
    }

    
    template<>
    object::forward_iterator<edge>::forward_iterator(const constructor_arg_t& arg)
        : impl_(std::make_unique<impl_t>(arg))
    {
    }

    template<>
    object::forward_iterator<edge>&
    object::forward_iterator<edge>::operator++()
    {
        return *this;
    }

    template<>
    object::forward_iterator<edge>
    object::forward_iterator<edge>::operator++(int)
    {
        forward_iterator tmp(*this);
        operator++();
        return tmp;
    }
    
    template<>
    edge&
    object::forward_iterator<edge>::operator*()
    {
        throw std::runtime_error("TODO:");
    }

    template<>
    edge&
    object::forward_iterator<edge>::operator*() const
    {
        throw std::runtime_error("TODO:");
        //return (const_cast<forward_iterator*>(this));
    }

    template<>
    bool
    object::forward_iterator<edge>::operator==(const forward_iterator& other) const
    {
        return get_native_ptr(&impl_->e_) == get_native_ptr(&other.impl_->e_);
    }

    template<>
    bool
    object::forward_iterator<edge>::operator==(std::default_sentinel_t) const
    {
        return get_native_ptr(&impl_->e_) == nullptr;
    }

    edge::edge(const constructor_arg_t& arg)
        : object(arg)
    {
    }
}
