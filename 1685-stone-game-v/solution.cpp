#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    int memo[501][501];
    int pref[501];

    // Helper function to get the sum of elements from index i to j
    int getSum(int i, int j) {
        return pref[j + 1] - pref[i];
    }

    int solve(int i, int j, const std::vector<int>& stoneValue) {
        // Base case: Only one stone left, no score can be obtained
        if (i == j) return 0;
        
        // Return already calculated state
        if (memo[i][j] != -1) return memo[i][j];

        int max_score = 0;

        // Try all possible split positions from i to j-1
        for (int k = i; k < j; ++k) {
            int left_sum = getSum(i, k);
            int right_sum = getSum(k + 1, j);

            int current_score = 0;
            if (left_sum < right_sum) {
                // Bob discards right, Alice keeps left
                current_score = left_sum + solve(i, k, stoneValue);
            } else if (left_sum > right_sum) {
                // Bob discards left, Alice keeps right
                current_score = right_sum + solve(k + 1, j, stoneValue);
            } else {
                // Equal sums: Alice chooses the maximum yielding path
                current_score = left_sum + std::max(solve(i, k, stoneValue), solve(k + 1, j, stoneValue));
            }

            max_score = std::max(max_score, current_score);
        }

        return memo[i][j] = max_score;
    }

public:
    int stoneGameV(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Initialize memoization table with -1
        std::fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(int), -1);

        // Precompute prefix sums for O(1) range sum queries
        pref[0] = 0;
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + stoneValue[i];
        }

        return solve(0, n - 1, stoneValue);
    }
};

