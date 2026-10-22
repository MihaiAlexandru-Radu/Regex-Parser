#include "Graph.hpp"

#include <iostream>
#include <string>

using namespace std;

void printOptions() {
    cout << "+----------------------------+" << endl;
    cout << "|(1) Write Regular Expression|" << endl;
    cout << "|(2) Print Graph             |" << endl;
    cout << "|(3) Write Text              |" << endl;
    cout << "|(4) Find Matches            |" << endl;
    cout << "|(5) Quit                    |" << endl;
    cout << "+----------------------------+" << endl;
    cout << "Choose Number> "; 
}

int main() {
    Graph graph;
    string regex, text;
    int input = -1;
    while(input != 5) {
        printOptions();
        cin >> input;
        while(cin.fail()) {
            cin.clear();
            cin.ignore();
        }
        switch(input) {
            case 1:
                graph.deleteGraph();
                cout << "Regex> ";
                cin >> regex;
                graph.createGraph(regex,regex.length());
                break;
            case 2:
                cout << graph.toString();
                break;
            case 3:
                cin.ignore();
                cout << "Text> ";
                getline(cin, text);
                break;
            case 4:
                cout << "Regex: " << regex << endl;
                cout << "Text: " << text << endl;
                cout << "Matches: ";
                cout << graph.match(text) << endl;
                break;
            case 5:
                break;
        }
        cout << endl;
    }
}
