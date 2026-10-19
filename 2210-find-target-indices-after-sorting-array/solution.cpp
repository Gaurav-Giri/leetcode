#include <vector>

class Solution {
public:
    std::vector<int> targetIndices(std::vector<int>& nums, int target) {
        int less_than_target = 0;
        int equal_to_target = 0;
        
        // Count elements smaller than and equal to target
        for (int num : nums) {
            if (num < target) {
                less_than_target++;
            } else if (num == target) {
                equal_to_target++;
            }
        }
        
        // Populate the resulting indices sequentially
        std::vector<int> result;
        for (int i = 0; i < equal_to_target; ++i) {
            result.push_back(less_than_target + i);
        }
        
        return result;
    }
};

