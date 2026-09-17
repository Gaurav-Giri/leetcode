class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        // dp[i] will store the minimum length of a subarray summing to target found in arr[0...i]
        vector<int> dp(n, INT_MAX);
        
        int min_total_sum = INT_MAX;
        int current_sum = 0;
        int left = 0;
        int min_len_so_far = INT_MAX;

        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];

            // Shrink the window if the current sum exceeds the target
            while (current_sum > target) {
                current_sum -= arr[left];
                left++;
            }

            // If we found a subarray that sums exactly to target
            if (current_sum == target) {
                int current_len = right - left + 1;

                // Check if a valid non-overlapping subarray exists to the left
                if (left > 0 && dp[left - 1] != INT_MAX) {
                    min_total_sum = min(min_total_sum, dp[left - 1] + current_len);
                }

                // Update the minimum length found up to the current window
                min_len_so_far = min(min_len_so_far, current_len);
            }

            // dp[right] maintains the smallest length found so far up to index right
            dp[right] = min_len_so_far;
        }

        return min_total_sum == INT_MAX ? -1 : min_total_sum;
    }
};

