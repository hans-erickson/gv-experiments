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

#if !defined(GV_NODE_H)
#define GV_NODE_H

#include "object.h"

#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

// Assumptions:
//   nodes are created by graphs
//   edges are created by nodes
//   a pointer to a node is stored in the implementation
//   the implementation is derived from Agrec_t and created
//     by agbindrec(), which will be associated with the Agnode_t
//   nodes are removed by graphs
//   edges are removed by nodes
//   facade container classes are provided for node/edge iteration
//
// node order of creation:
//   1. Agnode_t is created first (by graph)
//   2. node is created (by graph)
//   3. impl_t for node is created by node using agbindrec()
//      The impl_t contains a pointer back to the node
//   4. callbacks are registered for the node that will be called
//      when edges are added or removed, or when the node itself
//      is destroyed


namespace gv
{
    class edge;

    class node final
        : public object
    {
    public:
        using edge_iterator = forward_iterator<edge>;
        using edge_view     = view<edge_iterator>;

        node(const constructor_arg_t& arg);
        
        ~node();

        bool
        operator==(const node& other) const;

        edge_view
        in_edges() const;

        edge
        join(node& other, const char* name = nullptr);

        edge_view
        out_edges() const;
    };
}

#endif // GV_NODE_H
