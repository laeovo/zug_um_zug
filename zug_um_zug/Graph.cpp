#include <iostream>

#include "Graph.hpp"

using namespace std;

Node::Node(const size_t id) : id(id) {}

const size_t Node::getId() const {
    return this->id;
}

const bool Node::operator==(const Node& other) const {
    return other.getId() == this->id;
}

const bool Node::operator==(const size_t otherId) const {
    return otherId == this->id;
}







ODPair::ODPair(const Node& origin, const Node& destination) : nodes({&origin, &destination}) {}

const bool ODPair::operator==(const ODPair& other) const {
    return this->nodes == other.nodes;
}

const set<const Node*> ODPair::getNodes() const {
    return this->nodes;
}

const bool ODPair::contains(const Node& search) const {
    return this->nodes.contains(&search);
}

const string ODPair::toString() const {
    string output{"OD-Pair:"};
    for (const Node* node: this->nodes) {
        output.append(" ");
        output.append(to_string(node->getId()));
    }
    return output;
}






Edge::Edge(const ODPair& OD, const int costSubway, const int costTram, const int bonus, const size_t id): OD(OD), costSubway(costSubway), costTram(costTram), bonus(bonus), id(id) {};

const ODPair& Edge::getOD() const {
    return this->OD;
}

const int Edge::getCostSubway() const {
    return this->costSubway;
}

const int Edge::getCostTram() const {
    return this->costTram;
}

const int Edge::getBonus() const {
    return this-> bonus;
}






Graph::Graph() {}

const bool Graph::containsNode(const string& nodeName) const {
    return this->nameToIdIndexDictionary.find(nodeName) != this->nameToIdIndexDictionary.end();
}

void Graph::createAndInsertNode(const string& newNodeName) {
    if (!this->containsNode(newNodeName)) {
        const size_t newNodeId{this->nodes.size()};
        this->nodes.push_back(Node(newNodeId));
        this->nameToIdIndexDictionary.insert({newNodeName, newNodeId});
    }
}

const Node* const Graph::getNode(const std::string& nodeName) const {
    if (this->containsNode(nodeName)) {
        return this->getNode(this->nameToIdIndexDictionary.at(nodeName));
    }
    return NULL;
}

const Node* const Graph::getNode(const size_t nodeId) const {
    if (nodeId < this->nodes.size()) {
        return &this->nodes[nodeId];
    }
    return NULL;
}

const string Graph::getNodeName(const Node& node) const {
    if (node == NULL) {
        return "NULL";
    }
    for (const pair<string, size_t> nameIdPair : this->nameToIdIndexDictionary) {
        if (nameIdPair.second == node.getId()) return nameIdPair.first;
    }
    return "NODE NOT FOUND";
}

const bool Graph::containsEdge(const ODPair& OD) const {
    for (const Edge& edge : this->edges) {
        if (edge.getOD() == OD) return true;
    }
    return false;
}

void Graph::createAndInsertEdge(const ODPair& OD, const int costSubway, const int costTram, const int bonus) {
    if (!this->containsEdge(OD)) {
        this->edges.push_back({OD, costSubway, costTram, bonus, this->edges.size()});
    }
    // Test
    const Edge& latestEdge{this->edges.back()};
    cout << latestEdge.getOD().toString() << endl;
}

void Graph::print() const {
    cout << "Printing Graph:" << endl;
    cout << "Nodes:" << endl;
    for (const pair<string, const size_t> nameIdPair : this->nameToIdIndexDictionary) {
        cout << " " << nameIdPair.first << " (" << nameIdPair.second << ")" <<  endl;
    }
    cout << "Edges:" << endl;
    for (const Edge& edge : this->edges) {
        for (const Node* node : edge.getOD().getNodes()) {
            cout << " (" << node->getId() << ") " << this->getNodeName(*node);
        }
        cout << " " << edge.getCostSubway() << " " << edge.getCostTram() << " " << edge.getBonus() << endl;
    }
}
