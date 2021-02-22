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

#include <functional>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <vector>

namespace gv
{
    class node;

    class graph final
    {
    public:
        enum class desc_t
        {
            directed,
            strict_directed,
            undirected,
            strict_undirected
        };

        using id_t = int;

        graph(const char* name, desc_t desc);

        graph(std::istream& in);

        graph(const std::string& str);

        ~graph();

        node&
        create_node(const char* name = nullptr);

        node&
        create_node(id_t id);

        node*
        find_node(const char* name);

        node*
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

        std::vector<std::reference_wrapper<node>>
        nodes() const;

    private:
        struct impl_t;
        std::unique_ptr<impl_t> impl_;
    };
}

#endif // GV_GRAPH_H
