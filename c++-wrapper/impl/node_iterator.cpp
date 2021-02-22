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

#include "../node_iterator.h"

#include "../node.h"

namespace gv
{
    struct node_iterator::impl_t
    {
        node* ptr = nullptr;
    };

    node_iterator::reference
    node_iterator::operator*() const
    {
        return *m_ptr;
    }

    node_iterator::pointer
    node_iterator::operator->()
    {
        return m_ptr;
    }

    // Prefix increment
    node_terator&
    node_iterator::operator++()
    {
        m_ptr++;
        return *this;
    }

    // Postfix increment
    node_terator
    node_iterator::operator++(int)
    {
        node_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool
    operator==(const node_iterator& a, const node_iterator& b)
    {
        return a.m_ptr == b.m_ptr;
    }

    bool
    operator!=(const node_iterator& a, const node_iterator& b)
    {
        return a.m_ptr != b.m_ptr;
    }
}

#endif // GV_NODE_ITERATOR_H
