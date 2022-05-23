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

#include "../layout.h"

#include <gvc.h>

#include <ostream>

namespace gv
{
    struct layout::impl_t
    {
        impl_t(const context& ctx, const graph& gobj)
        {
            //            gvc = ctx.impl_->gvc;
            //gvc = impl_accessor_t(ctx);
            //g = impl_accessor_t(gobj);
        }

        /*
        impl_t(std::shared_ptr<GVC_t> gvc_,
               std::shared_ptr<graph_t> g_,
               const char* engine_)
            : gvc(gvc_),
              g(g_),
              engine(engine_)
        {
            if (engine == nullptr)
            {
                gvLayoutJobs(gvc.get(), g.get());
            }
            else
            {
                gvLayout(gvc.get(), g.get(), engine);
            }
        }

        ~impl_t()
        {
            gvFreeLayout(gvc.get(), g.get());
        }

        int
        render()
        {
            return gvRenderJobs(gvc.get(), g.get());
        }

        int
        render(const char* format, FILE* out)
        {
            return gvRender(gvc.get(), g.get(), format, out);
        }

        int
        render(const char* format, const char* filename)
        {
            return gvRenderFilename(gvc.get(), g.get(), format, filename);
        }

        int
        render(const char* format, char** result, unsigned int* length)
        {
            return gvRenderData(gvc.get(), g.get(), format, result, length);
        }

        std::shared_ptr<GVC_t> gvc;
        std::shared_ptr<graph_t> g;
        const char* engine = nullptr;
        */
        GVC_t*    gvc {};
        Agraph_t* g   {};
    };

    layout::layout(const context& ctx, const graph& g)
        : impl_(std::make_unique<impl_t>(ctx, g))
    {
    }

    layout::~layout()
    {
    }

    std::string
    layout::render(const std::string& format)
    {
        std::string result;

        char* data = nullptr;
        unsigned length = 0;
        gvRenderData(impl_->gvc, impl_->g, format.c_str(), &data, &length);

        return result;
    }

    /*
    int
    layout::render()
    {
        return impl_->render();
    }
    */

    /*
    int
    layout::render(const char* format, FILE* out)
    {
        return impl_->render(format, out);
    }

    int
    layout::render(const char* format, const char* filename)
    {
        return impl_->render(format, filename);
    }

    int
    layout::render(const char* format, char** result, unsigned int* length)
    {
        return impl_->render(format, result, length);
    }
    */
    
        // Compute a layout using a specified engine
        //int
        //layout(context& ctx, const char *engine);

        /*

        // Compute a layout using layout engine from command line args
        int gvLayoutJobs(GVC_t *gvc, graph_t *g);

        // Render layout into string attributes of the graph
        void attach_attrs(graph_t *g);

        // Render layout in a specified format to an open FILE
        int gvRender(GVC_t *gvc, graph_t *g, const char *format, FILE *out);

        // Render layout in a specified format to a file with the given name
        int gvRenderFilename(GVC_t *gvc, graph_t *g, const char *format, const char *filename);

        // Render layout in a specified format to an external context
        int gvRenderContext(GVC_t *gvc, graph_t *g, const char *format, void *context);

        // Render layout in a specified format to a malloc'ed string
        int gvRenderData(GVC_t *gvc, graph_t *g, const char *format, char **result, unsigned int *length);

        // Free memory allocated and pointed to by *result in gvRenderData
        void gvFreeRenderData (char* data);

        // Render layout according to -T and -o options found by gvParseArgs
        int gvRenderJobs(GVC_t *gvc, graph_t *g);

        // Clean up layout data structures - layouts are not nestable (yet)
        int gvFreeLayout(GVC_t *gvc, graph_t *g);
        */
}
