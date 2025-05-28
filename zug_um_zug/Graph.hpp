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

struct Route {
public:
    Route(const ODPair& OD, const int bonus);
    void print() const;
    const ODPair OD;
    const int bonus;
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
    const bool containsNode(const std::string& nodeName) const; // TODO: get rid
    void createAndInsertNode(const std::string& newNodeName);
    const Node* const getNode(const std::string& nodeName) const;
    const bool containsEdge(const ODPair& OD) const;
    void createAndInsertEdge(const ODPair& OD, const int costSubway, const int costTram, const int bonus);
    const std::vector<Edge>& getEdges() const;
    const std::vector<Node>& getNodes() const;
    void print() const;
    void doPrecomputations();
private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::vector<std::vector<const Node*>> stars;
};

class Solution {
public:
    Solution(const Graph& graph, const std::vector<bool>& edges, const std::vector<Route>& routes, const std::vector<const Node*> mustIncludes);
    void print() const;
    void printLong() const;
    const int computeCostSubway() const;
    const int computeCostTram() const;
    const int computeBonus() const;
    const int computeRouteBonus() const;
    const bool check() const; // checks if it makes sense to store this solution
    const bool checkCost() const;
    const bool checkNoCycles() const;
    const bool checkConnected() const;
    const bool checkMustIncludes() const;
    const bool containsNode(const Node* node) const;
    const bool containsODPair(const ODPair& OD) const;
private:
    const std::vector<bool> edgesVector;
    std::vector<const Edge*> edges;
    const Graph& graph;
    const std::vector<Route>& routes;
    const std::vector<const Node*> mustIncludes;
};

#endif /* Graph_hpp */
