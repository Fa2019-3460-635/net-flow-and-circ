#include "gtest/gtest.h"

#include <climits>
#include "program_options.hpp"

TEST (ProgramOptionsTests, CanParseValidBfsInput)
{
    //set up the mock inputs
    char* moc_argv[] = {
      "program_name", // program name at index 0
      "-b", // Algorithm selection
      "example.txt", // Filename
      "0", // source
      "13", // target
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(), 
              ProgramOptions::AlgorithmSelection::BST);
    EXPECT_EQ(ProgramOptions::graph_filepath(), "example.txt");
    EXPECT_EQ(ProgramOptions::source_node(), 0);
    EXPECT_EQ(ProgramOptions::target_node(), 13);

}

TEST (ProgramOptionsTests, CanParseValidFordFulkersonInput)
{
    //set up the mock inputs
    char* moc_argv[] = {
      "program_name", // program name at index 0
      "-f", // Algorithm selection
      "example.txt", // Filename
      //"0", // source -- Not Required
      //"13", // target -- Not Required
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(), 
              ProgramOptions::AlgorithmSelection::FORD_FULKERSON);
    EXPECT_EQ(ProgramOptions::graph_filepath(), "example.txt");
    EXPECT_EQ(ProgramOptions::source_node(), INT_MIN);
    EXPECT_EQ(ProgramOptions::target_node(), INT_MIN);
}

TEST (ProgramOptionsTests, CanParseValidCirculationInput)
{
    //set up the mock inputs
    char* moc_argv[] = {
      "program_name", // program name at index 0
      "-c", // Algorithm selection
      "example.txt", // Filename
      //"0", // source -- Not Required
      //"13", // target -- Not Required
    };

    int moc_argc = sizeof(moc_argv) / sizeof(char*) - 1;

    // parse it
    ProgramOptions::parse(moc_argc, moc_argv);

    // check it
    EXPECT_EQ(ProgramOptions::program_name(), "program_name");
    EXPECT_EQ(ProgramOptions::selected_algorithm(), 
              ProgramOptions::AlgorithmSelection::CIRCULATION);
    EXPECT_EQ(ProgramOptions::graph_filepath(), "example.txt");
    EXPECT_EQ(ProgramOptions::source_node(), INT_MIN);
    EXPECT_EQ(ProgramOptions::target_node(), INT_MIN);

}
