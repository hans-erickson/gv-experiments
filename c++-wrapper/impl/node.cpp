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

namespace gv
{
    node::node(const factory_t& f)
        : object(f)
    {
    }

    node::~node() = default;

    bool
    node::operator==(const node& other) const
    {
        return (impl_accessor_t(*this) == impl_accessor_t(other));
    }

    std::vector<edge>
    node::in_edges() const
    {
        std::vector<edge> result;

        auto this_node = impl_accessor_t(*this);
        auto g = agraphof(this_node);

        for (auto e = agfstin(g, this_node); e != nullptr; e = agnxtin(g, e))
        {
            result.push_back(factory_t{e});
        }

        return result;
    }
        
    std::vector<edge>
    node::out_edges() const
    {
        std::vector<edge> result;

        auto this_node = impl_accessor_t(*this);
        auto g = agraphof(this_node);
        
        for (auto e = agfstout(g, this_node); e != nullptr; e = agnxtout(g, e))
        {
            result.push_back(factory_t{e});
        }

        return result;
    }

    edge
    node::join(node& other, const char* name)
    {
        tmp_string s(name);

        auto this_node = impl_accessor_t(*this);
        auto other_node = impl_accessor_t(other);
        auto g = agraphof(this_node);
        return edge(factory_t{agedge(g, this_node, other_node, s.str(), true)});
    }
}
