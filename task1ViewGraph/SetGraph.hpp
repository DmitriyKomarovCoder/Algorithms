#pragma once

#include <vector>
#include <unordered_set>

#include "IGraph.hpp"

class SetGraph : public IGraph {
 public:
    explicit SetGraph(int num);
    explicit SetGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::unordered_set<int>> adjLists;
};
