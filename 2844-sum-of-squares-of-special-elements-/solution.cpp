#include <vector>

class Solution {
public:
    int sumOfSquares(std::vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        
        for (int i = 0; i < n; ++i) {
            // Convert 0-based index to 1-based index
            if (n % (i + 1) == 0) {
                sum += nums[i] * nums[i];
            }
        }
        
        return sum;
    }
};

