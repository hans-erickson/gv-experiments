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

#include "impl.h"


#include <cgraph.h>

#include <stdexcept>

// Assumptions:
//   objects are created by graphs
//   edges are created by objects
//   a pointer to an object is stored in the implementation
//   the implementation is derived from Agrec_t and created
//     by agbindrec(), which will be associated with the Agobject_t
//   objects are removed by graphs
//   edges are removed by objects
//   facade container classes are provided for object/edge iteration
//
// object order of creation:
//   1. Agobject_t is created first (by graph)
//   2. object is created (by graph)
//   3. impl_t for object is created by object using agbindrec()
//      The impl_t contains a pointer back to the object
//   4. callbacks are registered for the object that will be called
//      when edges are added or removed, or when the object itself
//      is destroyed
// object order of creation (2nd possiblity):
//   1. object is created by graph (e.g. node)
//   2. Agobject_t is created by object (e.g. Agnode_t is created by node).
//      This requires object to know about Agraph_t.
//   3. object creates impl_t that is derived from Agrec_t. The creation
//      and binding to Agobject_t has to happen at the same time,
//      which complicates things a little
//   4. ...?
//
// object creation (3rd possibility)
//   1. object (e.g. node) is created with passed-in graph
//   2. object (node) gets Agraph_t somehow from graph.
//   3. Agobject_t (Agnode_t) is created by object (node)
//   4. object (node) binds itself to Agobject_t (Agnode_t) by pointer
// when graph needs nodes pointers, it gets pointers to Agnode_t types
//   and gets the bound copy
// object destruction
//   1. object (node) is deleted by going out of scope
//   2. destructor for object (node) is called
//   3. destructor unbinds itself from Agobject_t
//   4. destructor deletes Agobject_t
//
// Q: what if object isn't bound? What if every object (node)
//    is a copy that refers to the underlying object but there
//    isn't a single pointer to every node? In other words,
//    there may be several copy-able node objects that are
//    thin wrappers around the actual nodes? This probably
//    makes more sense and is less fragile, since a graph
//    isn't created only by adding nodes explicitly but can
//    be parsed as well.
//




namespace gv
{
        /*
        CGRAPH_API Agraph_t *agraphof(void* obj);
        CGRAPH_API Agraph_t *agroot(void* obj);
        CGRAPH_API int agcontains(Agraph_t *, void *);
        CGRAPH_API char *agnameof(void *);
        CGRAPH_API int agrelabel(void *obj, char *name);    // scary
        CGRAPH_API int agrelabel_node(Agnode_t * n, char *newname);
        CGRAPH_API int agdelete(Agraph_t * g, void *obj);
        CGRAPH_API long agdelsubg(Agraph_t * g, Agraph_t * sub);    // could be agclose
        CGRAPH_API int agdelnode(Agraph_t * g, Agnode_t * arg_n);
        CGRAPH_API int agdeledge(Agraph_t * g, Agedge_t * arg_e);
        CGRAPH_API int agobjkind(void *);
        */

        /*
;        CGRAPH_API Agobject_t *agfstobject(Agraph_t * g);
        CGRAPH_API Agobject_t *agnxtobject(Agraph_t * g, Agobject_t * n);
        CGRAPH_API Agobject_t *aglstobject(Agraph_t * g);
        CGRAPH_API Agobject_t *agprvobject(Agraph_t * g, Agobject_t * n);
        */

    /*
    struct object::factory_t
    {
        void* obj = nullptr;
    };

    struct object::impl_t : factory_t {};
    */

    graph
    object::graph_of() const
    {
        return graph(factory_t{agraphof(obj_)});
        //return convert_agraph(agraphof(obj_));
    }

    object::kind_t
    object::kind() const
    {
        switch (agobjkind(obj_))
        {
            case AGRAPH:
            {
                return kind_t::graph;
            }
            case AGNODE:
            {
                return kind_t::node;
            }
            case AGOUTEDGE:
            case AGINEDGE:
            {
                // Q: Do we need to distinguish between edge types?
                return kind_t::edge;
            }
        }
        throw std::logic_error("Invalid object kind. (Internal error.)");
    }

    std::string
    object::name() const
    {
        return agnameof(obj_);
    }

    graph
    object::root() const
    {
        //return convert_agraph(agroot(obj_));
    }

    object::object(const factory_t& f)
        : obj_(f.ptr)
    {
    }

    object::~object()
    {
    }

    void*
    object::shared_obj()
    {
        return obj_;
    }

    const void*
    object::shared_obj() const
    {
        return obj_;
    }
}
