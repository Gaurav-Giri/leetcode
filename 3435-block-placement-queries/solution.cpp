class Solution {
public:
    struct FenwickMax {
        int n;
        vector<int> bit;

        FenwickMax(int n) : n(n), bit(n + 1, 0) {}

        void update(int idx, int val) {
            for (++idx; idx <= n; idx += idx & -idx)
                bit[idx] = max(bit[idx], val);
        }

        int query(int idx) {
            int res = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                res = max(res, bit[idx]);
            return res;
        }
    };

    vector<bool> getResults(vector<vector<int>>& queries) {
        const int MAXX = 50000;

        set<int> obstacles;
        obstacles.insert(0);

        // Build final obstacle configuration
        for (auto &q : queries) {
            if (q[0] == 1)
                obstacles.insert(q[1]);
        }

        FenwickMax bit(MAXX + 2);

        int last = 0;
        for (auto it = next(obstacles.begin()); it != obstacles.end(); ++it) {
            int p = *it;
            bit.update(p, p - last);
            last = p;
        }

        vector<bool> ans;

        for (int i = (int)queries.size() - 1; i >= 0; --i) {
            auto &q = queries[i];

            if (q[0] == 2) {
                int x = q[1];
                int sz = q[2];

                auto it = obstacles.upper_bound(x);
                --it;

                int lastObstacle = *it;

                int bestGap = max(bit.query(x), x - lastObstacle);

                ans.push_back(bestGap >= sz);
            } else {
                int p = q[1];

                auto it = obstacles.find(p);
                auto itPrev = std::prev(it);
                auto itNext = std::next(it);

                if (itNext != obstacles.end()) {
                    int prv = *itPrev;
                    int nxt = *itNext;

                    // Gap ending at nxt becomes larger after removing p
                    bit.update(nxt, nxt - prv);
                }

                obstacles.erase(it);
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};
