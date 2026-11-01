class Solution {
public:
    int minMoves(vector<int>& nums) {
        long long sum = 0;
        int min_val = INT_MAX;
        
        for (int num : nums) {
            sum += num;
            if (num < min_val) {
                min_val = num;
            }
        }
        
        return sum - (long long)min_val * nums.size();
    }
};

