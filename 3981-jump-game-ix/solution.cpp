class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        // suffix_min[i] = min(nums[i..n-1])
        vector<int> suffix_min(n + 1, INT_MAX);
        for (int i = n - 1; i >= 0; --i) {
            suffix_min[i] = min(nums[i], suffix_min[i + 1]);
        }
        
        vector<int> ans(n);
        int prefix_max = INT_MIN;
        int seg_max = INT_MIN;
        int seg_start = 0;
        
        for (int i = 0; i < n; ++i) {
            prefix_max = max(prefix_max, nums[i]);
            seg_max = max(seg_max, nums[i]);
            // Component boundary: no inversions between [0..i] and [i+1..n-1]
            if (i == n - 1 || prefix_max <= suffix_min[i + 1]) {
                // Fill the current component with its maximum value
                for (int j = seg_start; j <= i; ++j) {
                    ans[j] = seg_max;
                }
                // Reset for next component
                seg_start = i + 1;
                seg_max = INT_MIN;
            }
        }
        return ans;
    }
};
