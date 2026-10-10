#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        
        // Find the maximum difference to size our bucket array
        int maxDiff = 0;
        vector<int> diffs(n);
        for (int i = 0; i < n; ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diffs[i]);
        }
        
        // If maxDiff is 0, no changes are needed
        if (maxDiff == 0) return 0;
        
        // Create a frequency bucket for differences
        vector<long long> bucket(maxDiff + 1, 0);
        for (int d : diffs) {
            bucket[d]++;
        }
        
        // Greedily reduce the largest differences down
        for (int d = maxDiff; d > 0; --d) {
            if (bucket[d] == 0) continue;
            
            // If we have enough k to reduce all elements with current difference 'd' to 'd-1'
            if (k >= bucket[d]) {
                k -= bucket[d];
                bucket[d - 1] += bucket[d];
                bucket[d] = 0;
            } else {
                // We can only reduce 'k' elements out of 'bucket[d]' down to 'd-1'
                bucket[d - 1] += k;
                bucket[d] -= k;
                k = 0;
                break; // Out of operations
            }
        }
        
        // Calculate the minimum sum of squared differences
        long long minSquaredSum = 0;
        for (long long d = 1; d <= maxDiff; ++d) {
            if (bucket[d] > 0) {
                minSquaredSum += bucket[d] * (d * d);
            }
        }
        
        return minSquaredSum;
    }
};

