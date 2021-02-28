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

            tmp_string s(name);
            return ::agopen(s.str(), desc_map.at(desc), &custom_disc);
        }

        static Agraph_t*
        agread(const std::istream& in)
        {
            return ::agread(in.rdbuf(), &custom_disc);
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

    graph::graph(const std::istream& in)
        : object(factory_t{impl_t::agread(in)})
    {
    }

    // TODO: We need to call agclose in most cases, probably. (Maybe in all cases?)
    graph::~graph() = default;

    bool
    graph::is_directed() const
    {
        return agisdirected(impl_accessor_t(*this));
    }

    bool
    graph::is_simple() const
    {
        return agissimple(impl_accessor_t(*this));
    }

    bool
    graph::is_strict() const
    {
        return agisstrict(impl_accessor_t(*this));
    }

    bool
    graph::is_undirected() const
    {
        return agisundirected(impl_accessor_t(*this));
    }

    node
    graph::create_node(const char* name)
    {
        tmp_string s(name);
        return factory_t(agnode(impl_accessor_t(*this), s.str(), true));
    }

    node
    graph::create_node(id_t id)
    {
        return factory_t(agidnode(impl_accessor_t(*this), id, true));
    }

    std::optional<node>
    graph::find_node(const char* name)
    {
        std::optional<gv::node> result;

        tmp_string s(name);

        auto nptr = agnode(impl_accessor_t(*this), s.str(), false);
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

        auto nptr = agidnode(impl_accessor_t(*this), id, false);
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

        for (auto n = agfstnode(impl_accessor_t(*this));
             n != nullptr; n = agnxtnode(impl_accessor_t(*this), n))
        {
            result.emplace_back(node::factory_t(n));
        }

        return result;
    }

    void
    graph::write(std::ostream& out)
    {
        agwrite(impl_accessor_t(*this), out.rdbuf());
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
