class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // dp[j] stores the number of distinct subsequences of t[0...j-1]
        // Initialize with 0s, and dp[0] = 1 because there is 1 way to match an empty t
        vector<unsigned long long> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= m; i++) {
            // Traverse backwards to use values from the previous row iteration
            for (int j = n; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    // If characters match, we add the ways without using s[i-1] (dp[j])
                    // and the ways using s[i-1] (dp[j-1])
                    dp[j] += dp[j - 1];
                }
            }
        }
        
        return dp[n];
    }
};

