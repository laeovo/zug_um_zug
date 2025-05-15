#ifndef Graph_hpp
#define Graph_hpp

#include <unordered_map>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>

class Node {
public:
    Node(const std::string& name);
    const std::string getName() const;
    const bool operator==(const Node& other) const;
    const bool operator==(const std::string& otherName) const;
private:
    const std::string name;
};

class ODPair {
public:
    ODPair(const Node& origin, const Node& destination);
    const bool operator==(const ODPair& other) const;
    const std::set<const Node*> getNodes() const;
    const bool contains(const Node& search) const;
    const std::string toString() const;
private:
    const std::set<const Node*> nodes; // TODO: make it of type const std::set<const Node* const>
};

class Edge {
public:
    Edge(const ODPair& OD, const int costSubway, const int costTram, const int bonus, const size_t id);
    const ODPair& getOD() const;
    const int getCostSubway() const;
    const int getCostTram() const;
    const int getBonus() const;
private:
    const ODPair OD;
    const int costSubway;
    const int costTram;
    const int bonus;
    const size_t id;
    std::string info{""};
};

class Graph {
public:
    Graph();
    const bool containsNode(const std::string& nodeName) const; // TODO: get rid
    void createAndInsertNode(const std::string& newNodeName);
    const Node* const getNode(const std::string& nodeName) const;
    const bool containsEdge(const ODPair& OD) const;
    void createAndInsertEdge(const ODPair& OD, const int costSubway, const int costTram, const int bonus);
    void print() const;
private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};

//const vector<const Edge*> getKanten(const Node* const knoten, const vector<const Edge*>& kanten) {
//    vector<const Edge*> output{};
//    for (const Edge* kante : kanten) {
//        if (kante->getStart() == knoten || kante->getEnde() == knoten) output.push_back(kante);
//    }
//    return output;
//}

#endif /* Graph_hpp */
