#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Graph.hpp"

using namespace std;

// Helper function to split string into substrings
const vector<string> explode(const string& input, char separator) {
    if (input == "") {
        return {""};
    }
    vector <string> outputWords;
    string word = "";
    for (int i = 0; i <= input.size(); i++) {
        if (input[i] == separator || i == input.size()) {
            outputWords.push_back(word);
            word = "";
        }
        else {
            word.push_back(input[i]);
        }
    }
    return outputWords;
}

// TODO: implement str replace function


int main(int argc, const char * argv[]) {
    Graph graph{};
    // Read nodes
    fstream fin_nodes;
    fin_nodes.open("/Users/leovornberger/Code/zug_um_zug/nodes.csv", ios::in);
    string line;
    fin_nodes >> line; // skip header line
    fin_nodes >> line;
    while (line != "end") {
        graph.createAndInsertNode(line);
        fin_nodes >> line;
    }
    cout << graph.getNodes().size() << " Nodes erstellt" << endl;
    
    // Read edges
    fstream fin_edges;
    fin_edges.open("/Users/leovornberger/Code/zug_um_zug/edges.csv", ios::in);
    fin_edges >> line; // skip header line
    fin_edges >> line;
    while (line != "end") {
        const vector<string> lineInfo{explode(line, ';')};
        const Node* origin{graph.getNode(lineInfo[0])};
        const Node* destination{graph.getNode(lineInfo[1])};
        if (origin == NULL) {
            cout << "Node (" << lineInfo[0] << ") wurde nicht gefunden" << endl;
            return 1;
        }
        if (destination == NULL) {
            cout << "Node (" << lineInfo[1] << ") wurde nicht gefunden" << endl;
            return 1;
        }
        const int costSubway{stoi(lineInfo[2])};
        const int costTram{stoi(lineInfo[3])};
        const int bonus{stoi(lineInfo[4])};
        
        graph.createAndInsertEdge({*origin, *destination}, costSubway, costTram, bonus);
        fin_edges >> line;
    }
    cout << graph.getEdges().size() << " Edges erstellt" << endl;
    
    graph.doPrecomputations();
    
    // read routes
    vector<Route> routes;
    fstream fin_routes;
    fin_routes.open("/Users/leovornberger/Code/zug_um_zug/routes.csv");
    fin_routes >> line; // skip header line
    fin_routes >> line;
    while (line != "end") {
        const vector<string> lineInfo{explode(line, ';')};
        const Node* origin{graph.getNode(lineInfo[0])};
        const Node* destination{graph.getNode(lineInfo[1])};
        if (origin == NULL) {
            cout << "Node (" << lineInfo[0] << ") wurde nicht gefunden" << endl;
            return 1;
        }
        if (destination == NULL) {
            cout << "Node (" << lineInfo[1] << ") wurde nicht gefunden" << endl;
            return 1;
        }
        const int bonus{stoi(lineInfo[2])};
        const Route newRoute{{*origin, *destination}, bonus};
        routes.push_back(newRoute);
        fin_routes >> line;
    }
    cout << routes.size() << " Routen erstellt" << endl;
    
    // read must-includes
    vector<const Node*> mustIncludes;
    fstream fin_mustIncludes;
    fin_mustIncludes.open("/Users/leovornberger/Code/zug_um_zug/must-include.csv");
    fin_mustIncludes >> line; // skip header line
    fin_mustIncludes >> line;
    while (line != "end") {
        mustIncludes.push_back(graph.getNode(line));
        fin_mustIncludes >> line;
    }
    cout << mustIncludes.size() << " Must-Includes gelesen" << endl;
    
    // Create and test solutions
    vector<bool> solutionCandidateVector{};
    for (size_t i = 0; i < graph.getEdges().size(); ++i) {
        solutionCandidateVector.push_back(false);
    }
    
    int highestBonus{0};
    while (true) { // TODO: find break condition
        const Solution solutionCandidate(graph, solutionCandidateVector, routes, mustIncludes);
        if (solutionCandidate.check()) {
            if (solutionCandidate.computeBonus() > highestBonus) {
                highestBonus = solutionCandidate.computeBonus();
                solutionCandidate.printLong();
            }
        }
        for (size_t digit = 0; digit < solutionCandidateVector.size(); ++digit) {
            if (solutionCandidateVector[digit] == true) solutionCandidateVector[digit] = false;
            else if (solutionCandidateVector[digit] == false) {
                solutionCandidateVector[digit] = true;
                break;
            }
        }
    }
    
    
    

    return 0;
}

// TODO: Kreise eliminieren
// TODO: Zoo und Kudamm sicherstellen
