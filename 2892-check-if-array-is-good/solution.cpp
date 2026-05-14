class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = *max_element(nums.begin(), nums.end());

        // Length must be n + 1
        if (nums.size() != n + 1)
            return false;

        vector<int> freq(n + 1, 0);

        for (int x : nums) {
            if (x > n)
                return false;
            freq[x]++;
        }

        // Numbers 1 to n-1 must appear exactly once
        for (int i = 1; i < n; i++) {
            if (freq[i] != 1)
                return false;
        }

        // Number n must appear exactly twice
        return freq[n] == 2;
    }
};
