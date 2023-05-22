#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cassert>

struct IGraph {
virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
    explicit ListGraph(int vertexCount);
    explicit ListGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::vector<int>> adjLists;
    std::vector<std::vector<int>> prevAdjLists;
};

ListGraph::ListGraph(int vertexCount) {
    adjLists.resize(vertexCount);
    prevAdjLists.resize(vertexCount);
}

ListGraph::ListGraph(const IGraph& graph) {
    adjLists.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjLists[i] = graph.GetNextVertices(i);
        prevAdjLists[i] = graph.GetPrevVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjLists.size());
    assert(to >= 0 && to < adjLists.size());

    adjLists[from].push_back(to);
    adjLists[to].push_back(from);

    prevAdjLists[to].push_back(from);
    prevAdjLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size());
    return adjLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size());
    return prevAdjLists[vertex];
}


void shortPaths(const IGraph &graph, int from, int to, std::function<void(int)> visit) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::vector<int> path(graph.VerticesCount(), 0);
    std::vector<int> count(graph.VerticesCount(), 0);
    std::queue<int> bfsQ;

    bfsQ.push(from);
    visited[from] = true;
    count[from] = 1;

    while (bfsQ.size() > 0) {
        int current = bfsQ.front();
        bfsQ.pop();

        std::vector<int> next = graph.GetNextVertices(current);
        for (int i = 0; i < next.size(); ++i) {
            if (!visited[next[i]]) {
                bfsQ.push(next[i]);
                path[next[i]] = path[current] + 1;
                visited[next[i]] = true;
            }
            if (path[next[i]] > path[current]) {
                count[next[i]] += count[current];
            }
        }
    }

    visit(count[to]);
}

int main() {
    int v, n;
    std::cin >> v >> n;
    ListGraph* listGraph = new ListGraph(v);
    int from, to;
    for (int i= 0; i < n; ++i) {
        std::cin >> from >> to;
        listGraph->AddEdge(from, to);
    }
    std::cin >> from >> to;
    shortPaths(*listGraph, from, to, [&](int path) {
        std::cout << path <<std::endl;
    });

    return 0;
}