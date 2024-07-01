#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Vertex {
    int index;
    int abscissa;
    int ordinate;
};

bool compare_x(Vertex vertex1, Vertex vertex2) {
    return vertex1.abscissa < vertex2.abscissa;
}

bool compare_y(Vertex vertex1, Vertex vertex2) {
    return vertex1.ordinate < vertex2.ordinate;
}

void dijkstra(const vector<vector<pair<int, int>>>& adjacency_list, int start, vector<int>& distance) {
    distance[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    vector<bool> visited(distance.size(), false); 

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        if (dist > distance[u] || visited[u])
            continue;

        visited[u] = true;

        for (int i = 0; i < adjacency_list[u].size(); ++i) {
            int v = adjacency_list[u][i].first;
            int weight = adjacency_list[u][i].second;
            if (!visited[v] && distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }
}


int main() {
    int n, s, d;
    cin >> n;
    vector<Vertex> vertices(n);
    for (int i = 0; i < n; i++) {
        cin >> vertices[i].abscissa >> vertices[i].ordinate;
        vertices[i].index = i;
    }
    cin >> s >> d;


    sort(vertices.begin(), vertices.end(), compare_x);


    vector<vector<pair<int, int>>> adjacency_list(n);
    for (int i = 0; i < n - 1; i++) {
        int weight = vertices[i + 1].abscissa - vertices[i].abscissa;
        adjacency_list[vertices[i].index].push_back({vertices[i + 1].index, weight});
        adjacency_list[vertices[i + 1].index].push_back({vertices[i].index, weight});
    }


    sort(vertices.begin(), vertices.end(), compare_y);


    for (int i = 0; i < n - 1; i++) {
        int weight = vertices[i + 1].ordinate - vertices[i].ordinate;
        int u = vertices[i].index;
        int v = vertices[i + 1].index;
        bool found = false;


        for (int i = 0; i < adjacency_list[u].size(); ++i) {
            if (adjacency_list[u][i].first == v) {
                found = true;
                if (weight < adjacency_list[u][i].second) {
                    adjacency_list[u][i].second = weight;
                }
                break;
            }
        }


        if (!found) {
            adjacency_list[u].push_back({v, weight});
            adjacency_list[v].push_back({u, weight});
        }
    }


    vector<int> distance(n, 100000000);
    dijkstra(adjacency_list, s, distance);


    cout << distance[d] << endl;

    return 0;
}
