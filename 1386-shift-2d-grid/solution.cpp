class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        k %= total;

        vector<int> shifted(total);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int oldIndex = i * n + j;
                int newIndex = (oldIndex + k) % total;
                shifted[newIndex] = grid[i][j];
            }
        }

        vector<vector<int>> ans(m, vector<int>(n));

        for (int idx = 0; idx < total; idx++) {
            ans[idx / n][idx % n] = shifted[idx];
        }

        return ans;
    }
};
