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
    string output{""};
    for (const Node* node: this->nodes) {
        output.append("-");
        output.append(node->getName());
    }
    return output;
}





Route::Route(const ODPair& OD, const int bonus) : OD(OD), bonus(bonus) {}

void Route::print() const {
    cout << "Route: " << this->OD.toString() << "  Bonus: " << this->bonus << endl;
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
}

const vector<Edge>& Graph::getEdges() const {
    return this->edges;
}

const vector<Node>& Graph::getNodes() const {
    return this->nodes;
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

void Graph::doPrecomputations() {
    // Compute stars
    for (const Node& center : this->nodes) {
        vector<const Node*> star{};
        for (const Node& other : this->nodes) {
            for (const Edge& edge : this->edges) {
                if (edge.getOD().contains(center) && edge.getOD().contains(other)) {
                    star.push_back(&other);
                    break;
                }
            }
        }
        this->stars.insert({&center, star});
    }
}

const vector<const Node*> Graph::getStar(const Node* node) const {
    return this->stars.at(node);
}






Solution::Solution(const Graph& graph, const vector<bool>& edges, const vector<Route>& routes, const vector<const Node*> mustIncludes) : graph(graph), edgesVector(edges), routes(routes), mustIncludes(mustIncludes) {
    for (size_t i = 0; i < this->graph.getEdges().size(); ++i) {
        if (this->edgesVector[i]) this->edges.push_back(&graph.getEdges()[i]);
    }
    for (const Edge* edge : this->edges) {
        for (const Node* node : edge->getOD().getNodes()) {
            if (find(this->nodes.begin(), this->nodes.end(), node) == this->nodes.end()) this->nodes.push_back(node);
        }
    }
}

void Solution::print() const {
    for (size_t i = 0; i < this->edgesVector.size(); ++i) {
        if (this->edgesVector[i]) cout << "1";
        if (!this->edgesVector[i]) cout << "0";
        cout << " ";
    }
    cout << "Cost: " << this->computeCostSubway() << "/" << this->computeCostTram() << " Bonus: " << this->computeBonus() << endl;
}

void Solution::printLong() const {
    cout << "Solution:" << endl;
    cout << " ";
    this->print();
    cout << " Edges:" << endl;
    for (const Edge* const edge : this->edges) {
        cout << "  " << edge->getOD().toString() << "  Cost: " << edge->getCostSubway() << "/" << edge->getCostTram() << "  Bonus: " << edge->getBonus() << endl;
    }
    cout << " Nodes:" << endl;
    for (const Node* node : this->nodes) {
        cout << "  " << node->getName() << endl;
    }
    cout << " Finished routes:" << endl;
    for (const Route& route : this->routes) {
        if (this->containsODPair(route.OD)) {
            cout << "  ";
            route.print();
        }
    }
    cout << " Solution is";
    if (!this->checkConnected()) {
        cout << " not";
    }
    cout << " connected." << endl;
    cout << endl;
}

const int Solution::computeCostSubway() const {
    int output{0};
    for (const Edge* edge : this->edges) {
        output += edge->getCostSubway();
    }
    return output;
}

const int Solution::computeCostTram() const {
    int output{0};
    for (size_t i = 0; i < this->graph.getEdges().size(); ++i) {
        if (this->edgesVector[i]) output += graph.getEdges()[i].getCostTram();
    }
    return output;
}

const int Solution::computeBonus() const {
    int output{0};
    for (size_t i = 0; i < this->graph.getEdges().size(); ++i) {
        if (this->edgesVector[i]) output += graph.getEdges()[i].getBonus();
    }
    return output + this->computeRouteBonus();
}

const int Solution::computeRouteBonus() const {
    int output{0};
    for (const Route& route : this->routes) {
        if (this->containsODPair(route.OD)) {
            output += route.bonus;
        }
    }
    return output;
}

const bool Solution::check() const {
//    if (!this->checkMustIncludes()) return false;
    if (!this->checkCost()) return false;
    if (!this->checkNoCycles()) return false;
    if (!this->checkConnected()) return false;
    return true;
}

const bool Solution::checkCost() const {
    if (this->computeCostSubway() > 5) return false;
    if (this->computeCostTram() > 11) return false;
    
    return true;
}

const bool Solution::checkNoCycles() const {
    // Using Depth first search
//    vector<bool> visited{};
//    for (size_t i = 0; i < this->graph.getNodes().size(); ++i) visited.push_back(false);
    
    return true;
}

const bool Solution::checkConnected() const {
    if (this->nodes.empty()) return true;
    vector<const Node*> visited;
    const Node* startNode{*this->edges.front()->getOD().getNodes().begin()};
    visited.push_back(startNode);
    size_t i = 0;
    while (i < visited.size()) {
//        const vector<const Node*> star{this->graph.getStar(visited[i])};
        vector<const Node*> star{};
        for (const Edge* e : this->edges) {
            if (e->getOD().contains(*visited[i])) {
                for (const Node* n : e->getOD().getNodes()) {
                    if (n != visited[i]) {
                        star.push_back(n);
                    }
                }
            }
        }
        for (const Node* n : star) {
            if (find(visited.begin(), visited.end(), n) == visited.end()) {
                visited.push_back(n);
            }
        }
        ++i;
    }
//    cout << "checkConnected:: visited.size = " << visited.size() << ", this->nodes.size = " << this->nodes.size() << endl;
    if (visited.size() == this->nodes.size()) {
        return true;
    }
    return false;
}

const bool Solution::checkMustIncludes() const {
    for (const Node* node : this->mustIncludes) {
        if (!this->containsNode(node)) {
            return false;
        }
    }
    return true;
}

const bool Solution::containsNode(const Node* node) const {
    for (const Edge* edge : this->edges) {
        for (const Node* containedNode : edge->getOD().getNodes()) {
            if (node == containedNode) {
                return true;
            }
        }
    }
    return false;
}

const bool Solution::containsODPair(const ODPair& OD) const {
    for (const Node* node : OD.getNodes()) {
        if (!this->containsNode(node)) {
            return false;
        }
    }
    return true;
}
