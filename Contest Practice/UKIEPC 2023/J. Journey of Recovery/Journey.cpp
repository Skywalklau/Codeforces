#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using Flight = tuple<string, int, string, int>;

int parse_time(const string& s) {
    int d, h, m;
    sscanf(s.c_str(), "%dd%2d:%2d", &d, &h, &m);
    return d * 24 * 60 + h * 60 + m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Flight> flights(n);
    unordered_map<string, set<int>> times; // airport -> interesting times
    vector<tuple<string, int, string, int>> edges; // flight edges

    for (int i = 0; i < n; ++i) {
        string from, t1, to, t2;
        cin >> from >> t1 >> to >> t2;
        int dep = parse_time(t1);
        int arr = parse_time(t2);
        flights[i] = {from, dep, to, arr};
        times[from].insert(dep);
        times[to].insert(arr);
    }

    // Itinerary
    int m;
    cin >> m;
    vector<int> itinerary(m);
    for (int i = 0; i < m; ++i) {
        cin >> itinerary[i];
        itinerary[i]--;
    }

    // Determine final arrival time and destination
    auto [_, __, final_dest, final_arrival] = flights[itinerary.back()];

    // Assign node ids to (airport, time)
    unordered_map<string, map<int, int>> node_ids;
    int node_cnt = 0;
    for (auto& [airport, tset] : times) {
        for (int t : tset) {
            node_ids[airport][t] = node_cnt++;
        }
    }

    vector<vector<int>> rev_graph(node_cnt);
    vector<int> node_time(node_cnt); // time of each node
    vector<string> node_airport(node_cnt); // airport of each node

    for (auto& [airport, tmap] : node_ids) {
        for (auto& [t, id] : tmap) {
            node_time[id] = t;
            node_airport[id] = airport;
        }
    }

    // Add wait edges
    for (auto& [airport, tmap] : node_ids) {
        vector<int> tids;
        for (auto& [t, id] : tmap) tids.push_back(t);
        for (size_t i = 0; i + 1 < tids.size(); ++i) {
            int u = node_ids[airport][tids[i + 1]];
            int v = node_ids[airport][tids[i]];
            rev_graph[u].push_back(v); // reverse edge
        }
    }

    // Add flight edges (reversed)
    for (auto& [from, dep, to, arr] : flights) {
        int u = node_ids[to][arr];
        int v = node_ids[from][dep];
        rev_graph[u].push_back(v); // reverse edge
    }

    // Earliest time to reach destination from node
    vector<int> earliest(node_cnt, INT_MAX);
    vector<bool> visited(node_cnt, false);

    function<void(int)> dfs = [&](int u) {
        if (visited[u]) return;
        visited[u] = true;
        for (int v : rev_graph[u]) {
            dfs(v);
        }
    };

    // Start DFS from all destination nodes
    for (auto& [t, id] : node_ids[final_dest]) {
        dfs(id);
    }

    // Annotate reachable nodes with earliest arrival
    queue<int> q;
    for (auto& [t, id] : node_ids[final_dest]) {
        earliest[id] = t;
        q.push(id);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : rev_graph[u]) {
            if (earliest[v] > earliest[u]) {
                earliest[v] = earliest[u];
                q.push(v);
            }
        }
    }

    // Evaluate each flight cancellation
    int max_delay = 0;
    bool possible = true;
    for (int idx : itinerary) {
        auto [from, dep, to, arr] = flights[idx];
        auto it = node_ids[from].lower_bound(dep);
        if (it == node_ids[from].end()) {
            possible = false;
            break;
        }
        int id = it->second;
        if (earliest[id] == INT_MAX) {
            possible = false;
            break;
        }
        max_delay = max(max_delay, earliest[id] - final_arrival);
    }

    if (!possible) cout << "stranded\n";
    else cout << max(0, max_delay) << '\n';
}
