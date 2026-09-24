class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            int currentNumber = nums[i];
            int digitSum = 0;
            
            // Calculate the sum of digits
            while (currentNumber > 0) {
                digitSum += currentNumber % 10;
                currentNumber /= 10;
            }
            
            // If the element was 0, digitSum will naturally be 0
            if (digitSum == i) {
                return i; // Returns the first (smallest) valid index found
            }
        }
        return -1; // Return -1 if no index satisfies the condition
    }
};

