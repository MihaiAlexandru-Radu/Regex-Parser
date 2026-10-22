/**
 * Inspired by Thompson's Construction (https://en.wikipedia.org/wiki/Thompson%27s_construction)
 */

#include "Graph.hpp"

using namespace std;

/**
 * Given string 'text' of size 'length', print all matches given current regex graph
 * @returns string of matched words
 */
string Graph::match(string text) {
    string matchInfo = "";
    if(vertices.empty()) return matchInfo;
    matches.clear();
    matchHelper(text,vertices[0],nullptr,vertices[0],0,-1,"");
    for(string match : matches) {
        matchInfo += "[" + match + "]";
    }
    return matchInfo;
}

/**
 * Recursive Helper which finds all valid word matches and stores them in 'matches' vector
 * @param text string to be checked for possible matches
 * @param cur current vertex pointed to
 * @param matchEnd [only if loops are present] given node 'A' is looping and an edge of 'cur', 'matchEnd' is the 
 * next empty, non-looping node in edges, replacing 'cur' if no more valid edges
 * @param start when function is stuck, the graph goes back to vertex 'start', generally vertices[0], though replaced 
 * if it finds new non-terminal, empty edge
 * @param i index integer of current character in text
 * @param matchStart first index in text where a character was found, will replace i when it can't find valid edge and 
 * needs to back-track. Once program no longer finds valid characters, match start is reset 
 * @param word current sub-string of potentially valid or non-valid word formed
 */
void Graph::matchHelper(string text, vertex* cur, vertex* matchEnd, vertex* start, int i, int matchStart, string word) {
    if(i > (int) text.length()) {
        return;
    }
    if(cur->isTerminal) { 
        matches.push_back(word);
        cur = vertices[0];
        start = vertices[0];
        matchEnd = nullptr;
        word = "";
        matchStart = -1;
    }
    /** There's a change the last letter contributes to a match. Since there's one extra "terminal node", the function 
    should still run one more time if there's a potential match. */ 
    char c = (i < (int) text.length()) ? text.at(i) : '\0';
    for(vertex* edge : cur->edges) {
        if(c != '\0' && edge->key == c) { 
            if(matchStart == -1) 
                matchHelper(text,edge,matchEnd,start,i+1,i,word+c);
            else
                matchHelper(text,edge,matchEnd,start,i+1,matchStart,word+c);
            return;
        } else if(edge->key == '\0') {
            if(edge->distance < cur->distance) {
                /** If there's a loop on current edge, we find the next empty edge and record it as 'matchEnd'
                When running out of valid edges, 'cur' will be replaced with 'matchEnd' to record word eventually */
                matchStart = -1; 
                for(vertex* nextEmpty : cur->edges) {
                    if(nextEmpty->key == '\0' && nextEmpty->distance > edge->distance) {
                        matchEnd = nextEmpty;
                        break;
                    }
                }
            }
            if(!edge->isTerminal) start = edge;
            /** If we traversed through empty node, we didn't actually traverse through text.
            As such, 'i' is kept at same location. */
            matchHelper(text,edge,matchEnd,start,i,matchStart,word);
            return;
        } 
    }
    if(matchStart != -1) {
        if(matchEnd != nullptr) // If loop-edge found and no valid edges currently, we go to 'matchEnd' to avoid infinite recursion
            matchHelper(text,matchEnd,nullptr,start,matchStart+1,-1,word.substr(0,word.length()-matchStart+1));
        else
            matchHelper(text,start,nullptr,start,matchStart+1,-1,"");
    }  else {
        // No valid edges found in current index, reset traversal variables and go on to next index
        matchHelper(text,vertices[0],nullptr,vertices[0],i+1,-1,"");
    }
}

/**
 * Given regex statement 'regex', create graph with nodes which can be traversed to check for matches
 * @param regex regex statement
 * @param length length of regex statement
 */
void Graph::createGraph(string regex, int length) {
    vertex* start = addVertex('\0');
    start->isStart = true;
    vertex* end = addVertex('\0');
    end->isTerminal = true;
    vertex* cur = start;
    bool containsOr = false, inParentheses = false;
    for(int i = 0; i < length; i++) {
        char key = regex.at(i);
        if(key == '|') { // Deals with OR
            if(!cur->isStart) {
                addEdge(cur,end);
            }
            cur = start;
            if(inParentheses) containsOr = true;
        } else if(key == '+') { // Deals with ONE OR MORE
            int distance = cur->distance;
            addEdge(cur,cur);
            //Distance shouldn't be changed if edge points to itself
            cur->distance = distance; 
            if(isLastChar(i, length)) {
                addEdge(cur,end);
            }
        } else if(key == '(') { // Deals with PARANTHESES
            inParentheses = true;
            if(!cur->isStart) {
                addEdge(cur,end);
                cur = changeStart(start, end);
            }
        } else if(key == ')') { 
            bool plusAfter = (!isLastChar(i, length) && regex.at(i+1) == '+');
            if(plusAfter) {
                i++;
                /** Edge Case: If there is a '|' inside parentheses followed by a '+' and NOT then followed by another '|', loop is from end->start, not cur->start **/
                if(containsOr && (isLastChar(i, length) || regex.at(i+1) != '|')) addEdge(end,start);
                else addEdge(cur, start);   
            }
            if(!cur->isStart) {
                addEdge(cur,end);
            }
            if(!isLastChar(i, length) && regex.at(i+1) != '|') { // Edge Case: '|' after parentheses 
                cur = changeStart(start, end);
            } else cur = start;
            containsOr = false;
            inParentheses = false;
        } else { // If none of above options are available, then concatanate. 
            cur = concatenate(cur, key);
            if(isLastChar(i, length)) {
                addEdge(cur,end);
            }
        }
    }
}

/**
 * From vertex 'cur' add new edge with key 'key'
 * @param cur current vertex
 * @param key key of node to be added
 * @returns new vertex with key 'key' which is an edge of cur
 * @note If 'cur' already has edge with given key we just return given edge
 */
vertex* Graph::concatenate(vertex* cur, char key) {
    vertex* edge = cur->containsEdge(key);
    if(edge == NULL) {
        vertex* addedVertex = addVertex(key);
        addEdge(cur, addedVertex);
        return addedVertex;
    } else {
        return edge;
    }
}

/**
 * Sets new start to be end, and creates new end vertex
 * @param start start vertex
 * @param end end node
 * @returns new start node
 * @note In certain scenarions (e.g. instance of ')' in regex), there need to be 
 * new start and end nodes to continue creating the graph
 */
vertex* Graph::changeStart(vertex*& start, vertex*& end) {
    start->isStart = false;
    end->isTerminal = false;
    start = end;
    end = addVertex('\0');
    start->isStart = true;
    end->isTerminal = true;
    return start;
}

/**
 * In list of vertices, add new vertex with given key
 * @param key key of new added vertex
 * @returns added vertex
 */
vertex* Graph::addVertex(char key) {
    vertex* addedVertex = new vertex;
    addedVertex->key = key;
    vertices.push_back(addedVertex);
    return addedVertex;
}

/**
 * Given index 'i', returns boolean if i is last index in string of length 'length'
 * @param i index of current character
 * @param length length of string
 * @returns true if last character in string of given length, false if not
 */
bool Graph::isLastChar(int i, int length) {
    return (i == length - 1);   
}

/**
 * From vertex 'to', add edge pointing towards vertex 'to' and sets distance from left-most node
 * @param from vertex where edge is added
 * @param to vertex where edge points to
 * @note If both 'from' and 'to' are the same nodes, or empty node with distance already initialized, its distance will not be set
 */
void Graph::addEdge(vertex* from, vertex* to) {
    from->edges.push_back(to);
    if(!to->isStart) to->distance = from->distance + 1;
}

/**
 * For each vertex, print its key, distance, with its edges 
 */
string Graph::toString() {
    string verticesInfo;
    for(vertex* v : vertices) {
        verticesInfo += v->toString();
        verticesInfo += " -> ";
        for(vertex* e : v->edges) {
            verticesInfo += e->toString();
        }
        verticesInfo += '\n';
    }
    return verticesInfo;
}

/**
 * From vertex, return edge with given key, NULL if absent
 * @param key key of node to be returned
 * @returns edge if key present, NULL if absent 
 */
vertex* vertex::containsEdge(char key) {
    for(vertex* edge : edges) {
        if(edge->key == key) {
            return edge;
        }
    }
    return NULL;
}

/**
 * For given vertex, return string its key and distance from left-most node
 * @returns string representation of vertex
 */
string vertex::toString() {
    string vertexInfo;
    vertexInfo += "['";
    if(key != '\0') vertexInfo += key;
    vertexInfo += "' " + to_string(distance) + "]";
    return vertexInfo;
}

/**
 * Deconstructor
 */
Graph::~Graph() {
    deleteGraph();
}

/**
 * Deconstructor helper
 */
void Graph::deleteGraph() {
    for(vertex* v : vertices) {
        delete v;
    }
    vertices.clear();
}
