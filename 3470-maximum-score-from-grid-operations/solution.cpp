
class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Precompute prefix sums for each column to get range sums in O(1)
        // pref[j][i] is the sum of grid[0...i-1][j]
        vector<vector<long long>> pref(n, vector<long long>(n + 1, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                pref[j][i + 1] = pref[j][i] + grid[i][j];
            }
        }

        // dp[j][h][state]
        // state 0: Current height h is >= previous height
        // state 1: Current height h is < previous height
        // Using -1 for uninitialized states
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(n + 1, vector<long long>(2, -1)));

        // Define the recursive DP function
        // j: current column, h: height of black paint in column j-1
        auto solve = [&](auto self, int j, int h, int is_decreasing) -> long long {
            if (j == n) return 0;
            if (dp[j][h][is_decreasing] != -1) return dp[j][h][is_decreasing];

            long long res = 0;

            // Try all possible heights k for the current column j
            for (int k = 0; k <= n; ++k) {
                if (k > h) {
                    // Increasing: column j is taller than j-1
                    // If we were previously decreasing, we don't pick up scores 
                    // from the "valley" until we establish a new trend.
                    long long score = (j > 0 && is_decreasing == 0) ? (pref[j - 1][k] - pref[j - 1][h]) : 0;
                    res = max(res, score + self(self, j + 1, k, 0));
                } else if (k < h) {
                    // Decreasing: column j is shorter than j-1
                    // White cells in column j covered by column j-1's height h score points
                    long long score = pref[j][h] - pref[j][k];
                    res = max(res, score + self(self, j + 1, k, 1));
                } else {
                    // Equal height: no score gain between columns
                    res = max(res, self(self, j + 1, k, 0));
                }
            }
            return dp[j][h][is_decreasing] = res;
        };

        return solve(solve, 0, 0, 0);
    }
};

