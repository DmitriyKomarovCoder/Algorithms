#include "ArcGraph.hpp"

#include <queue>
#include <cassert>

ArcGraph::ArcGraph(int vertexCount) : sizeGraph(vertexCount) {
    adjLists.reserve(vertexCount);
}

ArcGraph::ArcGraph(const IGraph& graph) : ArcGraph(graph.VerticesCount()) {
    for (int i = 0; i < sizeGraph; ++i) {
        std::vector<int> next = graph.GetNextVertices(i);
        for (const int &it : next) {
            adjLists.emplace_back(i, it);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    adjLists.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return sizeGraph;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto &it : adjLists) {
        if (it.first == vertex) {
            next.push_back(it.second);
        }
    }
    return next;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (const auto& it : adjLists) {
        if (it.second == vertex) {
            prev.push_back(it.first);
        }
    }
    return prev;
}
