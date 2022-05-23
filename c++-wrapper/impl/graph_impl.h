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

#if !defined(GV_GRAPH_IMPL_H)
#define GV_GRAPH_IMPL_H

#include "../graph.h"

#include "object_impl.h"

#include "impl_accessor.h"
#include "streambuf_iodisc.h"
#include "tmp_string.h"

#include <cgraph.h>
#include <map>

namespace gv
{
    gv::streambuf_iodisc_t custom_iodisc;

    Agdisc_t custom_disc
    {
        &AgMemDisc,
        &AgIdDisc,
        &custom_iodisc
    };

    template<>
    struct object::native_pointer_traits<graph>
    {
        using pointer_type = Agraph_t*;
    };

    template<>
    struct object::native_pointer_traits<const graph>
    {
        using pointer_type = Agraph_t*;
    };

    template<>
    struct impl_traits<graph>
    {
        using pointer_t = Agraph_t*;
    };

    struct graph::impl_t
    //: public object::impl_t
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
}

#endif // !defined(GV_GRAPH_IMPL_H)
