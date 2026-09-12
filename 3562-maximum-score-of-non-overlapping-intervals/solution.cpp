#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Interval {
        int l, r, weight, id;
        bool operator<(const Interval& other) const {
            if (l != other.l) return l < other.l;
            if (r != other.r) return r < other.r;
            return id < other.id;
        }
    };

    struct Result {
        long long weight;
        vector<int> selected;

        // Custom comparator to handle tie-breaking for identical weights
        bool isBetterThan(const Result& other) const {
            if (weight != other.weight) {
                return weight > other.weight;
            }
            return selected < other.selected;
        }
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        
        // Sort intervals by start time
        sort(arr.begin(), arr.end());

        // dp[i][j] stores the best Result considering intervals from i to n-1 with j choices left
        vector<vector<Result>> dp(n + 1, vector<Result>(5, {0, {}}));

        for (int i = n - 1; i >= 0; --i) {
            // Find the first interval that starts strictly after the current interval ends
            // intervals sharing a boundary are considered overlapping (r_i >= l_j)
            int next_idx = n;
            int low = i + 1, high = n - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid].l > arr[i].r) {
                    next_idx = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            for (int j = 1; j <= 4; ++j) {
                // Option 1: Skip the current interval
                Result best = dp[i + 1][j];

                // Option 2: Take the current interval
                Result take = dp[next_idx][j - 1];
                take.weight += arr[i].weight;
                take.selected.push_back(arr[i].id);
                sort(take.selected.begin(), take.selected.end()); // Keep indices sorted for lexicographical comparison

                // Choose the best option between skipping or taking
                if (take.isBetterThan(best)) {
                    best = take;
                }
                
                dp[i][j] = best;
            }
        }

        return dp[0][4].selected;
    }
};

