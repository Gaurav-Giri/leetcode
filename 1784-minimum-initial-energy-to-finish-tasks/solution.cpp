class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Sort tasks by (minimum - actual) in descending order
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });
        
        long long totalActual = 0;
        long long minInitial = 0;
        
        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];
            // The energy needed before starting this task
            long long required = minimum + totalActual;
            if (required > minInitial) {
                minInitial = required;
            }
            totalActual += actual;
        }
        
        return (int)minInitial;
    }
};
