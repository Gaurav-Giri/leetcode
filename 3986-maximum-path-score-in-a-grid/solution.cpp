class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        
        const int NEG = -1e9;

        // dp[j][c] -> current row optimization
        vector<vector<int>> prev(n, vector<int>(k + 1, NEG));
        vector<vector<int>> curr(n, vector<int>(k + 1, NEG));

        prev[0][0] = 0; // starting point

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int c = 0; c <= k; c++) {
                    curr[j][c] = NEG;
                }
            }

            for (int j = 0; j < n; j++) {
                int val = grid[i][j];
                int cost = (val == 0 ? 0 : 1);

                for (int c = cost; c <= k; c++) {
                    int best = NEG;

                    // from top
                    if (i > 0 && prev[j][c - cost] != NEG) {
                        best = max(best, prev[j][c - cost] + val);
                    }

                    // from left
                    if (j > 0 && curr[j-1][c - cost] != NEG) {
                        best = max(best, curr[j-1][c - cost] + val);
                    }

                    // special case for (0,0)
                    if (i == 0 && j == 0 && c == 0) {
                        best = 0;
                    }

                    curr[j][c] = best;
                }
            }

            prev = curr;
        }

        int ans = NEG;
        for (int c = 0; c <= k; c++) {
            ans = max(ans, prev[n-1][c]);
        }

        return (ans < 0 ? -1 : ans);
    }
};
