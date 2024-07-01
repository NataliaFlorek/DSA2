#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

struct Edge {
    int to;
    double probability;
};

double prim(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    priority_queue<pair<double, int>> pq;
    double totalProbability = 1.0;

    pq.push({1.0, start});

    while (!pq.empty()) {
        double probability = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        totalProbability *= probability;

        for (int j = 0; j < graph[u].size(); ++j) {
            const Edge& e = graph[u][j];
            int v = e.to;
            double p = e.probability;
            if (!visited[v]) {
                pq.push({p, v});
            }
        }

    }


    return totalProbability;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        double p;
        cin >> u >> v >> p;
        graph[u].push_back({v, p});
        graph[v].push_back({u, p});
    }

    double result = prim(graph, 0);

    cout << fixed << setprecision(5) << result << endl;

    return 0;
}
