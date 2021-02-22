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
#if !defined(GV_NODE_ITERATOR_H)
#define GV_NODE_ITERATOR_H

#include <iterator>
#include <memory>

namespace gv
{
    class node;

    class node_iterator 
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = node;
        using pointer           = node*;  // or also value_type*
        using reference         = node&;  // or also value_type&

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        node_terator& operator++() { m_ptr++; return *this; }  

        // Postfix increment
        node_terator operator++(int) { node_iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const node_iterator& a, const node_iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const node_iterator& a, const node_iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        struct impl_t;
        std::shared_ptr<impl_t> impl_;
    };
}

#endif // GV_NODE_ITERATOR_H
