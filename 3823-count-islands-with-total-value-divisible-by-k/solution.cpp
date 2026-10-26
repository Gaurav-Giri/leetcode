#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to perform DFS and accumulate the island's total value
    long long dfs(int r, int c, vector<vector<int>>& grid, int m, int n) {
        // Base case: check boundary limits and if the cell is water (0)
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
            return 0;
        }

        // Add current cell value to the island total
        long long current_val = grid[r][c];

        // Mark the current cell as visited by setting it to 0 (water)
        // This avoids using an extra visited array, saving space
        grid[r][c] = 0;

        // Explore all 4 cardinal directions
        long long total = current_val;
        total += dfs(r + 1, c, grid, m, n); // Down
        total += dfs(r - 1, c, grid, m, n); // Up
        total += dfs(r, c + 1, grid, m, n); // Right
        total += dfs(r, c - 1, grid, m, n); // Left

        return total;
    }

public:
    int countIslands(vector<vector<int>>& grid, int k) {
        if (grid.empty() || grid[0].empty()) return 0;

        int m = grid.size();
        int n = grid[0].size();
        int divisibleIslandsCount = 0;

        // Traverse every cell in the grid
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // If a land cell (> 0) is found, it's a new island
                if (grid[i][j] > 0) {
                    // Compute the total sum of this island using DFS
                    long long islandSum = dfs(i, j, grid, m, n);

                    // Check if the total value is divisible by k
                    if (islandSum % k == 0) {
                        divisibleIslandsCount++;
                    }
                }
            }
        }

        return divisibleIslandsCount;
    }
};

