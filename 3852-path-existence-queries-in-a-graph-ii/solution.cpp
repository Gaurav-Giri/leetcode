class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> v;
        v.reserve(n);

        for (int i = 0; i < n; i++) {
            v.push_back({nums[i], i});
        }

        sort(v.begin(), v.end());

        vector<int> posInSorted(n);
        vector<int> values(n);

        for (int i = 0; i < n; i++) {
            values[i] = v[i].first;
            posInSorted[v[i].second] = i;
        }

        // Component IDs
        vector<int> comp(n);
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            comp[i] = comp[i - 1];
            if (values[i] - values[i - 1] > maxDiff) {
                comp[i]++;
            }
        }

        // nxt[i] = furthest sorted position reachable in one edge to the right
        vector<int> nxt(n);
        int r = 0;

        for (int l = 0; l < n; l++) {
            while (r + 1 < n && values[r + 1] - values[l] <= maxDiff) {
                r++;
            }
            nxt[l] = r;
        }

        int LOG = 18; // 2^17 > 1e5
        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (auto &q : queries) {
            int u = q[0];
            int vtx = q[1];

            if (u == vtx) {
                answer.push_back(0);
                continue;
            }

            int p1 = posInSorted[u];
            int p2 = posInSorted[vtx];

            if (p1 > p2) swap(p1, p2);

            // Different connected components
            if (comp[p1] != comp[p2]) {
                answer.push_back(-1);
                continue;
            }

            int cur = p1;
            int dist = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < p2) {
                    dist += (1 << k);
                    cur = up[k][cur];
                }
            }

            answer.push_back(dist + 1);
        }

        return answer;
    }
};
