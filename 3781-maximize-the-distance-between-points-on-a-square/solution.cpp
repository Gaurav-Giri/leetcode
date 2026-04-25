class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> pos;
        
        // Map to perimeter
        for (auto &p : points) {
            long long x = p[0], y = p[1];
            
            if (y == 0) pos.push_back(x);
            else if (x == side) pos.push_back(side + y);
            else if (y == side) pos.push_back(3LL * side - x);
            else pos.push_back(4LL * side - y);
        }
        
        sort(pos.begin(), pos.end());
        int n = pos.size();
        
        // Extend for circular
        vector<long long> ext = pos;
        for (auto x : pos) ext.push_back(x + 4LL * side);
        
        auto can = [&](long long d) {
            vector<int> next(2 * n);
            
            // Two pointer to build next[]
            int j = 0;
            for (int i = 0; i < 2 * n; i++) {
                while (j < 2 * n && ext[j] - ext[i] < d) j++;
                next[i] = j;
            }
            
            // Try each start
            for (int i = 0; i < n; i++) {
                int cnt = 1;
                int cur = i;
                
                while (cnt < k) {
                    cur = next[cur];
                    if (cur >= i + n) break;
                    cnt++;
                }
                
                if (cnt >= k) {
                    // Check circular constraint
                    if (ext[cur] - ext[i] <= 4LL * side - d)
                        return true;
                }
            }
            
            return false;
        };
        
        long long low = 0, high = 2LL * side, ans = 0;
        
        while (low <= high) {
            long long mid = (low + high) / 2;
            
            if (can(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return (int)ans;
    }
};
