class Solution {
public:
    int m, n;
    vector<vector<int>> vis;
    
    bool dfs(int x, int y, int px, int py, vector<vector<char>>& grid) {
        vis[x][y] = 1;
        
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        
        for(auto &d : dirs) {
            int nx = x + d[0];
            int ny = y + d[1];
            
            if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
            if(grid[nx][ny] != grid[x][y]) continue;
            
            // If not visited → continue DFS
            if(!vis[nx][ny]) {
                if(dfs(nx, ny, x, y, grid)) return true;
            }
            // If visited and not parent → cycle found
            else if(nx != px || ny != py) {
                return true;
            }
        }
        
        return false;
    }
    
    bool containsCycle(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        vis.assign(m, vector<int>(n, 0));
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(!vis[i][j]) {
                    if(dfs(i, j, -1, -1, grid)) return true;
                }
            }
        }
        
        return false;
    }
};
