#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // dp[i][j] stores a bitset where the k-th bit is true 
        // if a XOR path value of k is reachable at cell (i, j)
        vector<vector<bitset<1024>>> dp(m, vector<bitset<1024>>(n));
        
        // Initialize the starting cell
        dp[0][0].set(grid[0][0]);
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                
                // Collect all reachable XOR values from the top and left cells
                bitset<1024> incoming;
                if (i > 0) incoming |= dp[i - 1][j];
                if (j > 0) incoming |= dp[i][j - 1];
                
                int current_val = grid[i][j];
                
                // Transition: if 'k' was reachable, 'k ^ current_val' is now reachable
                for (int k = 0; k < 1024; ++k) {
                    if (incoming.test(k)) {
                        dp[i][j].set(k ^ current_val);
                    }
                }
            }
        }
        
        // Find the smallest set bit at the destination cell (m-1, n-1)
        for (int k = 0; k < 1024; ++k) {
            if (dp[m - 1][n - 1].test(k)) {
                return k;
            }
        }
        
        return 0;
    }
};

