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

#include "../context.h"

#include "impl.h"

#include <gvc.h>

#include <functional>

namespace
{
    struct factory_helper_t
        : public gv::object
    {
        static object::factory_t
        nextInputGraph(GVC_t* gvc)
        {
            return object::factory_t { gvNextInputGraph(gvc) };
        }

        static object::factory_t
        pluginsGraph(GVC_t* gvc)
        {
            return object::factory_t { gvPluginsGraph(gvc) };
        }
    };
}

namespace gv
{
    context::context()
        : impl_(std::make_unique<impl_t>())
    {
    }

    context::context(int argc, char* argv[])
        : impl_(std::make_unique<impl_t>())
    {
        gvParseArgs(impl_->gvc, argc, argv);
    }

    context::~context() = default;

    std::string
    context::buildDate() const
    {
        return gvcBuildDate(impl_->gvc);
    }

    std::vector<std::string>
    context::info() const
    {
        std::vector<std::string> result(3);
        char** info = gvcInfo(impl_->gvc);
        for (std::size_t i = 0; i < result.size(); ++i)
        {
            result[i] = info[i];
        }
        return result;
    }

    graph
    context::nextInputGraph()
    {
        return factory_helper_t::nextInputGraph(impl_->gvc);
    }

    graph
    context::pluginsGraph()
    {
        return factory_helper_t::pluginsGraph(impl_->gvc);
    }

    std::string
    context::version() const
    {
        return gvcVersion(impl_->gvc);
    }
}

