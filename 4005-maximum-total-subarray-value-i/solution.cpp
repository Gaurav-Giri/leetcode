class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        long long mx = LLONG_MIN;
        long long mn = LLONG_MAX;

        for (int x : nums) {
            mx = max(mx, (long long)x);
            mn = min(mn, (long long)x);
        }

        return 1LL * k * (mx - mn);
    }
};
