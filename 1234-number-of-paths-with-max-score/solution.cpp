class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1e9 + 7;

        vector<vector<int>> dp(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        dp[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X') continue;
                if (i == n - 1 && j == n - 1) continue;

                int best = -1;
                long long cnt = 0;

                // From below
                if (i + 1 < n && dp[i + 1][j] != -1) {
                    if (dp[i + 1][j] > best) {
                        best = dp[i + 1][j];
                        cnt = ways[i + 1][j];
                    } else if (dp[i + 1][j] == best) {
                        cnt = (cnt + ways[i + 1][j]) % MOD;
                    }
                }

                // From right
                if (j + 1 < n && dp[i][j + 1] != -1) {
                    if (dp[i][j + 1] > best) {
                        best = dp[i][j + 1];
                        cnt = ways[i][j + 1];
                    } else if (dp[i][j + 1] == best) {
                        cnt = (cnt + ways[i][j + 1]) % MOD;
                    }
                }

                // From diagonal
                if (i + 1 < n && j + 1 < n && dp[i + 1][j + 1] != -1) {
                    if (dp[i + 1][j + 1] > best) {
                        best = dp[i + 1][j + 1];
                        cnt = ways[i + 1][j + 1];
                    } else if (dp[i + 1][j + 1] == best) {
                        cnt = (cnt + ways[i + 1][j + 1]) % MOD;
                    }
                }

                if (best == -1) continue;

                dp[i][j] = best;
                if (board[i][j] != 'E' && board[i][j] != 'S')
                    dp[i][j] += board[i][j] - '0';

                ways[i][j] = cnt % MOD;
            }
        }

        if (dp[0][0] == -1)
            return {0, 0};

        return {dp[0][0], ways[0][0]};
    }
};
