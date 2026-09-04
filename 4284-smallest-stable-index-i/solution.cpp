class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return -1;

        // Step 1: Precompute suffix minimums
        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);
        }

        // Step 2: Track prefix maximums dynamically and find the first stable index
        int prefixMax = nums[0];
        for (int i = 0; i < n; ++i) {
            prefixMax = max(prefixMax, nums[i]);
            
            // Check the instability score condition
            if (prefixMax - suffixMin[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};

