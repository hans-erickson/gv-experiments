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

#include "impl_old.h"

#include <functional>

namespace gv
{
    struct context::impl_t
    {
        impl_t()
            : gvc(std::shared_ptr<GVC_t>(gvContext(), gvFreeContext))
        {
        }

        impl_t(int argc, char* argv[])
            : impl_t()
        {
            gvParseArgs(gvc.get(), argc, argv);
        }
        
        ~impl_t()
        {
        }

        std::string
        buildDate() const
        {
            return gvcBuildDate(gvc.get());
        }

        std::vector<std::string>
        info() const
        {
            std::vector<std::string> result(3);
            char** info = gvcInfo(gvc.get());
            for (std::size_t i = 0; i < result.size(); ++i)
            {
                result[i] = info[i];
            }
            return result;
        }

        std::unique_ptr<graph>
        nextInputGraph()
        {
            /*
            std::shared_ptr<graph_t> g(gvNextInputGraph(gvc.get()),
                                       [](graph_t*){});
            return std::make_unique<graph>(graph::factory_arg_t(gvc, g));
            */
            throw "TODO:";
        }

        std::unique_ptr<graph>
        pluginsGraph()
        {
            /*
            std::shared_ptr<graph_t> g(gvPluginsGraph(gvc.get()),
                                       [](graph_t*){});
            return std::make_unique<graph>(graph::factory_arg_t(gvc, g));
            */
            throw "TODO:";
        }

        std::string
        version() const
        {
            return gvcVersion(gvc.get());
        }

        std::shared_ptr<GVC_t> gvc;
    };

    context::context()
        : impl_(std::make_unique<impl_t>())
    {
    }

    context::context(int argc, char* argv[])
        : impl_(std::make_unique<impl_t>(argc, argv))
    {
    }

    context::~context() = default;

    std::string
    context::buildDate() const
    {
        return impl_->buildDate();
    }

    std::vector<std::string>
    context::info() const
    {
        return impl_->info();
    }

    std::unique_ptr<graph>
    context::nextInputGraph()
    {
        return impl_->nextInputGraph();
    }

    std::unique_ptr<graph>
    context::pluginsGraph()
    {
        return impl_->pluginsGraph();
    }

    std::string
    context::version() const
    {
        return impl_->version();
    }
}

