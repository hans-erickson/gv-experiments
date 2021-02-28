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

#if !defined(GV_OBJECT_H)
#define GV_OBJECT_H

#include <memory>
#include <string>
#include <vector>
#include <utility>

// Assumptions:
//   objects are created by graphs
//   edges are created by objects
//   a pointer to a object is stored in the implementation
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


namespace gv
{
    class graph;

    class object
    {
    public:
        enum class kind_t
        {
            graph,
            node,
            edge
        };

        using id_t = int;

        /*
        CGRAPH_API int agcontains(Agraph_t *, void *);
        CGRAPH_API int agrelabel(void *obj, char *name);    // scary
        CGRAPH_API int agrelabel_node(Agnode_t * n, char *newname);
        CGRAPH_API int agdelete(Agraph_t * g, void *obj);
        CGRAPH_API long agdelsubg(Agraph_t * g, Agraph_t * sub);    // could be agclose
        CGRAPH_API int agdelnode(Agraph_t * g, Agnode_t * arg_n);
        CGRAPH_API int agdeledge(Agraph_t * g, Agedge_t * arg_e);
        */

        /*
;        CGRAPH_API Agobject_t *agfstobject(Agraph_t * g);
        CGRAPH_API Agobject_t *agnxtobject(Agraph_t * g, Agobject_t * n);
        CGRAPH_API Agobject_t *aglstobject(Agraph_t * g);
        CGRAPH_API Agobject_t *agprvobject(Agraph_t * g, Agobject_t * n);
        */

        std::string
        get(const std::string& key) const;
        
        std::vector<std::pair<std::string, std::string>>
        get_attributes() const;

        graph
        graph_of() const;

        kind_t
        kind() const;

        std::string
        name() const;

        graph
        root() const;

        void
        set(const std::string& key, const std::string& value);

    protected:
        struct factory_t;

        object(const factory_t& f);

        ~object();

    private:
        template<typename> friend class impl_accessor_t;
        void* impl_ = nullptr;
    };
}

#endif // GV_OBJECT_H
