//
//  MIT License
//  
//  Copyright (c) 2022 Hans Erickson
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

#if !defined(GV_EDGE_IMPL_H)
#define GV_EDGE_IMPL_H

#include "../edge.h"

#include "impl_accessor.h"
//#include "streambuf_iodisc.h"
//#include "tmp_string.h"

#include <cgraph.h>

namespace gv
{
    template<>
    struct impl_traits<edge>
    {
        using pointer_t = Agedge_t*;
    };

    template<>
    struct object::forward_iterator<edge>::constructor_arg_t
    {
        using FirstFunc = Agedge_t* (*)(Agraph_t*, Agnode_t*);
        using NextFunc  = Agedge_t* (*)(Agraph_t*, Agedge_t*);

        FirstFunc first_func_ptr   {};
        NextFunc  next_func_ptr    {};
        Agraph_t* native_graph_ptr {};
        Agnode_t* native_node_ptr  {};
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
    template<>
    struct object::native_handle<edge>
    {
        using pointer_t = impl_traits<edge>::pointer_t;
        pointer_t ptr {};
    };
    */


    /*struct edge::impl_t
    {
    };*/
}

#endif // !defined(GV_EDGE_IMPL_H)
