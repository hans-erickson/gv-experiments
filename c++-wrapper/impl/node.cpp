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

#include "../node.h"
#include "../graph.h"

#include "impl.h"

#include <string>

auto get_ptr = gv::common_impl::get_agraph_ptr;

namespace gv
{
    struct node::impl_t
    {
        impl_t(Agnode_t* ag)
            : agnode(ag)
        {
        }

        std::string
        name() const
        {
            return agnameof(agnode);
        }

        Agnode_t* agnode = nullptr;
    };

    node::node(const factory_t& f)
        : impl_(std::make_unique<impl_t>(f.ptr))
    {
    }

    node::~node() = default;

    std::string
    node::name() const
    {
        return impl_->name();
    }

    /*
    struct node::impl_t
    {
        impl_t(Agnode_t* ag)
            : agnode(ag)
        {
        }

        Agnode_t* agnode = nullptr;
    };
    
    node::node(graph& gr,
               const char* name,
               bool create)
    {
        std::string s(name);
        s.push_back('\0');
        impl_ = std::make_unique<impl_t>(agnode(get_ptr(gr), s.data(), create));
    }

    // Anonymous node
    // CGRAPH_API Agnode_t *agnode(Agraph_t * g, char *name, int createflag);
    node::node(graph& gr)
        : node(gr, nullptr, true)
    {
    }

    // CGRAPH_API Agnode_t *agidnode(Agraph_t * g, IDTYPE id, int createflag);
    node::node(graph& gr, id_t id, bool create)
        : impl_(std::make_unique<impl_t>(agidnode(get_ptr(gr), id, create)))
    {
    }

    // CGRAPH_API Agnode_t *agsubnode(Agraph_t * g, Agnode_t * n, int createflag)
    node::node(graph& gr, node& subnode, bool create)
    {
    }

    node::~node() = default;
    */
}
