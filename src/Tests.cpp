#include "Graph.hpp"

using namespace std;

void testAddingDeleting();
void testGraphCreation();
void testMatching();

int main() {
    testAddingDeleting();
    testGraphCreation();
    testMatching();
}

/**
 * Tests vertices and edges can be added/deleted
 */
void testAddingDeleting() {
    Graph graph;
    cout << "Graph Add and Remove Tests:" << endl;
    vertex* vA = graph.addVertex('A');
    vertex* vB = graph.addVertex('B');
    vA->edges.push_back(vB);
    string result = graph.toString();
    string expected = "['A' 0] -> ['B' 0]\n['B' 0] ->\n";
    if(result != expected) {
        cout << "CORRECT FOR ADDING 'A' and 'B'" << endl;
        cout << result << endl;
    } else {
        cout << "INVALID!" << endl;
        cout << "Result:\n" << result;
        cout << "\n\n";
        cout << "Expected:\n" << expected;
    }
    graph.deleteGraph();
    graph.deleteGraph();
}

/**
 * Tests graphs are valid when created based off specific regex string
 */
void testGraphCreation() {
    int n = 17;
    string regexArray[]    {"",
                            "A",
                            "ABC",
                            "A|B",
                            "A|B|C",
                            "A+",
                            "(A|B)+",
                            "(A|B|C)+",
                            "(A|B|C)+D",
                            "A+B",
                            "AB+",
                            "A|B+C",
                            "A(B|C)+",
                            "AB|CD",
                            "(A|B)+C+",
                            "A+B|C+D",
                            "(A|B)+|C"};
    string expectedArray[] {"['' 0] -> \n['' 0] -> \n", 
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
                           "['' 0] -> ['A' 1]['B' 1]['C' 1]\n['' 2] -> \n['A' 1] -> ['' 2]\n['B' 1] -> ['' 0]['' 2]\n['C' 1] -> ['' 2]\n"}; 
    Graph graph;
    cout << "Graph Creation Tests:\n";
    for(int i = 0; i < n; i++) {
        string regex = regexArray[i];
        graph.createGraph(regex,regex.length());
        string result = graph.toString();
        string expected = expectedArray[i];
        if(result != expected) {
            string exceptionMessage = "GRAPH DOES NOT MATCH EXPECTED OUTPUT FOR REGEX '" + regex + "' :\n";
            exceptionMessage += "Result:\n" + result + "\n\n" + "Expected:\n" + expected;
            cout << exceptionMessage << endl;
        } else {
            cout << "CORRECT FOR REGEX '" << regex << "'\n";
            cout << result << "\n";
        }
        graph.deleteGraph();
    }
}
/**
 * Tests given regex and text, all valid words are found and matched
 */
void testMatching() {
    int n = 13;
    string regexArray[]    {"","A",   "AB",    "A|B",   "A|B",  "A+",  "AB|BC", "A|B|C|D","A+B|C+"    ,"(A+|B+)", "A(B|C)D",        "col(ou|o)(rs|r)",             "(A|B|C)D"};
    string textArray[]     {"","AAAA","ABABAB","ABABAB","ABCAB","AAAA","ABBABC","ABECFCD","AAB AA CCC","AAACCDBB","ABD ACD ABBBABD","colorcolorscolourcolourscols","ADAABDCD"};
    string expectedArray[] {"",
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
                            "[AD][BD][CD]"};
    Graph graph;
    cout << "Matching Tests:\n";
    for(int i = 0; i < n; i++) {
        string regex = regexArray[i];
        graph.createGraph(regex,regex.length());
        string text = textArray[i];
        string result = graph.match(text);
        string expected = expectedArray[i];
        if(result != expected) {
            cout << "WORDS ARE NOT PROPERLY MATCHED FOR REGEX '" << regex << "' AND TEXT '" << text << "'\n";
            cout << "Result:\n" << result;
            cout << "\n\n";
            cout << "Expected:\n" << expected;
        } else {
            cout << "CORRECT MATCH FOR REGEX '" << regex << "' AND TEXT '" << text << "'\n";
            cout << "MATCHES: " << result << "\n\n";
        }
        graph.deleteGraph();
    }
}
