class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        // Build the adjacency list for the directed graph
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // Distance table track minimum cost for state: dist[node][consecutive_count]
        // consecutive_count ranges from 1 to k.
        vector<vector<int>> dist(n, vector<int>(k + 1, 1e9));

        // Min-heap priority queue stores: {cost, current_node, consecutive_count}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

        // Base case: starting at node 0 has cost 0 and a label sequence length of 1
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, consec] = pq.top();
            pq.pop();

            // If we found a path to the destination node, it's guaranteed to be the shortest
            if (u == n - 1) {
                return cost;
            }

            // Skip outdated states
            if (cost > dist[u][consec]) {
                continue;
            }

            // Traverse neighbors
            for (const auto& [v, weight] : adj[u]) {
                int next_consec = (labels[u] == labels[v]) ? consec + 1 : 1;

                // Check if the run of identical consecutive labels remains within valid bound k
                if (next_consec <= k) {
                    if (cost + weight < dist[v][next_consec]) {
                        dist[v][next_consec] = cost + weight;
                        pq.push({dist[v][next_consec], v, next_consec});
                    }
                }
            }
        }

        return -1;
    }
};

