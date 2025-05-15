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


int main(int argc, const char * argv[]) {
    Graph graph{};
    fstream fin;
    fin.open("/Users/leovornberger/Code/zug_um_zug/kanten.csv", ios::in);
    string line;
    fin >> line;
    while (line != "ende") {
        const vector<string> lineInfo{explode(line, ';')};
        const string origin{lineInfo[0]};
        const string destination{lineInfo[1]};
        const int costSubway{stoi(lineInfo[2])};
        const int costTram{stoi(lineInfo[3])};
        const int bonus{stoi(lineInfo[4])};
        graph.createAndInsertNode(origin);
        graph.createAndInsertNode(destination);
        graph.createAndInsertEdge({*graph.getNode(origin), *graph.getNode(destination)}, costSubway, costTram, bonus);
        fin >> line;
    }
    
    graph.print();

    return 0;
}

// TODO: Kreise eliminieren
// TODO: Zoo und Kudamm sicherstellen
