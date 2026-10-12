#include <vector>

class Solution {
public:
    int maxSum(std::vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        // Step 1: Count occurrences of 1s at each bit position (up to 30 bits)
        std::vector<int> bitCounts(31, 0);
        for (int num : nums) {
            for (int i = 0; i < 31; ++i) {
                if ((num >> i) & 1) {
                    bitCounts[i]++;
                }
            }
        }
        
        long long totalMaxSum = 0;
        
        // Step 2: Greedily assemble the k largest numbers
        for (int step = 0; step < k; ++step) {
            long long currentNum = 0;
            for (int i = 0; i < 31; ++i) {
                if (bitCounts[i] > 0) {
                    currentNum |= (1LL << i); // Place the set bit
                    bitCounts[i]--;          // Consume the bit
                }
            }
            // Add the square of the constructed number to the total sum
            totalMaxSum = (totalMaxSum + (currentNum * currentNum) % MOD) % MOD;
        }
        
        return totalMaxSum;
    }
};

