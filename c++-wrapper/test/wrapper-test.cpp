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

#include "../graph.h"
#include "../node.h"

#include <gtest/gtest.h>

#include <sstream>

namespace
{
    const char hello_dot[] = "digraph H { \"Hello world!\" }";
}

TEST(WrapperTest, BasicTest)
{
    {
        gv::graph basic("basic", gv::graph::desc_t::directed);
        EXPECT_TRUE(basic.is_directed());
        EXPECT_FALSE(basic.is_strict());
        EXPECT_FALSE(basic.is_simple());
        EXPECT_FALSE(basic.is_undirected());
    }

    {
        gv::graph basic("basic", gv::graph::desc_t::strict_directed);
        EXPECT_TRUE(basic.is_directed());
        EXPECT_TRUE(basic.is_strict());
        EXPECT_FALSE(basic.is_simple());
        EXPECT_FALSE(basic.is_undirected());
    }

    {
        gv::graph basic("basic", gv::graph::desc_t::undirected);
        EXPECT_FALSE(basic.is_directed());
        EXPECT_FALSE(basic.is_strict());
        EXPECT_FALSE(basic.is_simple());
        EXPECT_TRUE(basic.is_undirected());
    }

    {
        gv::graph basic("basic", gv::graph::desc_t::strict_undirected);
        EXPECT_FALSE(basic.is_directed());
        EXPECT_TRUE(basic.is_strict());
        EXPECT_FALSE(basic.is_simple());
        EXPECT_TRUE(basic.is_undirected());
    }

    {
        gv::graph basic("basic", gv::graph::desc_t::directed);
        gv::node& node0 = basic.create_node("node0");
        gv::node* node0_ptr = basic.find_node("node0");
        EXPECT_EQ(&node0, node0_ptr);
        std::string name = node0.name();
        EXPECT_EQ(name, "node0");
        gv::node* null_node = basic.find_node("non-existent");
        EXPECT_EQ(null_node, nullptr);
        auto nodes = basic.nodes();
        EXPECT_EQ(nodes.size(), 1);
        EXPECT_EQ(nodes[0].get().name(), "node0");
    }
}

TEST(WrapperTest, HelloTest)
{
    {
        gv::graph hello(hello_dot);
        EXPECT_TRUE(hello.is_directed());
        EXPECT_FALSE(hello.is_strict());
        EXPECT_FALSE(hello.is_simple());
        EXPECT_FALSE(hello.is_undirected());
        auto nodes = hello.nodes();
        EXPECT_EQ(nodes.size(), 1);
        EXPECT_EQ(nodes[0].get().name(), "Hello world!");
    }

    {
        std::stringstream ss(hello_dot);
        gv::graph hello(ss);
        EXPECT_TRUE(hello.is_directed());
        EXPECT_FALSE(hello.is_strict());
        EXPECT_FALSE(hello.is_simple());
        EXPECT_FALSE(hello.is_undirected());
        auto nodes = hello.nodes();
        EXPECT_EQ(nodes.size(), 1);
        EXPECT_EQ(nodes[0].get().name(), "Hello world!");
    }
}
