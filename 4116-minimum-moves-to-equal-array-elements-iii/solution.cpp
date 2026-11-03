class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int max_val = 0;
        long long sum = 0;
        
        // Find the maximum value and the sum of all elements
        for (int num : nums) {
            if (num > max_val) {
                max_val = num;
            }
            sum += num;
        }
        
        // Total moves needed to make all elements equal to max_val
        return (1LL * max_val * n) - sum;
    }
};

