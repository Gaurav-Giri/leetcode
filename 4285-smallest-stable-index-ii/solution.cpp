class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        
        // right[i] will store the minimum value from index i to n - 1
        vector<int> right(n);
        right[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right[i] = min(right[i + 1], nums[i]);
        }
        
        // left tracks the maximum value from index 0 to i on the fly
        int left = 0; 
        for (int i = 0; i < n; ++i) {
            left = max(left, nums[i]);
            
            // Instability score = max(nums[0..i]) - min(nums[i..n-1])
            if (left - right[i] <= k) {
                return i; // Return the first index that satisfies the condition
            }
        }
        
        return -1; // Return -1 if no such index is found
    }
};

