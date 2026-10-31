class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int MOD = 1e9 + 7;
        
        // Space-optimized DP array tracking paths coming from above
        vector<int> dp_down(n, 0);
        int totalPaths = 0;
        
        for (int i = 0; i < m; ++i) {
            int dp_right = 0; // Tracks paths coming from the left cell
            
            for (int j = 0; j < n; ++j) {
                int in_down = dp_down[j];
                int in_right = dp_right;
                
                // Base case: Inject the starting path at the top-left corner
                if (i == 0 && j == 0) {
                    in_down = 1;
                }
                
                // If we reached the destination, record the total incoming paths
                if (i == m - 1 && j == n - 1) {
                    totalPaths = (in_down + in_right) % MOD;
                }
                
                int out_right, out_down;
                if (grid[i][j] == 1) {
                    // Mirror: Swap the incoming path directions
                    out_right = in_down;
                    out_down = in_right;
                } else {
                    // Empty Cell: Merge paths and distribute to both choices
                    int total = (in_down + in_right) % MOD;
                    out_right = total;
                    out_down = total;
                }
                
                // Update DP states for subsequent transitions
                dp_down[j] = out_down;
                dp_right = out_right;
            }
        }
        
        return totalPaths;
    }
};

