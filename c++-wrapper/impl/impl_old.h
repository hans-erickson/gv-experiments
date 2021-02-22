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

#if !defined(GV_IMPL_OLD_H)
#define GV_IMPL_OLD_H

#include "../context.h"
#include "../graph.h"
#include "../layout.h"

#include <gvc.h>

namespace gv
{
    struct factory_arg_t
    {
        factory_arg_t(std::shared_ptr<GVC_t> gvc_,
                      std::shared_ptr<graph_t> g_)
            : gvc(gvc_),
              g(g_)
        {
        }

        std::shared_ptr<GVC_t> gvc;
        std::shared_ptr<graph_t> g;
    };

    /*
    struct graph::factory_arg_t
        : gv::factory_arg_t
    {
        using gv::factory_arg_t::factory_arg_t;
    };
    */

    struct layout::factory_arg_t
        : gv::factory_arg_t
    {
        factory_arg_t(std::shared_ptr<GVC_t> gvc_,
                      std::shared_ptr<graph_t> g_,
                      const char* engine_)
            : gv::factory_arg_t(gvc_, g_)
        {
        }

        const char* engine = nullptr;
    };
}

#endif // GV_IMPL_OLD_H
