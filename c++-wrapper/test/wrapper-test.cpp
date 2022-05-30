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

TEST(GraphTest, Directed)
{
    gv::graph basic("basic", gv::graph::desc_t::directed);
    EXPECT_TRUE(basic.is_directed());
    EXPECT_FALSE(basic.is_strict());
    EXPECT_FALSE(basic.is_simple());
    EXPECT_FALSE(basic.is_undirected());
}

TEST(GraphTest, StrictDirected)
{
    gv::graph basic("basic", gv::graph::desc_t::strict_directed);
    EXPECT_TRUE(basic.is_directed());
    EXPECT_TRUE(basic.is_strict());
    EXPECT_FALSE(basic.is_simple());
    EXPECT_FALSE(basic.is_undirected());
}

TEST(GraphTest, Undirected)
{
    gv::graph basic("basic", gv::graph::desc_t::undirected);
    EXPECT_FALSE(basic.is_directed());
    EXPECT_FALSE(basic.is_strict());
    EXPECT_FALSE(basic.is_simple());
    EXPECT_TRUE(basic.is_undirected());
}

TEST(GraphTest, StrictUndirected)
{
    gv::graph basic("basic", gv::graph::desc_t::strict_undirected);
    EXPECT_FALSE(basic.is_directed());
    EXPECT_TRUE(basic.is_strict());
    EXPECT_FALSE(basic.is_simple());
    EXPECT_TRUE(basic.is_undirected());
}

TEST(GraphTest, ObjectProperties)
{
    gv::graph basic("basic", gv::graph::desc_t::directed);

    EXPECT_EQ(basic.name(), "basic");
    EXPECT_EQ(basic.kind(), gv::object::kind_t::graph);
    EXPECT_EQ(basic.graph_of(), basic);
    EXPECT_EQ(basic.root(), basic);

    auto attributes = basic.get_attributes();
    EXPECT_EQ(attributes.begin(), attributes.end());
}

TEST(GraphTest, AttributesBasic)
{
    gv::graph basic("basic", gv::graph::desc_t::directed);

    basic.set("key0", "value0");
    EXPECT_EQ(basic.get("key0"), "value0");

    basic.set("key1", "value1");
    EXPECT_EQ(basic.get("key1"), "value1");

    basic.set("key0", "value0.1");
    EXPECT_EQ(basic.get("key0"), "value0.1");

    EXPECT_EQ(basic.get("invalid"), "");
}

TEST(GraphTest, AttributesIterator)
{
    gv::graph basic("basic", gv::graph::desc_t::directed);

    auto attributes = basic.get_attributes();
    EXPECT_EQ(attributes.begin(), attributes.end());


    basic.set("key0", "value0.0");
    attributes = basic.get_attributes();
    auto iter = attributes.begin();
    EXPECT_EQ((*iter).name(), "key0");
    EXPECT_EQ((*iter).value(), "value0.0");
    ++iter;
    EXPECT_EQ(iter, attributes.end());

    EXPECT_EQ(basic.get("key0"), "value0.0");
    basic.set("key0", "value0.1");
    EXPECT_EQ(basic.get("key0"), "value0.1");

    iter = attributes.begin();
    EXPECT_EQ((*iter).name(), "key0");
    EXPECT_EQ((*iter).value(), "value0.1");

    basic.set("key0", "value0.2");
    EXPECT_EQ((*iter).value(), "value0.2");

    basic.set("key1", "value1.0");
    EXPECT_EQ(basic.get("key1"), "value1.0");
    ++iter;
    EXPECT_EQ((*iter).value(), "value1.0");
}

TEST(GraphTest, CreateNode)
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
    EXPECT_EQ((*nodes.begin()).name(), "node0");
}

TEST(HelloWorldTest, HelloTest)
{
    gv::graph hello{std::stringstream(hello_dot)};
    EXPECT_TRUE(hello.is_directed());
    EXPECT_FALSE(hello.is_strict());
    EXPECT_FALSE(hello.is_simple());
    EXPECT_FALSE(hello.is_undirected());
    auto nodes = hello.nodes();
    EXPECT_EQ((*nodes.begin()).name(), "Hello world!");
}

TEST(HelloWorldTest, HelloGoodbyeTest)
{
    gv::graph hibye{std::stringstream(hello_goodbye_dot)};
    EXPECT_TRUE(hibye.is_directed());
    EXPECT_FALSE(hibye.is_strict());
    EXPECT_FALSE(hibye.is_simple());
    EXPECT_FALSE(hibye.is_undirected());

    auto nodes = hibye.nodes();
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

TEST(WrapperTest, HelloGoodbyeTest)
{
    gv::graph hibye{std::stringstream(hello_goodbye_dot)};
    auto nodes = hibye.nodes();
    auto iter = nodes.begin();
    EXPECT_EQ((*iter).name(), "Hello world!");
    ++iter;
    EXPECT_EQ((*iter).name(), "Goodbye!");
    ++iter;
    EXPECT_EQ(iter, nodes.end());
    --iter;
    EXPECT_EQ((*iter).name(), "Goodbye!");
    --iter;
    EXPECT_EQ((*iter).name(), "Hello world!");
    EXPECT_EQ((*iter++).name(), "Hello world!");
    EXPECT_EQ((*iter).name(), "Goodbye!");

    auto tmp0(iter);
    EXPECT_EQ((*tmp0).name(), "Goodbye!");
    --iter;
    EXPECT_EQ((*tmp0).name(), "Goodbye!");
    //EXPECT_EQ((*iter--).name(), "Goodbye!");
    //EXPECT_EQ((*iter).name(), "Hello world!");            
    /*auto tmp0 = iter;
      ++iter;
      EXPECT_EQ((*tmp0).name(), "Hello world!");
      EXPECT_EQ((*iter).name(), "Goodbye!");
    */
    //auto tmp1 = iter--;
    //EXPECT_EQ((*tmp1).name(), "Goodbye!");
    //EXPECT_EQ((*iter).name(), "Hello world!");
}
/*
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
*/
//}

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
