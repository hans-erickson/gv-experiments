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
    class graph;
    class node;

    class edge final
        : public object
    {
    public:
        //struct constructor_arg_t;
    /*
      Agedge_t *agedge(Agraph_t* g, Agnode_t *t, Agnode_t *h, char *name, int createflag);
      Agedge_t *agidedge(Agraph_t * g, Agnode_t * t, Agnode_t * h, unsigned long id, int createflag);
      Agedge_t *agsubedge(Agraph_t *g, Agedge_t *e, int createflag);
      Agnode_t *aghead(Agedge_t *e), *agtail(Agedge_t *e);

      // Create an edge iterator for these
      Agedge_t *agfstedge(Agraph_t* g, Agnode_t *n);
      Agedge_t *agnxtedge(Agraph_t* g, Agedge_t *e, Agnode_t *n);
      Agedge_t *agfstin(Agraph_t* g, Agnode_t *n);
      Agedge_t *agnxtin(Agraph_t* g, Agedge_t *e);
      Agedge_t *agfstout(Agraph_t* g, Agnode_t *n);
      Agedge_t *agnxtout(Agraph_t* g, Agedge_t *e);

      int      agdeledge(Agraph_t *g, Agedge_t *e);
    */


        
        edge(const constructor_arg_t& arg);


        /*
;        CGRAPH_API Agedge_t *agfstedge(Agraph_t * g);
        CGRAPH_API Agedge_t *agnxtedge(Agraph_t * g, Agedge_t * n);
        CGRAPH_API Agedge_t *aglstedge(Agraph_t * g);
        CGRAPH_API Agedge_t *agprvedge(Agraph_t * g, Agedge_t * n);
        */

        ~edge();

        node
        head();

        node
        tail();
    };
}

#endif // GV_EDGE_H
