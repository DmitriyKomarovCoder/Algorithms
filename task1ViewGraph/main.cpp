#include <vector>
#include <queue>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "ArcGraph.hpp"

int main() {
    IGraph* listGraph = new ListGraph(9);
    listGraph->AddEdge(0, 1);
    listGraph->AddEdge(0, 5);
    listGraph->AddEdge(1, 2);
    listGraph->AddEdge(1, 3);
    listGraph->AddEdge(1, 5);
    listGraph->AddEdge(1, 6);
    listGraph->AddEdge(3, 2);
    listGraph->AddEdge(3, 4);
    listGraph->AddEdge(3, 6);
    listGraph->AddEdge(5, 4);
    listGraph->AddEdge(5, 6);
    listGraph->AddEdge(6, 4);
    listGraph->AddEdge(7, 8);

    MatrixGraph* matrixGraph = new MatrixGraph(*listGraph);
    SetGraph* setGraph = new SetGraph(*matrixGraph);
    ArcGraph* arcGraph = new ArcGraph(*setGraph);

    for (int i = 0; i < 8; ++i) {
        std::vector<int> nextList = listGraph->GetNextVertices(i);
        std::vector<int> nextMatrix = matrixGraph->GetNextVertices(i);
        std::vector<int> nextSetGraph = setGraph->GetNextVertices(i);
        std::vector<int> nextArcGraph = arcGraph->GetNextVertices(i);

        std::sort(nextList.begin(), nextList.end());
        std::sort(nextMatrix.begin(), nextMatrix.end());
        std::sort(nextSetGraph.begin(), nextSetGraph.end());
        std::sort(nextArcGraph.begin(), nextArcGraph.end());
        assert(nextList == nextMatrix);
        assert(nextSetGraph == nextMatrix);
        assert(nextArcGraph == nextList);
    }

    for (int i = 0; i < 8; ++i) {
        std::vector<int> prevList = listGraph->GetPrevVertices(i);
        std::vector<int> prevMatrix = matrixGraph->GetPrevVertices(i);
        std::vector<int> prevSetGraph = setGraph->GetPrevVertices(i);
        std::vector<int> prevArcGraph = arcGraph->GetPrevVertices(i);

        std::sort(prevList.begin(), prevList.end());
        std::sort(prevMatrix.begin(), prevMatrix.end());
        std::sort(prevSetGraph.begin(), prevSetGraph.end());
        std::sort(prevArcGraph.begin(), prevArcGraph.end());

        assert(prevList == prevMatrix);
        assert(prevSetGraph == prevMatrix);
        assert(prevArcGraph == prevList);
    }

    std::cout << "SUCCESS" << std::endl;

    delete listGraph;
    delete matrixGraph;
    delete setGraph;
    delete arcGraph;

    return 0;
}
