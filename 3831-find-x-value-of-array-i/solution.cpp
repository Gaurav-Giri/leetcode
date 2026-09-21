class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        // dp[r] stores the number of subarrays ending at the current position 
        // whose product modulo k equals r
        vector<long long> dp(k, 0);
        
        for (const int num : nums) {
            vector<long long> newDp(k, 0);
            int numMod = num % k;
            
            // Choice 1: Start a completely new subarray at the current element
            newDp[numMod] = 1;
            
            // Choice 2: Extend all valid previous subarrays to include the current element
            for (int i = 0; i < k; ++i) {
                if (dp[i] > 0) {
                    int newMod = (static_cast<long long>(i) * numMod) % k;
                    newDp[newMod] += dp[i];
                }
            }
            
            // Accumulate the counts of all subarrays ending at this index into our total
            for (int i = 0; i < k; ++i) {
                ans[i] += newDp[i];
            }
            
            dp = std::move(newDp);
        }
        
        return ans;
    }
};

