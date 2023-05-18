#include "SetGraph.hpp"

SetGraph::SetGraph(int num) : adjLists(num) {}

SetGraph::SetGraph(const IGraph& graph) : adjLists(graph.VerticesCount()) {
    for (int i = 0; i < adjLists.size(); ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (int it : nextVertices) {
            adjLists[i].insert(it);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjLists[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjLists.size();
}

std::vector<int> SetGraph::GetNextVertices(int num) const {
    std::vector<int> next;
    for (int it : adjLists[num]) {
         next.push_back(it);
    }
    return next;
}

std::vector<int> SetGraph::GetPrevVertices(int num) const {
    std::vector<int> prev;
    for (int i = 0; i < adjLists.size(); ++i) {
        if (adjLists[i].count(num) > 0) {
            prev.push_back(i);
        }
    }
    return prev;
}