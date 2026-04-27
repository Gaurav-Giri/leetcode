class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dirs = {
            {},
            {1, 3},
            {0, 2},
            {3, 2},
            {1, 2},
            {3, 0},
            {1, 0}
        };

        vector<int> dx = {-1, 0, 1, 0};
        vector<int> dy = {0, 1, 0, -1};

        vector<vector<bool>> vis(m, vector<bool>(n, false));
        queue<pair<int,int>> q;

        q.push({0, 0});
        vis[0][0] = true;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == m - 1 && y == n - 1) return true;

            for (int dir : dirs[grid[x][y]]) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                if (vis[nx][ny]) continue;

                int opposite = (dir + 2) % 4;

                // check if next cell connects back
                for (int d : dirs[grid[nx][ny]]) {
                    if (d == opposite) {
                        vis[nx][ny] = true;
                        q.push({nx, ny});
                        break;
                    }
                }
            }
        }

        return false;
    }
};
