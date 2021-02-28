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

#if !defined(GV_GRAPH_H)
#define GV_GRAPH_H

#include "object.h"

#include <functional>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>

namespace gv
{
    class edge;
    class node;

    class graph final
        : public object
    {
    public:
        enum class desc_t
        {
            directed,
            strict_directed,
            undirected,
            strict_undirected
        };

        graph(const factory_t& f);

        graph(const char* name, desc_t desc);

        graph(const std::istream& in);

        ~graph();

        node
        create_node(const char* name = nullptr);

        node
        create_node(id_t id);

        std::vector<std::reference_wrapper<edge>>
        edges() const;

        std::optional<node>
        find_node(const char* name);

        std::optional<node>
        find_node(id_t id);

        /*
        CGRAPH_API Agnode_t *agfstnode(Agraph_t * g);
        CGRAPH_API Agnode_t *agnxtnode(Agraph_t * g, Agnode_t * n);
        */

        bool
        is_directed() const;

        bool
        is_simple() const;

        bool
        is_strict() const;
        
        bool
        is_undirected() const;

        std::vector<node>
        nodes() const;

        void
        write(std::ostream& out);

    private:
        struct impl_t;
    };
}

#endif // GV_GRAPH_H
