class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n; // Edge case: if size is 1 or 2, we must delete all elements

        // Step 1: Find the indices of the minimum and maximum elements
        int minIdx = 0;
        int maxIdx = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[minIdx]) minIdx = i;
            if (nums[i] > nums[maxIdx]) maxIdx = i;
        }

        // Step 2: Ensure minIdx is the smaller index to simplify boundary math
        int leftIdx = min(minIdx, maxIdx);
        int rightIdx = max(minIdx, maxIdx);

        // Option 1: Delete both from the front (up to rightIdx)
        int delFromFront = rightIdx + 1;

        // Option 2: Delete both from the back (up to leftIdx)
        int delFromBack = n - leftIdx;

        // Option 3: Delete leftIdx from front and rightIdx from back
        int delFromBoth = (leftIdx + 1) + (n - rightIdx);

        // Return the minimum of the three strategies
        return min({delFromFront, delFromBack, delFromBoth});
    }
};

