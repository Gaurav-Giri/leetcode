class Solution {
public:
    vector<string> createGrid(int m, int n) {
        // Initialize the grid entirely filled with obstacles '#'
        vector<string> grid(m, string(n, '#'));
        
        // Open up the first row (move all the way right)
        for (int j = 0; j < n; ++j) {
            grid[0][j] = '.';
        }
        
        // Open up the last column (move all the way down)
        for (int i = 0; i < m; ++i) {
            grid[i][n - 1] = '.';
        }
        
        return grid;
    }
};

