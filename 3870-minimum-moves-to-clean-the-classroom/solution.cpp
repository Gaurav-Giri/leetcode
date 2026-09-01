class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startX = -1, startY = -1;
        vector<pair<int, int>> litterPositions;
        
        // Locate the starting position and map all litter spots
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    startX = i;
                    startY = j;
                } else if (classroom[i][j] == 'L') {
                    litterPositions.push_back({i, j});
                }
            }
        }
        
        int totalLitter = litterPositions.size();
        int targetMask = (1 << totalLitter) - 1;
        
        // Helper lambda to find the index of a litter spot
        auto getLitterIndex = [&](int r, int c) {
            for (int i = 0; i < totalLitter; ++i) {
                if (litterPositions[i].first == r && litterPositions[i].second == c) {
                    return i;
                }
            }
            return -1;
        };

        // 4D Visited tracking array: visited[x][y][current_energy][litter_mask]
        vector<vector<vector<vector<bool>>>> visited(
            m, vector<vector<vector<bool>>>(
                n, vector<vector<bool>>(
                    energy + 1, vector<bool>(1 << totalLitter, false)
                )
            )
        );
        
        // Queue stores: {x, y, curr_energy, mask, moves}
        queue<tuple<int, int, int, int, int>> q; 
        
        // Handle edge case where start position 'S' is also a litter item
        int initialMask = 0;
        int initialIdx = getLitterIndex(startX, startY);
        if (initialIdx != -1) {
            initialMask |= (1 << initialIdx);
        }
        
        q.push({startX, startY, energy, initialMask, 0});
        visited[startX][startY][energy][initialMask] = true;
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [x, y, curr_energy, mask, moves] = q.front();
            q.pop();
            
            // Goal: All pieces of litter collected
            if (mask == targetMask) {
                return moves;
            }
            
            // Cannot move forward if out of energy and not standing on a reset pad
            if (curr_energy == 0 && classroom[x][y] != 'R') {
                continue;
            }
            
            // Move in 4 directions
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                // Boundary check and wall/obstacle avoidance ('X')
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                    
                    int next_energy = curr_energy - 1; 
                    
                    // Instantly reset energy back to max capacity on 'R'
                    if (classroom[nx][ny] == 'R') {
                        next_energy = energy;
                    }
                    
                    int next_mask = mask;
                    if (classroom[nx][ny] == 'L') {
                        int lIdx = getLitterIndex(nx, ny);
                        if (lIdx != -1) {
                            next_mask |= (1 << lIdx);
                        }
                    }
                    
                    // Push valid unvisited states to the queue
                    if (next_energy >= 0 && !visited[nx][ny][next_energy][next_mask]) {
                        visited[nx][ny][next_energy][next_mask] = true;
                        q.push({nx, ny, next_energy, next_mask, moves + 1});
                    }
                }
            }
        }
        
        return -1; // Return -1 if it is impossible to clean the entire classroom
    }
};

