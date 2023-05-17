#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(int num) {
    adjLists.resize(num);
    for (int i = 0; i < adjLists.size(); i ++) {
        for (int j = 0; j < num; j++) {
            adjLists[i][j] = false;
        }
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph) {
    int sizeGraph = graph.VerticesCount();
    adjLists.resize(sizeGraph);
    for (int i = 0; i < adjLists.size(); i ++) {
        for (int j = 0; j < adjLists.size(); j++) {
            adjLists[i][j] = false;
        }
    }

    for (int i = 0; i < sizeGraph; i++) {
        for (auto next : graph.GetNextVertices(i)) {
            adjLists[i][next] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    adjLists[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return adjLists.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int num) const {
    std::vector<int> next;
    for (int i = 0; i < adjLists.size(); i ++) {
        if (adjLists[num][i]) {
            next.push_back(i);
        }
    }
    return next;
}

std::vector<int> MatrixGraph::GetPrevVertices(int num) const {
    std::vector<int> prev;
    for (int i = 0; i < adjLists.size(); i++) {
        if (adjLists[i][num]) {
            prev.push_back(i);
        }
    }
    return prev;
}