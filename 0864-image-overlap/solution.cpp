class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        vector<pair<int, int>> ones1;
        vector<pair<int, int>> ones2;
        
        // 1. Collect coordinates of all 1s in both images
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (img1[i][j] == 1) ones1.push_back({i, j});
                if (img2[i][j] == 1) ones2.push_back({i, j});
            }
        }
        
        // 2. Count the frequency of each translation vector (dx, dy)
        // Since N <= 30, we can uniquely encode the vector as: (dx + 30) * 100 + (dy + 30)
        unordered_map<int, int> transformCount;
        int maxOverlap = 0;
        
        for (auto& p1 : ones1) {
            for (auto& p2 : ones2) {
                int dx = p2.first - p1.first;
                int dy = p2.second - p1.second;
                
                int vectorKey = (dx + 30) * 100 + (dy + 30);
                transformCount[vectorKey]++;
                
                maxOverlap = max(maxOverlap, transformCount[vectorKey]);
            }
        }
        
        return maxOverlap;
    }
};

