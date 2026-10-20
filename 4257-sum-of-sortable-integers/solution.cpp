#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int total_sum = 0;
        
        // Find all valid divisors of n
        vector<int> divisors;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) {
                    divisors.push_back(n / i);
                }
            }
        }
        
        // Validate each candidate k
        for (int k : divisors) {
            if (isValid(nums, n, k)) {
                total_sum += k;
            }
        }
        
        return total_sum;
    }

private:
    bool isValid(const vector<int>& nums, int n, int k) {
        int prev_max = -1; // Keeps track of the maximum value from the previous block
        
        for (int i = 0; i < n; i += k) {
            int desc_counts = 0;
            int min_val = nums[i];
            int max_val = nums[i];
            
            // Step 1: Analyze the current subarray block circularly
            for (int j = 0; j < k; ++j) {
                int curr = nums[i + j];
                int next = nums[i + (j + 1) % k]; // Circular wrap-around tracking
                
                if (curr > next) {
                    desc_counts++;
                }
                min_val = min(min_val, curr);
                max_val = max(max_val, curr);
            }
            
            // A subarray block cannot be sorted via cyclic rotation if it has > 1 decreasing step
            if (desc_counts > 1) {
                return false;
            }
            
            // Step 2: Verify block continuity (The entire array must end up globally sorted)
            if (desc_counts == 1) {
                // If there's 1 drop, the element right after the drop represents the block's true minimum after rotation
                for (int j = 0; j < k; ++j) {
                    if (nums[i + j] > nums[i + (j + 1) % k]) {
                        int block_min = nums[i + (j + 1) % k];
                        if (block_min < prev_max) return false;
                        break;
                    }
                }
            } else {
                // desc_counts == 0 means the block is perfectly sorted or all elements are identical
                if (min_val < prev_max) {
                    return false;
                }
            }
            
            prev_max = max_val;
        }
        
        return true;
    }
};

