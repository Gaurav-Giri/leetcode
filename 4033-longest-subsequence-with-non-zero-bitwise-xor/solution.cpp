#include <vector>

class Solution {
public:
    int longestSubsequence(std::vector<int>& nums) {
        int xorSum = 0;
        bool hasNonZero = false;
        int n = nums.size();
        
        for (int x : nums) {
            xorSum ^= x;
            if (x != 0) {
                hasNonZero = true;
            }
        }
        
        if (xorSum != 0) {
            return n;
        }
        return hasNonZero ? n - 1 : 0;
    }
};

