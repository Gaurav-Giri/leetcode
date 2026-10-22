class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        
        // Find the index of 0
        int zero = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }
        
        // Check if it's cyclically increasing (Ascending starting from 0)
        auto check = [&](int step) -> bool {
            for (int i = 1; i < n; i++) {
                int prev = (zero + (i - 1) * step + n) % n;
                int curr = (zero + i * step + n) % n;
                if (nums[prev] > nums[curr]) {
                    return false;
                }
            }
            return true;
        };
        
        int ans = INT_MAX;
        
        // Case 1: Elements increase strictly by 1 mod n starting from 'zero'
        if (check(1)) {
            ans = min(ans, zero);            // Only left shifts
            ans = min(ans, n - zero + 2);    // Reverse -> left shifts -> reverse
        }
        
        // Case 2: Elements decrease strictly by 1 mod n starting from 'zero'
        if (check(-1)) {
            ans = min(ans, zero + 2);        // Reverse -> left shifts -> reverse
            ans = min(ans, n - zero);        // Left shifts -> reverse
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};

