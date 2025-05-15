#include <iostream>

#include "Graph.hpp"

using namespace std;

Node::Node(const string& name) : name(name) {}

const string Node::getName() const {
    return this->name;
}

const bool Node::operator==(const Node& other) const {
    return other.getName() == this->name;
}

const bool Node::operator==(const string& otherName) const {
    return otherName == this->name;
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
        output.append(node->getName());
    }
    return output;
}






Edge::Edge(const ODPair& OD, const int costSubway, const int costTram, const int bonus, const size_t id): OD(OD), costSubway(costSubway), costTram(costTram), bonus(bonus), id(id) {
    for (const Node* node : this->OD.getNodes()) {
        this->info.append(node->getName());
    }
};

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
    return this->getNode(nodeName) != NULL;
}

void Graph::createAndInsertNode(const string& newNodeName) {
    if (!this->containsNode(newNodeName)) {
        this->nodes.push_back(Node(newNodeName));
    }
}

const Node* const Graph::getNode(const std::string& nodeName) const {
    for (const Node& node : this-> nodes) {
        if (node.getName() == nodeName) return &node;
    }
    return NULL;
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
    // const Edge& latestEdge{this->edges.back()};
    // cout << latestEdge.getOD().toString() << endl;
}

void Graph::print() const {
    cout << "Printing Graph:" << endl;
    cout << "Nodes (" << this->nodes.size() << "):" << endl;
    if (this->nodes.size() == 0) {
        cout << " (none)" << endl;
    }
    else {
        for (const Node& node : this->nodes) {
            cout << " " << node.getName() <<  endl;
        }
    }
    cout << "Edges (" << this->edges.size() << "):" << endl;
    if (this->edges.size() == 0) {
        cout << " (none)" << endl;
    }
    else {
        for (const Edge& edge : this->edges) {
            for (const Node* node : edge.getOD().getNodes()) {
                cout << " " << node->getName();
            }
            cout << " " << edge.getCostSubway() << " " << edge.getCostTram() << " " << edge.getBonus() << endl;
        }
    }
}
