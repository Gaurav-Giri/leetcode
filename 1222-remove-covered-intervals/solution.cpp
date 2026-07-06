class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {

        // Sort by starting point in ascending order.
        // If starting points are equal, sort by ending point in descending order.
        sort(intervals.begin(), intervals.end(),
            [](vector<int>& a, vector<int>& b) {
                if (a[0] == b[0])
                    return a[1] > b[1];
                return a[0] < b[0];
            });

        int count = 0;
        int maxEnd = 0;

        for (auto &interval : intervals) {
            // If current interval extends beyond all previous intervals,
            // it is not covered.
            if (interval[1] > maxEnd) {
                count++;
                maxEnd = interval[1];
            }
            // Otherwise, it is covered and ignored.
        }

        return count;
    }
};
