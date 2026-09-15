class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.length();
        // dp[i] stores the maximum number of non-overlapping palindromes 
        // that can be formed using the prefix substring s[0...i-1]
        vector<int> dp(n + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            // By default, the result up to the next character carries over the current max
            dp[i + 1] = max(dp[i + 1], dp[i]);
            
            // Check for both Odd and Even length palindromes centered around 'i'
            for (int change = 0; change <= 1; ++change) {
                int left = i;
                int right = i + change;
                
                // Expand outward from the center
                while (left >= 0 && right < n && s[left] == s[right]) {
                    int len = right - left + 1;
                    
                    // If we found a valid palindrome of length >= k
                    if (len >= k) {
                        dp[right + 1] = max(dp[right + 1], dp[left] + 1);
                        // Greedy choice: break early because any further expansion 
                        // creates a longer palindrome, which is suboptimal.
                        break; 
                    }
                    left--;
                    right++;
                }
            }
        }
        
        return dp[n];
    }
};

