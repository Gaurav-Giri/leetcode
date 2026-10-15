#include <vector>
#include <unordered_set>

class Solution {
public:
    int sumCounts(std::vector<int>& nums) {
        int totalSum = 0;
        int n = nums.size();

        // Iterate through all possible starting positions of subarrays
        for (int i = 0; i < n; ++i) {
            std::unordered_set<int> uniqueElements;
            
            // Expand the subarray from index i to j
            for (int j = i; j < n; ++j) {
                uniqueElements.insert(nums[j]); // Track unique elements incrementally
                
                int distinctCount = uniqueElements.size();
                totalSum += distinctCount * distinctCount; // Add the square of distinct count
            }
        }

        return totalSum;
    }
};

