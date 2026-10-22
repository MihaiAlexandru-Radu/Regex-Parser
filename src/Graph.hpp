#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct vertex {
    char key;
    int distance = 0; //represents distance from left-most node
    bool isTerminal = false; // tracks right-most node in graph, used in matching function
    bool isStart = false; // tracks current start when making graph, used to ensure its distance is not changed
    vector<vertex*> edges;
    vertex* containsEdge(char key);
    string toString();
};

class Graph {

    public:
        ~Graph();
        void createGraph(string regex, int length);
        void addEdge(vertex* from, vertex* to);
        void deleteGraph();
        string match(string text);
        string toString();
        vertex* addVertex(char key);

    private:
        vector<vertex*> vertices;
        vector<string> matches; // when matching, all words are placed into this vector
        vertex* concatenate(vertex* cur, char key);
        vertex* changeStart(vertex*& start, vertex*& end);
        bool isLastChar(int i, int length);
        void matchHelper(string text, vertex* cur, vertex* matchEnd, vertex* start, int i, int matchStart, string word);
};

#endif
