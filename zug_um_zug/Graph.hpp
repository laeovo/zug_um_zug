#ifndef Graph_hpp
#define Graph_hpp

#include <unordered_map>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>

class Node {
public:
    Node(const size_t id);
    const size_t getId() const;
    const bool operator==(const Node& other) const;
    const bool operator==(const size_t otherId) const;
private:
    const size_t id;
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
};

class Graph {
public:
    Graph();
    const bool containsNode(const std::string& nodeName) const;
    void createAndInsertNode(const std::string& newNodeName);
    const Node* const getNode(const std::string& nodeName) const;
    const Node* const getNode(const size_t nodeId) const;
    const std::string getNodeName(const Node& node) const;
    const bool containsEdge(const ODPair& OD) const;
    void createAndInsertEdge(const ODPair& OD, const int costSubway, const int costTram, const int bonus);
    void print() const;
private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::unordered_map<std::string, const size_t> nameToIdIndex;
};

//const vector<const Edge*> getKanten(const Node* const knoten, const vector<const Edge*>& kanten) {
//    vector<const Edge*> output{};
//    for (const Edge* kante : kanten) {
//        if (kante->getStart() == knoten || kante->getEnde() == knoten) output.push_back(kante);
//    }
//    return output;
//}

#endif /* Graph_hpp */
