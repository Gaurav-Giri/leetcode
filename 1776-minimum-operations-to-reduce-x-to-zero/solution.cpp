#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int minOperations(std::vector<int>& nums, int x) {
        int n = nums.size();
        
        // Calculate the total sum of the array
        int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        
        // The target sum for our middle subarray
        int target = totalSum - x;
        
        // Edge cases
        if (target == 0) return n; // Must remove all elements
        if (target < 0) return -1; // Total sum is less than x, impossible
        
        int maxLen = -1;
        int currentSum = 0;
        int left = 0;
        
        // Sliding window to find the longest subarray summing to 'target'
        for (int right = 0; right < n; ++right) {
            currentSum += nums[right];
            
            // Shrink the window from the left if currentSum exceeds target
            while (currentSum > target && left <= right) {
                currentSum -= nums[left];
                left++;
            }
            
            // Check if we hit the target sum
            if (currentSum == target) {
                maxLen = std::max(maxLen, right - left + 1);
            }
        }
        
        // If maxLen remains -1, no valid subarray was found
        return (maxLen == -1) ? -1 : (n - maxLen);
    }
};

