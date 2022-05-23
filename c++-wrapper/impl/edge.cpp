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

#include "edge_impl.h"

#include "object_impl.h"

#include <memory>

namespace gv
{

    class in_edge_iterator_test
    {
    public:
        in_edge_iterator_test(Agraph_t *g, Agnode_t *n)
            : graph_(g),
              edge_(::agfstin(g, n))
        {
        }

        in_edge_iterator_test&
        next()
        {
            edge_ = ::agnxtin(graph_, edge_);
            return *this;
        }

        Agedge_t* operator*()
        {
            return edge_;
        }

    private:
        Agraph_t* graph_ {};
        Agedge_t* edge_ {};
    };
    /*
    CGRAPH_API Agedge_t * 	agfstin (Agraph_t *g, Agnode_t *n)
 
    CGRAPH_API Agedge_t * 	agnxtin (Agraph_t *g, Agedge_t *e)
 
    CGRAPH_API Agedge_t * 	agfstout (Agraph_t *g, Agnode_t *n)
 
    CGRAPH_API Agedge_t * 	agnxtout (Agraph_t *g, Agedge_t *e)
 
    CGRAPH_API Agedge_t * 	agfstedge (Agraph_t *g, Agnode_t *n)
 
    CGRAPH_API Agedge_t * 	agnxtedge (Agraph_t *g, Agedge_t *e, Agnode_t *n)
    */

    /*
    struct edge::constructor_arg_t
        : object::constructor_arg_t
    {
        //native_handle_ptr<edge> ptr;
    };
    */


    
    template<>
    struct object::forward_iterator<edge>::impl_t
    {
        impl_t(const constructor_arg_t& arg)
        //: e_(native_handle(arg.first_func_ptr(arg.native_graph_ptr, arg.native_node_ptr)))
        {
        }

        //edge e_;
    };


    /*template<>
    struct object::forward_iterator<edge>::impl_t
    {
    };*/

    /*template<>
    object::forward_iterator<edge>::forward_iterator()
    {}*/

    /*template<>
    object::forward_iterator<edge>::forward_iterator(native_handle<edge>)
    {}
    */

    /*template<>
    object::forward_iterator<edge>::forward_iterator(const forward_iterator& i)
    {}*/

    template<>
    object::forward_iterator<edge>::forward_iterator(const constructor_arg_t& arg)
        : impl_(std::make_unique<impl_t>(arg))
    {
    }

    template<>
    object::forward_iterator<edge>&
    object::forward_iterator<edge>::operator++()
    {
        return *this;
    }

    template<>
    object::forward_iterator<edge>
    object::forward_iterator<edge>::operator++(int)
    {
        forward_iterator tmp(*this);
        operator++();
        return tmp;
    }
    
    template<>
    edge&
    object::forward_iterator<edge>::operator*()
    {
        throw std::runtime_error("TODO:");
    }

    template<>
    edge&
    object::forward_iterator<edge>::operator*() const
    {
        throw std::runtime_error("TODO:");
        //return (const_cast<forward_iterator*>(this));
    }

    template<>
    bool
    object::forward_iterator<edge>::operator==(const forward_iterator& other) const
    {
        return false;
    }

    //Agedge_t*
    //agedge(Agraph_t* g, Agnode_t *t, Agnode_t *h, char *name, int createflag);

    /*
    edge::edge(const factory_t& f)
        : object(f)
    {
    }
    */
        /*
;        CGRAPH_API Agedge_t *agfstedge(Agraph_t * g);
        CGRAPH_API Agedge_t *agnxtedge(Agraph_t * g, Agedge_t * n);
        CGRAPH_API Agedge_t *aglstedge(Agraph_t * g);
        CGRAPH_API Agedge_t *agprvedge(Agraph_t * g, Agedge_t * n);
        */

    edge::edge(const constructor_arg_t& arg)
        : object(arg)
    {
    }

    edge::~edge() = default;
}
