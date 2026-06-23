class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int MOD = 1e9 + 7;
        int m = r - l + 1;

        vector<long long> up(m + 2), down(m + 2);
        vector<long long> newUp(m + 2), newDown(m + 2);
        vector<long long> prefixDown(m + 2), suffixUp(m + 3);

        // length = 2
        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;      // previous element < current
            down[v] = m - v;    // previous element > current
        }

        for (int len = 3; len <= n; len++) {

            prefixDown[0] = 0;
            for (int v = 1; v <= m; v++) {
                prefixDown[v] = (prefixDown[v - 1] + down[v]) % MOD;
            }

            suffixUp[m + 1] = 0;
            for (int v = m; v >= 1; v--) {
                suffixUp[v] = (suffixUp[v + 1] + up[v]) % MOD;
            }

            for (int v = 1; v <= m; v++) {
                // current difference positive => previous difference negative
                newUp[v] = prefixDown[v - 1];

                // current difference negative => previous difference positive
                newDown[v] = suffixUp[v + 1];
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;
        for (int v = 1; v <= m; v++) {
            ans += up[v] + down[v];
            ans %= MOD;
        }

        return (int)ans;
    }
};
