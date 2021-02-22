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

#if !defined(GV_LAYOUT_H)
#define GV_LAYOUT_H

#include <memory>

namespace gv
{
    class layout final
    {
    public:
        struct factory_arg_t;

        layout(const factory_arg_t& args);

        ~layout();

        int
        render();

        int
        render(const char* format, FILE* out);

        int
        render(const char* format, const char* filename);

        int
        render(const char* format, char** result, unsigned int* length);
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
        
    private:
        struct impl_t;
        std::unique_ptr<impl_t> impl_;
    };
}

#endif // GV_LAYOUT_H
