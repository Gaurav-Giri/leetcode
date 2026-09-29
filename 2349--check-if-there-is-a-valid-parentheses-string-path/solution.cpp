class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // Fast Pruning: Path length must be even to be balanced.
        // Also, the start must be '(' and the end must be ')'.
        if ((m + n - 1) % 2 != 0 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') {
            return false;
        }
        
        // vis[i][j][k] stores whether the state (i, j, balance=k) has been visited.
        // Maximum balance possible is bounded by (m + n)
        vector<vector<vector<bool>>> vis(m, vector<vector<bool>>(n, vector<bool>(m + n, false)));
        
        return dfs(0, 0, 0, grid, vis, m, n);
    }

private:
    bool dfs(int i, int j, int k, const vector<vector<char>>& grid, 
             vector<vector<vector<bool>>>& vis, int m, int n) {
        
        // Update the bracket balance
        k += (grid[i][j] == '(' ? 1 : -1);
        
        // If balance becomes negative, or if we have already visited this state, return false
        if (k < 0 || vis[i][j][k]) {
            return false;
        }
        
        // Pruning: if remaining steps cannot possibly reduce balance back to 0
        int remaining_steps = (m - 1 - i) + (n - 1 - j);
        if (k > remaining_steps) {
            return false;
        }
        
        // Base case: Reached the bottom-right cell
        if (i == m - 1 && j == n - 1) {
            return k == 0;
        }
        
        // Mark current state as visited
        vis[i][j][k] = true;
        
        // Move Right
        if (j + 1 < n && dfs(i, j + 1, k, grid, vis, m, n)) {
            return true;
        }
        
        // Move Down
        if (i + 1 < m && dfs(i + 1, j, k, grid, vis, m, n)) {
            return true;
        }
        
        return false;
    }
};

