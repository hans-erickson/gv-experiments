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

#include "object_impl.h"

#include "tmp_string.h"

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


#include "object_impl.h"

#include "graph_impl.h"

namespace gv
{
    template<>
    struct object::forward_iterator<object::attribute>::impl_t
    {
        impl_t(const constructor_arg_t& iter_arg)
            : iter_arg_(iter_arg),
              sym_(nullptr)
        {
            next();
        }

        void next()
        {
            sym_  = ::agnxtattr(iter_arg_.graph, iter_arg_.kind, sym_);
            attr_ = attribute(sym_);
        }

        constructor_arg_t iter_arg_;
        Agsym_t* sym_ { };
        attribute attr_;
    };


    // Rule of five members
    template<>
    object::forward_iterator<object::attribute>::forward_iterator(const forward_iterator& other)
        : impl_(std::make_unique<impl_t>(*other.impl_))
    {}

    template<>
    object::forward_iterator<object::attribute>::forward_iterator(forward_iterator&& other)
        : impl_(std::move(impl_))
    {}

    template<>
    object::forward_iterator<object::attribute>::~forward_iterator() = default;

    template<>
    object::forward_iterator<object::attribute>&
    object::forward_iterator<object::attribute>::operator=(const forward_iterator& other)
    {
        impl_ = std::make_unique<impl_t>(*other.impl_);
        return *this;
    }

    template<>
    object::forward_iterator<object::attribute>&
    object::forward_iterator<object::attribute>::operator=(forward_iterator&& other)
    {
        impl_ = std::move(other.impl_);
        return *this;
    }

    
    template<>
    object::forward_iterator<object::attribute>::forward_iterator(const constructor_arg_t& arg)
        : impl_(std::make_unique<impl_t>(arg))
    {
    }

    template<>
    object::forward_iterator<object::attribute>&
    object::forward_iterator<object::attribute>::operator++()
    {
        impl_->next();
        return *this;
    }

    template<>
    object::forward_iterator<object::attribute>
    object::forward_iterator<object::attribute>::operator++(int)
    {
        forward_iterator tmp(*this);
        operator++();
        return tmp;
    }
    
    template<>
    object::attribute&
    object::forward_iterator<object::attribute>::operator*()
    {
        return impl_->attr_;
    }

    template<>
    object::attribute&
    object::forward_iterator<object::attribute>::operator*() const
    {
        return impl_->attr_;
    }

    template<>
    bool
    object::forward_iterator<object::attribute>::operator==(const forward_iterator& other) const
    {
        return impl_->sym_ == other.impl_->sym_;
    }

    template<>
    bool
    object::forward_iterator<object::attribute>::operator==(std::default_sentinel_t) const
    {
        return impl_->sym_ == nullptr;
    }


    object::attribute::attribute(const constructor_arg_t& arg)
        : ptr_ { arg.ptr_.get() }
    {
    }

    std::string
    object::attribute::name()
    {
        return reinterpret_cast<Agsym_t*>(ptr_)->name;
    }

    std::string
    object::attribute::value()
    {
        return reinterpret_cast<Agsym_t*>(ptr_)->defval;
    }

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


    std::string
    object::get(const std::string& key) const
    {
        tmp_string s(key);
        auto result = ::agget(get_native_ptr(this), s.str());
        return (result? result: "");
    }

    graph
    object::graph_of() const
    {
        return graph { constructor_arg_t { ::agraphof(get_native_ptr(this)) } };
    }

    object::kind_t
    object::kind() const
    {
        switch (::agobjkind(get_native_ptr(this)))
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

    object::attribute_view
    object::get_attributes() const
    {
        forward_iterator<object::attribute>::constructor_arg_t arg {
            .kind  = ::agobjkind(get_native_ptr(this)),
            .graph = ::agraphof(get_native_ptr(this))
        };

        return attribute_view { attribute_iterator{arg} };
    }
    
    std::string
    object::name() const
    {
        const char* s = ::agnameof(get_native_ptr(this));
        return (s? s: "");
    }

    graph
    object::root() const
    {
        return graph { constructor_arg_t { ::agroot(get_native_ptr(this)) } };
    }

    void
    object::set(const std::string& key, const std::string& value)
    {
        tmp_string key_s(key);
        tmp_string value_s(value);
        tmp_string default_s("");

        // TODO: Return value?
        ::agsafeset(get_native_ptr(this), key_s.str(), value_s.str(), default_s.str());
    }

    object::object(const constructor_arg_t& arg)
        : impl_{arg.ptr_}
    {
    }

    object::~object()
    {
    }
}
