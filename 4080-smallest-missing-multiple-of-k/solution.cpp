class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        // Step 1: Track existing elements using a boolean vector
        // Fixed size of 101 because problem constraints state nums[i] <= 100
        vector<bool> present(101, false);
        for (int num : nums) {
            present[num] = true;
        }
        
        // Step 2: Iterate through consecutive positive multiples of k
        int multiple = k;
        while (multiple <= 100 && present[multiple]) {
            multiple += k;
        }
        
        // Step 3: Return the first multiple that is missing
        return multiple;
    }
};

