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

#if !defined(GV_EDGE_H)
#define GV_EDGE_H

#include "object.h"

namespace gv
{
    class edge final
        : public object
    {
    public:
        edge(const factory_t& f);
        /*
;        CGRAPH_API Agedge_t *agfstedge(Agraph_t * g);
        CGRAPH_API Agedge_t *agnxtedge(Agraph_t * g, Agedge_t * n);
        CGRAPH_API Agedge_t *aglstedge(Agraph_t * g);
        CGRAPH_API Agedge_t *agprvedge(Agraph_t * g, Agedge_t * n);
        */

        ~edge();
    };
}

#endif // GV_EDGE_H
