class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        // Pair: {digit_sum, original_value}
        vector<pair<int, int>> sortedPairs(n);
        for (int i = 0; i < n; ++i) {
            sortedPairs[i] = {getDigitSum(nums[i]), nums[i]};
        }
        
        // Sort according to problem rules: 
        // 1. Increasing digit sum 
        // 2. Break ties with the smaller value
        sort(sortedPairs.begin(), sortedPairs.end());
        
        // Map each unique value to its intended target index
        unordered_map<int, int> targetIndex;
        for (int i = 0; i < n; ++i) {
            targetIndex[sortedPairs[i].second] = i;
        }
        
        vector<bool> visited(n, false);
        int totalSwaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // Already visited or already at its correct final position
            if (visited[i] || targetIndex[nums[i]] == i) {
                continue;
            }
            
            int cycleSize = 0;
            int curr = i;
            
            // Traverse the cycle structure
            while (!visited[curr]) {
                visited[curr] = true;
                curr = targetIndex[nums[curr]];
                cycleSize++;
            }
            
            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }
        
        return totalSwaps;
    }

private:
    int getDigitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

