#include <vector>
#include <string>
#include <sstream>

using namespace std;

class FenwickTree {
    int n;
    vector<int> tree;
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    void add(int i, int delta) {
        for (++i; i <= n; i += i & -i) {
            tree[i] ^= delta;
        }
    }

    int query(int i) {
        int sum = 0;
        for (++i; i > 0; i -= i & -i) {
            sum ^= tree[i];
        }
        return sum;
    }

    int query(int l, int r) {
        return query(r) ^ query(l - 1);
    }
};

class Solution {
    int cur_pos;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos;

    int dfs(int v, int p) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != p) {
                depth[c] = depth[v] + 1;
                parent[c] = v;
                int c_size = dfs(c, v);
                size += c_size;
                if (c_size > max_c_size) {
                    max_c_size = c_size;
                    heavy[v] = c;
                }
            }
        }
        return size;
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = cur_pos++;
        if (heavy[v] != -1) {
            decompose(heavy[v], h);
        }
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v]) {
                decompose(c, c);
            }
        }
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        adj.assign(n, vector<int>());
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        parent.assign(n, 0);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        cur_pos = 0;

        dfs(0, -1);
        decompose(0, 0);

        FenwickTree ft(n);
        vector<int> node_mask(n, 0);
        for (int i = 0; i < n; ++i) {
            node_mask[i] = 1 << (s[i] - 'a');
            ft.add(pos[i], node_mask[i]);
        }

        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                
                int new_mask = 1 << (c - 'a');
                // XOR out the old mask value and XOR in the new mask value
                ft.add(pos[u], node_mask[u] ^ new_mask);
                node_mask[u] = new_mask;
            } else if (type == "query") {
                int u, v;
                ss >> u >> v;

                int path_mask = 0;
                while (head[u] != head[v]) {
                    if (depth[head[u]] > depth[head[v]]) {
                        swap(u, v);
                    }
                    path_mask ^= ft.query(pos[head[v]], pos[v]);
                    v = parent[head[v]];
                }
                if (depth[u] > depth[v]) {
                    swap(u, v);
                }
                path_mask ^= ft.query(pos[u], pos[v]);

                // A path forms a palindrome if at most 1 bit is set
                ans.push_back((path_mask & (path_mask - 1)) == 0);
            }
        }

        return ans;
    }
};

