class Solution {
public:
    int n;
    vector<int> dp;

    int dfs(int i, vector<int>& arr, int d) {
        if (dp[i] != -1)
            return dp[i];

        int ans = 1;

        // Move right
        for (int j = i + 1; j <= min(n - 1, i + d); j++) {

            // Cannot jump further
            if (arr[j] >= arr[i])
                break;

            ans = max(ans, 1 + dfs(j, arr, d));
        }

        // Move left
        for (int j = i - 1; j >= max(0, i - d); j--) {

            // Cannot jump further
            if (arr[j] >= arr[i])
                break;

            ans = max(ans, 1 + dfs(j, arr, d));
        }

        return dp[i] = ans;
    }

    int maxJumps(vector<int>& arr, int d) {

        n = arr.size();
        dp.assign(n, -1);

        int result = 1;

        for (int i = 0; i < n; i++) {
            result = max(result, dfs(i, arr, d));
        }

        return result;
    }
};
