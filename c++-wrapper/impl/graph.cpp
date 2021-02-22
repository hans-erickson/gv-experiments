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
#include "../node.h"

#include "impl.h"

#include <cgraph.h>
#include <cstring>
#include <iostream>
//#include <functional>
#include <map>
#include <stdexcept>
#include <string>

namespace
{
    struct streambuf_disc_t
    {
        static std::streambuf&
        sb(void* chan)
        {
            return *reinterpret_cast<std::streambuf*>(chan);
        }

        static int afread(void* chan,
                          char* buf,
                          int bufsize)
        {
            return sb(chan).sgetn(buf, bufsize);
        }

        static int flush(void* chan)
        {
            return sb(chan).pubsync();
        }

        static int putstr(void* chan,
                          const char* str)
        {
            return sb(chan).sputn(str, std::strlen(str));
        }
    };

    Agiodisc_t custom_iodisc
    {
        &streambuf_disc_t::afread,
        &streambuf_disc_t::putstr,
        &streambuf_disc_t::flush
    };

    Agdisc_t custom_disc
    {
        &AgMemDisc,
        &AgIdDisc,
        &custom_iodisc
    };
}

/*

typedef struct {Agmemdisc_t*mem;Agiddisc_t*id;Agiodisc_t*io;} Agdisc_t;

Agmemdisc_t AgMemDisc;Agiddisc_t  AgIdDisc;Agiodisc_t  AgIoDisc;Agdisc_t    AgDefaultDisc

typedef struct Agiodisc_s {int (*afread)(void*chan, char*buf, int bufsize);int (*putstr)(void*chan, char*str);int (*flush)(void*chan);} Agiodisc_t 
*/

namespace
{
    std::map<gv::graph::desc_t, Agdesc_t> desc_map =
    {
        { gv::graph::desc_t::directed,          Agdirected         },
        { gv::graph::desc_t::strict_directed,   Agstrictdirected   },
        { gv::graph::desc_t::undirected,        Agundirected       },
        { gv::graph::desc_t::strict_undirected, Agstrictundirected }
    };
}

namespace gv
{
    struct graph::impl_t
    {
        impl_t(Agraph_t* ag)
            : agraph(ag)
        {
            for (auto n = agfstnode(agraph); n != nullptr; n = agnxtnode(agraph,n))
            {
                add_node(n);
            }
        }

        ~impl_t()
        {
            agclose(agraph);
        }

        node&
        add_node(Agnode_t* n)
        {
            if (n == nullptr)
            {
                throw std::runtime_error("Invalid node");
            }
            node_map[n] = std::make_shared<node>(gv::node::factory_t{n});
            return *node_map[n];
        }

        node&
        create_node(const char* name)
        {
            std::string s(name);
            s.push_back('\0');
            // CGRAPH_API Agnode_t *agnode(Agraph_t * g, char *name, int createflag);
            return add_node(agnode(agraph, s.data(), true));
        }

        node&
        create_node(id_t id)
        {
            return add_node(agidnode(agraph, id, true));
        }

        node*
        find_node(const char* name)
        {
            std::string s(name);
            s.push_back('\0');
            // CGRAPH_API Agnode_t *agnode(Agraph_t * g, char *name, int createflag);
            return node_map[agnode(agraph, s.data(), false)].get();
            
            // CGRAPH_API Agnode_t *agnode(Agraph_t * g, char *name, int createflag);
        }

        node*
        find_node(id_t id)
        {
            return node_map[agidnode(agraph, id, false)].get();
        }

        bool
        is_directed() const
        {
            return agisdirected(agraph);
        }

        bool
        is_simple() const
        {
            return agissimple(agraph);
        }

        bool
        is_strict() const
        {
            return agisstrict(agraph);
        }

        bool
        is_undirected() const
        {
            return agisundirected(agraph);
        }

        std::vector<std::reference_wrapper<node>>
        nodes() const
        {
            std::vector<std::reference_wrapper<node>> result;
            for (auto n = agfstnode(agraph); n != nullptr; n = agnxtnode(agraph,n))
            {
                result.emplace_back(*node_map.at(n).get());
            }
            return result;
        }

        Agraph_t* agraph = nullptr;
        std::map<Agnode_t*, std::shared_ptr<node>> node_map;
    };

    graph::graph(const char* name,
                 desc_t desc)
    {
        std::string s(name);
        s.push_back('\0');
        impl_ = std::make_unique<impl_t>(agopen(s.data(), desc_map[desc], nullptr));
        // CGRAPH_API Agraph_t *agopen(char *name, Agdesc_t desc, Agdisc_t * disc);
    }

    graph::graph(std::istream& in)
        : impl_(std::make_unique<impl_t>(agread(in.rdbuf(), &custom_disc)))
    //: std::make_unique<impl_t>(name, desc, nullptr)
    {
        // TODO: Use istream in custom discipline
        // CGRAPH_API Agraph_t *agread(void *chan, Agdisc_t * disc);
    }

    graph::graph(const std::string& str)
        : impl_(std::make_unique<impl_t>(agmemread(str.c_str())))
    {
        // CGRAPH_API Agraph_t *agmemread(const char *cp);
    }

    graph::~graph() = default;

    bool
    graph::is_directed() const
    {
        return impl_->is_directed();
    }

    bool
    graph::is_simple() const
    {
        return impl_->is_simple();
    }

    bool
    graph::is_strict() const
    {
        return impl_->is_strict();
    }

    bool
    graph::is_undirected() const
    {
        return impl_->is_undirected();
    }

    node&
    graph::create_node(const char* name)
    {
        return impl_->create_node(name);
    }

    node&
    graph::create_node(id_t id)
    {
        return impl_->create_node(id);
    }

    node*
    graph::find_node(const char* name)
    {
        return impl_->find_node(name);
    }

    node*
    graph::find_node(id_t id)
    {
        return impl_->find_node(id);
    }

    std::vector<std::reference_wrapper<node>>
    graph::nodes() const
    {
        return impl_->nodes();
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
