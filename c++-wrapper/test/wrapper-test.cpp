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

#include "../edge.h"
#include "../graph.h"
#include "../node.h"

#include <gtest/gtest.h>

#include <sstream>

namespace
{
    const char hello_dot[] = "digraph H { \"Hello world!\" }";
    const char hello_goodbye_dot[] = "digraph H { \"Hello world!\" -> \"Goodbye!\" }";
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
        gv::node node0 = basic.create_node("node0");
        std::optional<gv::node> node0_opt = basic.find_node("node0");
        ASSERT_TRUE(node0_opt.has_value());
        EXPECT_EQ(node0, *node0_opt);
        std::string name = node0.name();
        EXPECT_EQ(name, "node0");
        std::optional<gv::node> null_node_opt = basic.find_node("non-existent");
        EXPECT_FALSE(null_node_opt.has_value());
        auto nodes = basic.nodes();
        //EXPECT_EQ(nodes.size(), 1);
        EXPECT_EQ((*nodes.begin()).name(), "node0");
    }
}

TEST(WrapperTest, HelloTest)
{
    {
        gv::graph hello{std::stringstream(hello_dot)};
        EXPECT_TRUE(hello.is_directed());
        EXPECT_FALSE(hello.is_strict());
        EXPECT_FALSE(hello.is_simple());
        EXPECT_FALSE(hello.is_undirected());
        auto nodes = hello.nodes();
        //EXPECT_EQ(nodes.size(), 1);
        EXPECT_EQ((*nodes.begin()).name(), "Hello world!");
    }
}

TEST(WrapperTest, HelloGoodbyeTest)
{
    {
        gv::graph hibye{std::stringstream(hello_goodbye_dot)};
        EXPECT_TRUE(hibye.is_directed());
        EXPECT_FALSE(hibye.is_strict());
        EXPECT_FALSE(hibye.is_simple());
        EXPECT_FALSE(hibye.is_undirected());
        auto nodes = hibye.nodes();
        //EXPECT_EQ(nodes.size(), 2);
        auto iter = nodes.begin();
        EXPECT_EQ((*iter).name(), "Hello world!");
        auto in_edges0 = (*iter).in_edges();
        //EXPECT_EQ(in_edges0.size(), 0);
        auto out_edges0 = (*iter).out_edges();
        //EXPECT_EQ(out_edges0.size(), 1);
        ++iter;
        EXPECT_EQ((*iter).name(), "Goodbye!");
        auto in_edges1 = (*iter).in_edges();
        //EXPECT_EQ(in_edges1.size(), 1);
        auto out_edges1 = (*iter).out_edges();
        //EXPECT_EQ(out_edges1.size(), 0);
    }
}

TEST(WrapperTest, CreateEdgeTest)
{
    {
        gv::graph gr("gr", gv::graph::desc_t::directed);
        gv::node node0 = gr.create_node("node0");
        gv::node node1 = gr.create_node("node1");
        auto in_edges0 = node0.in_edges();
        //EXPECT_EQ(in_edges0.size(), 0);
        auto out_edges0 = node0.out_edges();
        //EXPECT_EQ(out_edges0.size(), 0);
        auto in_edges1 = node1.in_edges();
        //EXPECT_EQ(in_edges1.size(), 0);
        auto out_edges1 = node1.out_edges();
        //EXPECT_EQ(out_edges1.size(), 0);

        gv::edge edge0 = node0.join(node1, "edge0");
        in_edges0 = node0.in_edges();
        //EXPECT_EQ(in_edges0.size(), 0); //
        out_edges0 = node0.out_edges();
        //EXPECT_EQ(out_edges0.size(), 1);
        in_edges1 = node1.in_edges();
        //EXPECT_EQ(in_edges1.size(), 1); //
        out_edges1 = node1.out_edges();
        //EXPECT_EQ(out_edges1.size(), 0);
    }

    {
        // Anonymous nodes/edges
        gv::graph gr("gr", gv::graph::desc_t::directed);
        gv::node node0 = gr.create_node();
        gv::node node1 = gr.create_node();
        gv::edge edge0 = node0.join(node1);
        auto in_edges0 = node0.in_edges();
        //EXPECT_EQ(in_edges0.size(), 0);
        auto out_edges0 = node0.out_edges();
        //EXPECT_EQ(out_edges0.size(), 1);
        auto in_edges1 = node1.in_edges();
        //EXPECT_EQ(in_edges1.size(), 1); //
        auto out_edges1 = node1.out_edges();
        //EXPECT_EQ(out_edges1.size(), 0);
    }
}
