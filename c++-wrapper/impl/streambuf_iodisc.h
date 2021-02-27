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

#if !defined(GV_STREAMBUF_IODISC_H)
#define GV_STREAMBUF_IODISC_H

#include <cgraph.h>

#include <cstring>
#include <iostream>

namespace gv
{
    class streambuf_iodisc_t final
        : public Agiodisc_t
    {
    public:
        streambuf_iodisc_t()
            : Agiodisc_t { &afread, &putstr, &flush }

        {
        }

    private:
        static int
        afread(void* chan,
               char* buf,
               int bufsize)
        {
            return sb(chan).sgetn(buf, bufsize);
        }

        static int
        flush(void* chan)
        {
            return sb(chan).pubsync();
        }

        static int
        putstr(void* chan,
               const char* str)
        {
            return sb(chan).sputn(str, std::strlen(str));
        }

        static std::streambuf&
        sb(void* chan)
        {
            return *reinterpret_cast<std::streambuf*>(chan);
        }
    };
}

#endif // GV_STREAMBUF_IODISC_H
