class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1; // Initialize with all bits set to 1
        
        for (int i = 0; i < nums.size(); ++i) {
            // Check if the current element is misplaced
            if (nums[i] != i) {
                ans &= nums[i];
            }
        }
        
        // If the array was already sorted, ans remains -1, so we return 0.
        // Otherwise, ans contains the maximum possible valid bitwise AND constraint k.
        return max(ans, 0);
    }
};

