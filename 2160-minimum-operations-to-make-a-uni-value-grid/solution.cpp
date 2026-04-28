class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> arr;

        // setp1: flatten
        for (auto &row : grid){
            for (int val : row){
                arr.push_back(val);
            }
        }

        // step2: check feasibility
        int base = arr[0];
        for (int val : arr){
            if ((val - base) % x  != 0)
            return -1;
        }

        // step3: normalise
        for (int &val : arr){
            val /= x;
        }

        // step4: sort
        sort(arr.begin(), arr.end());

        // step5: median
        int median = arr[arr.size() / 2];

        // step6: count operations
        int ops = 0;
        for (int val : arr){
            ops += abs(val - median);
        }

        return ops;
    }
};
