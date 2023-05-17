#include <vector>
#include <queue>
#include <cassert>
#include <iostream>



void main() {
    IGraph* ListGraph = new ListGraph(5);
    // ...
    MatrixGraph matrixGraph(ListGraph);
    SetGraph setGraph(matrixGraph);
    ArcGraph arcGraph(setGraph);
    return 0;
}

