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

#if !defined(GV_NODE_IMPL_H)
#define GV_NODE_IMPL_H

#include "../node.h"

#include <cgraph.h>

namespace gv
{
    template<>
    struct object::native_pointer_traits<node>
    {
        using pointer_type = Agnode_t*;
    };

    template<>
    struct object::bidirectional_iterator<node>::constructor_arg_t
    {
        using FirstFunc = Agnode_t* (*)(Agraph_t*);
        using NextFunc  = Agnode_t* (*)(Agraph_t*, Agnode_t*);
        using LastFunc  = Agnode_t* (*)(Agraph_t*);
        using PrevFunc  = Agnode_t* (*)(Agraph_t*, Agnode_t*);

        FirstFunc first_func_ptr   {};
        NextFunc  next_func_ptr    {};
        LastFunc  last_func_ptr    {};
        PrevFunc  prev_func_ptr    {};
        Agraph_t* native_graph_ptr {};

        Agnode_t* first()
        {
            return first_func_ptr(native_graph_ptr);
        }

        Agnode_t* next(Agnode_t* node_ptr)
        {
            return next_func_ptr(native_graph_ptr, node_ptr);
        }

        Agnode_t* last()
        {
            return last_func_ptr(native_graph_ptr);
        }

        Agnode_t* prev(Agnode_t* node_ptr)
        {
            return prev_func_ptr(native_graph_ptr, node_ptr);
        }
    };
}

#endif // !defined(GV_NODE_IMPL_H)
