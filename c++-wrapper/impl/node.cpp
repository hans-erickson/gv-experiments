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

#include "node_impl.h"

#include "edge_impl.h"
#include "object_impl.h"

#include "tmp_string.h"

#include <optional>
#include <string>

namespace gv
{
    template<>
    struct object::bidirectional_iterator<node>::impl_t
    {
        static node
        create_node(Agnode_t* ptr)
        {
            return node { object::constructor_arg_t { ptr}  };
        }

        impl_t(const constructor_arg_t& iter_arg)
            : iter_arg_(iter_arg),
              n_(create_node(iter_arg_.first()))
        {
        }

        void first()
        {
            n_ = create_node(iter_arg_.first());
        }

        void last()
        {
            n_ = create_node(iter_arg_.last());
        }

        void next()
        {
            n_ = create_node(iter_arg_.next(get_native_ptr(&n_)));
        }

        void prev()
        {
            n_ = create_node(iter_arg_.prev(get_native_ptr(&n_)));
        }
        
        constructor_arg_t iter_arg_;

        node n_;
    };

    template<>
    object::bidirectional_iterator<node>::bidirectional_iterator()
        : impl_(nullptr)
    {
    }

    template<>
    object::bidirectional_iterator<node>::bidirectional_iterator(const constructor_arg_t& arg)
        : impl_(std::make_shared<impl_t>(arg))
    {}

    template<>
    object::bidirectional_iterator<node>::bidirectional_iterator(const bidirectional_iterator& i)
        : impl_(i.impl_)
    {}

    template<>
    object::bidirectional_iterator<node>&
    object::bidirectional_iterator<node>::operator++()
    {
        impl_->next();
        return *this;
    }

    template<>
    object::bidirectional_iterator<node>&
    object::bidirectional_iterator<node>::operator--()
    {
        if (get_native_ptr(&impl_->n_))
        {
            impl_->prev();
        }
        else
        {
            impl_->last();
        }
        return *this;
    }
    
    template<>
    object::bidirectional_iterator<node>
    object::bidirectional_iterator<node>::operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }
    
    template<>
    object::bidirectional_iterator<node>
    object::bidirectional_iterator<node>::operator--(int)
    {
        auto tmp = *this;
        --(*this);
        return tmp;
    }
    
    template<>
    node&
    object::bidirectional_iterator<node>::operator*()
    {
        return impl_->n_;
    }

    template<>
    node&
    object::bidirectional_iterator<node>::operator*() const
    {
        return impl_->n_;
    }

    template<>
    bool
    object::bidirectional_iterator<node>::operator==(const bidirectional_iterator& other) const
    {
        return get_native_ptr(&impl_->n_) == get_native_ptr(&other.impl_->n_);
    }

    template<>
    bool
    object::bidirectional_iterator<node>::operator==(std::default_sentinel_t) const
    {
        return get_native_ptr(&impl_->n_) == nullptr;
    }


    node::node(const constructor_arg_t& arg)
        : object(arg)
    {
    }

    node::~node() = default;

    bool
    node::operator==(const node& other) const
    {
        return (get_native_ptr(this) == get_native_ptr(&other));
    }

    node::edge_view
    node::in_edges() const
    {
        forward_iterator<edge>::constructor_arg_t arg {
            .first_func_ptr   = ::agfstin,
            .next_func_ptr    = ::agnxtin,
            .native_graph_ptr = ::agraphof(get_native_ptr(this)),
            .native_node_ptr  = get_native_ptr(this)
        };

        return edge_view { edge_iterator{arg} };
    }

    node::edge_view
    node::out_edges() const
    {
        forward_iterator<edge>::constructor_arg_t arg {
            .first_func_ptr   = ::agfstout,
            .next_func_ptr    = ::agnxtout,
            .native_graph_ptr = ::agraphof(get_native_ptr(this)),
            .native_node_ptr  = get_native_ptr(this)
        };

        return edge_view { edge_iterator{arg} };
    }

    edge
    node::join(node& other, const char* name)
    {
        tmp_string s(name);

        auto this_node = get_native_ptr(this);
        auto other_node = get_native_ptr(&other);
        auto g = ::agraphof(this_node);

        return edge { ::agedge(g, this_node, other_node, s.str(), true) };
    }
}
