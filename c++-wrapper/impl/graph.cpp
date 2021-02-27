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
#include "../graph.h"

#include "../edge.h"
#include "../node.h"

#include "impl.h"
#include "streambuf_iodisc.h"

#include <cgraph.h>
#include <cstring>
#include <iostream>
//#include <functional>
#include <map>
#include <stdexcept>
#include <string>

namespace
{
    gv::streambuf_iodisc_t custom_iodisc;

    Agdisc_t custom_disc
    {
        &AgMemDisc,
        &AgIdDisc,
        &custom_iodisc
    };

    Agraph_t*
    agraph(const void* ptr)
    {
        return const_cast<Agraph_t*>(reinterpret_cast<const Agraph_t*>(ptr));
    }
}

namespace gv
{
    struct graph::impl_t
    {
        static Agraph_t*
        agopen(const char* name, desc_t desc)
        {
            const static std::map<gv::graph::desc_t, Agdesc_t> desc_map =
            {
                { gv::graph::desc_t::directed,          Agdirected         },
                { gv::graph::desc_t::strict_directed,   Agstrictdirected   },
                { gv::graph::desc_t::undirected,        Agundirected       },
                { gv::graph::desc_t::strict_undirected, Agstrictundirected }
            };

            std::string s(name);
            s.push_back('\0');
            return ::agopen(s.data(), desc_map.at(desc), nullptr);
        }

        static Agraph_t*
        agread(std::istream& in)
        {
            return ::agread(in.rdbuf(), &custom_disc);
        }

        static Agraph_t*
        agmemread(const std::string& str)
        {
            return ::agmemread(str.c_str());
        }
    };

    graph::graph(const factory_t& f)
        : object(f)
    {
    }

    graph::graph(const char* name,
                 desc_t desc)
        : object(factory_t{impl_t::agopen(name, desc)})
    {
    }

    graph::graph(std::istream& in)
        : object(factory_t{impl_t::agread(in)})
    {
    }

    graph::graph(const std::string& str)
        : object(factory_t{impl_t::agmemread(str)})
    {
    }

    graph::~graph() = default;

    bool
    graph::is_directed() const
    {
        return agisdirected(agraph(shared_obj()));
    }

    bool
    graph::is_simple() const
    {
        return agissimple(agraph(shared_obj()));
    }

    bool
    graph::is_strict() const
    {
        return agisstrict(agraph(shared_obj()));
    }

    bool
    graph::is_undirected() const
    {
        return agisundirected(agraph(shared_obj()));
    }

    node
    graph::create_node(const char* name)
    {
        std::string s(name);
        s.push_back('\0');
        return factory_t(agnode(agraph(shared_obj()), s.data(), true));
    }

    node
    graph::create_node(id_t id)
    {
        return factory_t(agidnode(agraph(shared_obj()), id, true));
    }

    std::optional<node>
    graph::find_node(const char* name)
    {
        std::optional<gv::node> result;

        std::string s(name);
        s.push_back('\0');

        auto nptr = agnode(agraph(shared_obj()), s.data(), false);
        if (nptr)
        {
            result = gv::node(gv::node::factory_t{nptr});
        }

        return result;
    }

    std::optional<node>
    graph::find_node(id_t id)
    {
        std::optional<gv::node> result;

        auto nptr = agidnode(agraph(shared_obj()), id, false);
        if (nptr)
        {
            result = gv::node(gv::node::factory_t{nptr});
        }

        return result;
    }

    std::vector<node>
    graph::nodes() const
    {
        std::vector<node> result;

        for (auto n = agfstnode(agraph(shared_obj()));
             n != nullptr; n = agnxtnode(agraph(shared_obj()),n))
        {
            result.emplace_back(node::factory_t(n));
        }

        return result;
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
