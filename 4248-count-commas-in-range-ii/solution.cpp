class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        // Iterate through each comma threshold: 1,000, 1,000,000, 1,000,000,000, etc.
        for (long long x = 1000; x <= n; x *= 1000) {
            // All numbers from x to n have at least one comma at this threshold position
            ans += (n - x + 1);
            
            // Prevent integer overflow for the next loop multiplication since n can be up to 10^15
            if (x > LLONG_MAX / 1000) {
                break;
            }
        }
        return ans;
    }
};

