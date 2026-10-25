class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int count = 0;

        // Helper lambda for Depth-First Search to sink the island
        auto dfs = [&](auto& self, int r, int c) -> void {
            if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 1) {
                return;
            }
            grid[r][c] = 1; // Mark as visited by turning land to water
            self(self, r + 1, c);
            self(self, r - 1, c);
            self(self, r, c + 1);
            self(self, r, c - 1);
        };

        // Step 1: Eliminate all land connected to the boundary
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && grid[r][c] == 0) {
                    dfs(dfs, r, c);
                }
            }
        }

        // Step 2: Count the remaining closed islands
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) {
                    count++;
                    dfs(dfs, r, c); // Sink this island so it isn't counted again
                }
            }
        }

        return count;
    }
};

