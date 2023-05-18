#pragma once

#include "IGraph.hpp"

class MatrixGraph : public IGraph {
 public:
    explicit MatrixGraph(int num);
    explicit MatrixGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::vector<bool>> adjLists;
};

