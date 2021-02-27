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

#if !defined(GV_IMPL_H)
#define GV_IMPL_H

#include "../context.h"
#include "../edge.h"
#include "../graph.h"
#include "../layout.h"
#include "../node.h"
#include "../object.h"

#include <cgraph.h>

#include <functional>
#include <iostream> // TODO: Remove
#include <string>

namespace
{
    template<typename T>
    class record
    {
    public:
        record(T& t, void* g)
        {
            auto str = object_name(agobjkind(g));
            auto obj = reinterpret_cast<impl_t*>(agbindrec(g, str.data(),
                                                           sizeof(impl_t), FALSE));
            impl_ = std::unique_ptr<impl_t>(obj);
            impl_->obj = &t;
            impl_->g = g;
            /*
            impl_ = std::unique_ptr<impl_t, deleter_t>(obj, deleter);

            impl_->obj = &t;
            */
        }

        ~record()
        {
            auto str = object_name(agobjkind(impl_->g));
            agdelrec(impl_->g, str.data());
            std::cout << "destructor" << std::endl;
        }

    private:
        static void
        deleter(void* g)
        {
            auto str = object_name(agobjkind(g));
            agdelrec(g, str.data());
            std::cout << "deleter()" << std::endl;
        }

        static std::string
        object_name(int type)
        {
            using namespace std::string_literals;

            switch (type)
            {
                case AGRAPH:
                {
                    return "gv::graph\0"s;
                }
                case AGNODE:
                {
                    return "gv::node\0"s;
                }
                case AGOUTEDGE:
                case AGINEDGE:
                {
                    return "gv::edge\0"s;
                }
            }
            return "unknown\0"s;
        }

        struct impl_t
        {
            Agrec_t rec;
            T* obj = nullptr;
            void* g = nullptr;
        };

        //using deleter_t = std::function<void(void*)>;
        std::unique_ptr<impl_t> impl_;
    };

    

        /*
        static void*
        operator new(std::size_t sz, void* obj)
        {
            std::cout << "operator new" << std::endl;
            auto s = object_name(agobjkind(obj));
            return agbindrec(obj, s.data(), sz, FALSE);
        }

        static void
        operator delete(void* obj)
        {
            std::cout << "operator delete" << std::endl;
            auto s = object_name(agobjkind(obj));
            agdelrec(obj, s.data());
        }
        */


        /*
        record*
        create(void* object)
        {
            Agnode_t* n = agnode(g,"mynodename",TRUE);
            record* data = (record*)agbindrec(n,"mynode_t",sizeof(mynode_t),FALSE);
            data->count = 1;

        }
        */

        /*
        static void* operator new(std::size_t sz)
        {
            mynode_t*data;
            Agnode_t*n;
            n = agnode(g,"mynodename",TRUE);
            record* data = (record*)agbindrec(n,"mynode_t",sizeof(mynode_t),FALSE);
            data->count = 1;


            std::cout << "custom new for size " << sz << '\n';
            return ::operator new(sz);
        }
        */
        //static void operator delete(void* ptr);
        

    /*
    struct bogus_wrapper
    {
        Agrec_t record;
        gv::graph* g = nullptr;
    };
    */
    
    // TODO: Move this somewhere.
    /*
    inline gv::graph&
    convert_agraph(Agraph_t* g)
    {
        using namespace std::string_literals;

        auto str = "cv::graph\0"s;
        auto gwrapper = reinterpret_cast<bogus_wrapper*>(aggetrec(g, str.data(), FALSE));
        if (gwrapper != nullptr && gwrapper->g != nullptr)
        {
            return *gwrapper->g;
        }
        // TODO: Get gv::graph from rec
    }
    */
}

namespace
{
    class tmp_string
    {
    public:
        tmp_string(const std::string& s)
            : s_(s)
        {
            s_.push_back('\0');
        }

        char*
        str()
        {
            return s_.data();
        }

        operator char*()
        {
            return s_.data();
        }

    private:
        std::string s_;
    };
}

namespace gv
{
    struct object::factory_t
    {
        void* ptr = nullptr;
    };
    /*
    struct node::factory_t
    {
        Agnode_t* ptr = nullptr;
    };

    struct edge::factory_t
    {
        Agedge_t* ptr = nullptr;
    };
    */

    struct common_impl_t
    {
        Agraph_t* agraph = nullptr;
        /*get_agraph_ptr(graph& g)
        {
            // TODO: Do some magic here
            return nullptr;
        }
        */
    };
}

#endif // GV_IMPL_H
