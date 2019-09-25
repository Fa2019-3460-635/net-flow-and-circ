#include "tree.hpp"
#include "gtest/gtest.h"
#include <sstream>

TEST (TreeTests, CanConstructTree)
{
  Tree tree;
}

TEST (TreeTests, CanAddAndGetString)
{
  Tree tree_one;
  tree_one.add({}, "one");
  EXPECT_EQ("one", tree_one.get({}).second);

  Tree tree_two;
  tree_two.add({}, "two");
  EXPECT_EQ("two", tree_two.get({}).second);
}

TEST (TreeTests, CanAddChildStrings)
{
  Tree tree;
  tree.add({"one"},   "one");
  tree.add({"two"},   "two");
  tree.add({"three"}, "three");
  EXPECT_EQ("one",   tree.get({"one"}).second);
  EXPECT_EQ("two",   tree.get({"two"}).second);
  EXPECT_EQ("three", tree.get({"three"}).second);
}

TEST (TreeTests, CanAddAndGetFromImbalancedTree)
{
  Tree tree;
  tree.add({"one", "a"}, "a");
  tree.add({"one", "b"}, "b");
  tree.add({"one", "c"}, "c");
  tree.add({"two"}, "two");

  EXPECT_EQ("a",   tree.get( {"one", "a"} ).second);
  EXPECT_EQ("b",   tree.get( {"one", "b"} ).second);
  EXPECT_EQ("c",   tree.get( {"one", "c"} ).second);
  EXPECT_EQ("two", tree.get( {"two"}      ).second);
}

TEST (TreeTests, GetReturnsTrueInFirstElementIfKeyIsFound)
{
  Tree tree;
  tree.add({}, "test");
  EXPECT_TRUE(tree.get({}).first);
}

TEST (TreeTests, GetReturnsFalseInFirstElementIfKeyNotFound)
{
  Tree tree;
  EXPECT_FALSE(tree.get({}).first);
}

TEST (TreeTests, CanWriteTree)
{
  Tree tree;
  tree.add({"one", "a"}, "a");
  tree.add({"one", "b"}, "b");

  std::ostringstream actual_json;
  tree.write(actual_json);

  EXPECT_EQ(R"({ "one" : { "a" : "a", "b" : "b" } })", actual_json.str());
}

TEST (TreeTests, CanWriteCoomplicatedTree)
{
  Tree tree;
  tree.add({"A"}, "A");
  tree.add({"B", "A"}, "BA");
  tree.add({"B", "B"}, "BB");
  tree.add({"B", "C"}, "BC");
  tree.add({"C", "A", "A"}, "CAA");
  tree.add({"C", "A", "B"}, "CAB");
  tree.add({"C", "B", "A"}, "CBA");
  tree.add({"C", "B", "B"}, "CBB");

  std::ostringstream actual_json;
  tree.write(actual_json);

  EXPECT_EQ (R"({ "A" : "A", "B" : { "A" : "BA", "B" : "BB", "C" : "BC" }, "C" : { "A" : { "A" : "CAA", "B" : "CAB" }, "B" : { "A" : "CBA", "B" : "CBB" } } })", actual_json.str());
}

TEST (TreeTests, CanOverwriteStringWithString)
{
  Tree tree;
  tree.add({}, "original_value");
  tree.add({}, "new_value");
  EXPECT_EQ("new_value", tree.get({}).second);
}

TEST (TreeTests, CanOverwriteStringWithSubtree)
{
  Tree tree;
  tree.add({"a"}, "a");
  tree.add({"a", "a"}, "child_one");
  tree.add({"a", "b"}, "child_two");
  EXPECT_FALSE(tree.get({"a"}).first);
  EXPECT_EQ(tree.get({"a", "a"}).second, "child_one");
  EXPECT_EQ(tree.get({"a", "b"}).second, "child_two");
}

TEST (TreeTests, CanOverwriteSubtreeWithString)
{
  Tree tree;
  tree.add({"a", "a"}, "child_one");
  tree.add({"a", "b"}, "child_two");
  tree.add({"a"}, "a");
  EXPECT_TRUE(tree.get({"a"}).first);
  EXPECT_FALSE(tree.get({"a", "a"}).first);
  EXPECT_FALSE(tree.get({"a", "b"}).first);
  EXPECT_EQ("a", tree.get({"a"}).second);
}