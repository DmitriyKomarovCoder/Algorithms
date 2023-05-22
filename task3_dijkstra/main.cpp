#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cassert>
#include <set>
#include <limits>

const int INF = std::numeric_limits<int>::max();

struct Node {
    int vertex;
    int weight;
};

struct IGraph {
virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<Node> GetNextVertices(int vertex) const = 0;
    virtual std::vector<Node> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
    explicit ListGraph(int vertexCount);
    explicit ListGraph(const IGraph& graph);

    void AddEdge(int from, int to, int weight) override;
    int VerticesCount() const override;
    std::vector<Node> GetNextVertices(int vertex) const override;
    std::vector<Node> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::vector<Node>> adjLists;
    std::vector<std::vector<Node>> prevAdjLists;
};

ListGraph::ListGraph(int vertexCount) :
    adjLists(vertexCount),
    prevAdjLists(vertexCount) {}

ListGraph::ListGraph(const IGraph& graph) {
    adjLists.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjLists[i] = graph.GetNextVertices(i);
        prevAdjLists[i] = graph.GetPrevVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to, int weight) {
    assert(from >= 0 && from < adjLists.size());
    assert(to >= 0 && to < adjLists.size());

    adjLists[from].push_back({to, weight});
    adjLists[to].push_back({from, weight});

    prevAdjLists[to].push_back({from, weight});
    prevAdjLists[from].push_back({to, weight});
}

int ListGraph::VerticesCount() const {
    return adjLists.size();
}

std::vector<Node> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size());
    return adjLists[vertex];
}

std::vector<Node> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size() -1);
    return prevAdjLists[vertex];
}

int dijikstra(const IGraph &graph, int from, int to) {
    std::vector<int> distance(graph.VerticesCount(), INF);
    distance[from] = 0;

    std::set<std::pair<int, int>> q;

    q.insert({0, from});

    while (!q.empty()) {
        int cur = q.begin()->second;
        q.erase(q.begin());

        std::vector<Node> next = graph.GetNextVertices(cur);
        for (const Node &it : next) {
            if (distance[cur] + it.weight < distance[it.vertex]) {
                q.erase({distance[it.vertex], it.vertex});
                distance[it.vertex] = distance[cur] + it.weight;
                q.insert({distance[it.vertex], it.vertex});
            }
        }
    }
    return distance[to];
}

int main() {
    int v, n;
    std::cin >> v >> n;
    ListGraph* listGraph = new ListGraph(v);
    int from, to, time;
    for (int i= 0; i < n; ++i) {
        std::cin >> from >> to >> time;
        listGraph->AddEdge(from, to, time);
    }
    int f, t;
    std::cin >> f >> t;
    std::cout << dijikstra(*listGraph, f, t) << std::endl;
    delete listGraph;
    return 0;
}
