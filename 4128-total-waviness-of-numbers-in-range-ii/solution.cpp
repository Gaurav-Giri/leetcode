class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;
    Node memo[16][2][3][10][10];
    bool vis[16][2][3][10][10];

    Node dfs(int pos, int tight, int state, int last2, int last1) {
        if (pos == (int)s.size())
            return {1, 0};

        if (!tight && vis[pos][0][state][last2][last1])
            return memo[pos][0][state][last2][last1];

        int limit = tight ? s[pos] - '0' : 9;

        Node res{0, 0};

        for (int d = 0; d <= limit; d++) {
            int ntight = tight && (d == limit);

            if (state == 0) {
                Node nxt;

                if (d == 0)
                    nxt = dfs(pos + 1, ntight, 0, 0, 0);
                else
                    nxt = dfs(pos + 1, ntight, 1, 0, d);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            }
            else if (state == 1) {
                Node nxt = dfs(pos + 1, ntight, 2, last1, d);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            }
            else {
                int add =
                    ((last1 > last2 && last1 > d) ||
                     (last1 < last2 && last1 < d));

                Node nxt = dfs(pos + 1, ntight, 2, last1, d);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav + nxt.cnt * add;
            }
        }

        if (!tight) {
            vis[pos][0][state][last2][last1] = true;
            memo[pos][0][state][last2][last1] = res;
        }

        return res;
    }

    long long solve(long long n) {
        if (n < 0) return 0;

        s = to_string(n);
        memset(vis, 0, sizeof(vis));

        return dfs(0, 1, 0, 0, 0).wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
