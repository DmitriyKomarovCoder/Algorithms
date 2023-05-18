#pragma once

#include "IGraph.hpp"

class ArcGraph : public IGraph {
 public:
    explicit ArcGraph(int vertexCount);
    explicit ArcGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::pair<int, int>> adjLists;
    int sizeGraph;
};
