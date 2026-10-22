#include <gtest/gtest.h>
#include "Graph.hpp"

#include <string>
#include <vector>

using namespace std;


/**
 * Graph Creation
 */

TEST(GraphTests, GraphCreation) {
    vector<string> regexArray = {
        "", "A", "ABC", "A|B", "A|B|C",
        "A+", "(A|B)+", "(A|B|C)+",
        "(A|B|C)+D", "A+B", "AB+",
        "A|B+C", "A(B|C)+", "AB|CD",
        "(A|B)+C+", "A+B|C+D", "(A|B)+|C"
    };

    vector<string> expectedArray = {
        "['' 0] -> \n['' 0] -> \n",
        "['' 0] -> ['A' 1]\n['' 2] -> \n['A' 1] -> ['' 2]\n",
        "['' 0] -> ['A' 1]\n['' 4] -> \n['A' 1] -> ['B' 2]\n['B' 2] -> ['C' 3]\n['C' 3] -> ['' 4]\n",
        "['' 0] -> ['A' 1]['B' 1]\n['' 2] -> \n['A' 1] -> ['' 2]\n['B' 1] -> ['' 2]\n",
        "['' 0] -> ['A' 1]['B' 1]['C' 1]\n['' 2] -> \n['A' 1] -> ['' 2]\n['B' 1] -> ['' 2]\n['C' 1] -> ['' 2]\n",
        "['' 0] -> ['A' 1]\n['' 2] -> \n['A' 1] -> ['A' 1]['' 2]\n",
        "['' 0] -> ['A' 1]['B' 1]\n['' 2] -> ['' 0]\n['A' 1] -> ['' 2]\n['B' 1] -> ['' 2]\n",
        "['' 0] -> ['A' 1]['B' 1]['C' 1]\n['' 2] -> ['' 0]\n['A' 1] -> ['' 2]\n['B' 1] -> ['' 2]\n['C' 1] -> ['' 2]\n",
        "['' 0] -> ['A' 1]['B' 1]['C' 1]\n['' 2] -> ['' 0]['D' 3]\n['A' 1] -> ['' 2]\n['B' 1] -> ['' 2]\n['C' 1] -> ['' 2]\n['' 4] -> \n['D' 3] -> ['' 4]\n",
        "['' 0] -> ['A' 1]\n['' 3] -> \n['A' 1] -> ['A' 1]['B' 2]\n['B' 2] -> ['' 3]\n",
        "['' 0] -> ['A' 1]\n['' 3] -> \n['A' 1] -> ['B' 2]\n['B' 2] -> ['B' 2]['' 3]\n",
        "['' 0] -> ['A' 1]['B' 1]\n['' 3] -> \n['A' 1] -> ['' 3]\n['B' 1] -> ['B' 1]['C' 2]\n['C' 2] -> ['' 3]\n",
        "['' 0] -> ['A' 1]\n['' 2] -> ['B' 3]['C' 3]\n['A' 1] -> ['' 2]\n['' 4] -> ['' 2]\n['B' 3] -> ['' 4]\n['C' 3] -> ['' 4]\n",
        "['' 0] -> ['A' 1]['C' 1]\n['' 3] -> \n['A' 1] -> ['B' 2]\n['B' 2] -> ['' 3]\n['C' 1] -> ['D' 2]\n['D' 2] -> ['' 3]\n",
        "['' 0] -> ['A' 1]['B' 1]\n['' 2] -> ['' 0]['C' 3]\n['A' 1] -> ['' 2]\n['B' 1] -> ['' 2]\n['' 4] -> \n['C' 3] -> ['C' 3]['' 4]\n",
        "['' 0] -> ['A' 1]['C' 1]\n['' 3] -> \n['A' 1] -> ['A' 1]['B' 2]\n['B' 2] -> ['' 3]\n['C' 1] -> ['C' 1]['D' 2]\n['D' 2] -> ['' 3]\n",
        "['' 0] -> ['A' 1]['B' 1]['C' 1]\n['' 2] -> \n['A' 1] -> ['' 2]\n['B' 1] -> ['' 0]['' 2]\n['C' 1] -> ['' 2]\n"
    };

    ASSERT_EQ(regexArray.size(), expectedArray.size());

    for (size_t i = 0; i < regexArray.size(); i++) {
        Graph graph;

        graph.createGraph(
            regexArray[i],
            regexArray[i].length()
        );

        EXPECT_EQ(graph.toString(), expectedArray[i])
            << "Failed regex: " << regexArray[i];

        graph.deleteGraph();
    }
}

/**
 * Testing matching
 */

TEST(GraphTests, RegexMatching) {
    vector<string> regexArray = {
        "", "A", "AB", "A|B", "A|B",
        "A+", "AB|BC", "A|B|C|D",
        "A+B|C+", "(A+|B+)", "A(B|C)D",
        "col(ou|o)(rs|r)", "(A|B|C)D"
    };

    vector<string> textArray = {
        "",
        "AAAA",
        "ABABAB",
        "ABABAB",
        "ABCAB",
        "AAAA",
        "ABBABC",
        "ABECFCD",
        "AAB AA CCC",
        "AAACCDBB",
        "ABD ACD ABBBABD",
        "colorcolorscolourcolourscols",
        "ADAABDCD"
    };

    vector<string> expectedArray = {
        "",
        "[A][A][A][A]",
        "[AB][AB][AB]",
        "[A][B][A][B][A][B]",
        "[A][B][A][B]",
        "[AAAA]",
        "[AB][AB]",
        "[A][B][C][C][D]",
        "[AAB][CCC]",
        "[AAA][BB]",
        "[ABD][ACD][ABD]",
        "[color][colors][colour][colours]",
        "[AD][BD][CD]"
    };

    ASSERT_EQ(regexArray.size(), textArray.size());
    ASSERT_EQ(regexArray.size(), expectedArray.size());

    for (size_t i = 0; i < regexArray.size(); i++) {
        Graph graph;

        graph.createGraph(
            regexArray[i],
            regexArray[i].length()
        );

        EXPECT_EQ(graph.match(textArray[i]), expectedArray[i])
            << "Failed regex: " << regexArray[i]
            << "\nText: " << textArray[i];

        graph.deleteGraph();
    }
}
