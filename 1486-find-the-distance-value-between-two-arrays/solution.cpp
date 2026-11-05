#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d) {
        // Sort arr2 to enable binary search
        std::sort(arr2.begin(), arr2.end());
        int distanceValue = 0;
        
        for (int val : arr1) {
            // Find the first element in arr2 that is >= (val - d)
            auto it = std::lower_bound(arr2.begin(), arr2.end(), val - d);
            
            // If such an element exists and it is <= (val + d), 
            // then it falls within the invalid range [val - d, val + d]
            if (it != arr2.end() && *it <= val + d) {
                continue; // Not a valid distance element, skip it
            }
            
            // If no element in arr2 is within the range, increment the count
            distanceValue++;
        }
        
        return distanceValue;
    }
};

