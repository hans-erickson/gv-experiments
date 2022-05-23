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

#include "graph_impl.h"

#include "edge_impl.h"
#include "node_impl.h"
#include "object_impl.h"

#include "impl_accessor.h"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>


namespace gv
{
    /*
    template<>
    object::native_pointer_traits<graph>::pointer_type
    object::get_native_ptr<graph>(graph* ptr)
    {
        return reinterpret_cast<native_pointer_traits<graph>::pointer_type>(ptr->impl_.get());
    }
    */

    graph::graph(const char* name,
                 desc_t desc)
        : object(object::constructor_arg_t(impl_t::agopen(name, desc)))
    {
    }

    graph::graph(const std::istream& in)
        : object(impl_t::agread(in))
    {
    }

    // TODO: We need to call agclose in most cases, probably. (Maybe in all cases?)
    graph::~graph() = default;

    bool
    graph::is_directed() const
    {
        return ::agisdirected(get_native_ptr(this));
    }

    bool
    graph::is_simple() const
    {
        return ::agissimple(get_native_ptr(this));
    }

    bool
    graph::is_strict() const
    {
        return ::agisstrict(get_native_ptr(this));
    }

    bool
    graph::is_undirected() const
    {
        return ::agisundirected(get_native_ptr(this));
    }

    node
    graph::create_node(const char* name)
    {
        tmp_string s(name);
        return constructor_arg_t { ::agnode(get_native_ptr(this), s.str(), true) };
            //throw std::runtime_error("TODO:");
        //return factory_t(agnode(native_handle_t(*this), s.str(), true));
    }

    node
    graph::create_node(id_t id)
    {
        throw std::runtime_error("TODO:");
        //return factory_t(agidnode(native_handle_t(*this), id, true));
    }

    std::optional<node>
    graph::find_node(const char* name)
    {
        std::optional<gv::node> result;

        tmp_string s(name);

        auto nptr = ::agnode(get_native_ptr(this), s.str(), false);
        if (nptr)
        {
            result = gv::node(constructor_arg_t{nptr});
        }

        return result;
    }

    std::optional<node>
    graph::find_node(id_t id)
    {
        std::optional<gv::node> result;

        auto nptr = agidnode(get_native_ptr(this), id, false);
        if (nptr)
        {
            throw std::runtime_error("TODO:");
            //result = gv::node(gv::node::factory_t{nptr});
        }

        return result;
    }

    graph::node_view
    graph::nodes() const
    {
        node_iterator::constructor_arg_t arg {
            .first_func_ptr   = ::agfstnode,
            .next_func_ptr    = ::agnxtnode,
            .last_func_ptr    = ::aglstnode,
            .prev_func_ptr    = ::agprvnode,
            .native_graph_ptr = ::agraphof(get_native_ptr(this))
        };

        return node_view { node_iterator{ arg } };

        //node_iterator fwd(constructor_arg_t{::agfstnode(get_native_ptr(this))});
        //node_reverse_iterator rev(native_handle<node>{::aglstnode(native_handle(*this))});
        
        //graph::node_view result(agfstnode(native_handle_t(*this)),
        //                        aglstnode(native_handle_t(*this)));

        /*
        std::vector<node> result;

        for (auto n = agfstnode(native_handle_t(*this));
             n != nullptr; n = agnxtnode(native_handle_t(*this), n))
        {
            throw std::runtime_error("TODO:");
            //result.emplace_back(node::factory_t(n));
        }
        */

        //return node_view(fwd);
    }

    void
    graph::write(std::ostream& out)
    {
        agwrite(get_native_ptr(this), out.rdbuf());
    }
}

/*
•Agraph_t: a graph or subgraph
•Agnode_t: a node from a particular graph or subgraph
•Agedge_t: an edge from a particular graph or subgraph
•Agsym_t: a descriptor for a string-value pair attribute
•Agrec_t: an internal C data record attribute of a graph object
*/

/*
{
    for (n = agfstnode(g); n; n = agnxtnode(g,n))
    {
        for (e = agfstout(g,n); e; e = agnxtout(g,e))
        {
            // do something with e
        }
    }
}
*/
