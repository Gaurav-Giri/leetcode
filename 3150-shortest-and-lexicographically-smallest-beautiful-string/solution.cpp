#include <string>
#include <algorithm>

class Solution {
public:
    std::string shortestBeautifulSubstring(std::string s, int k) {
        int n = s.length();
        int minLength = n + 1;
        int bestLeft = -1;
        int onesCount = 0;
        
        int l = 0;
        for (int r = 0; r < n; ++r) {
            if (s[r] == '1') {
                onesCount++;
            }
            
            // While we have exactly k '1's, try to shrink from the left
            while (onesCount == k) {
                int currentLength = r - l + 1;
                
                // Case 1: Found a strictly shorter beautiful substring
                if (currentLength < minLength) {
                    minLength = currentLength;
                    bestLeft = l;
                } 
                // Case 2: Found a substring of the same minimum length; check lexicographical order
                else if (currentLength == minLength) {
                    // s.compare(pos1, len1, s2, pos2, len2) returns < 0 if the first string fragment is smaller
                    if (s.compare(l, minLength, s, bestLeft, minLength) < 0) {
                        bestLeft = l;
                    }
                }
                
                // Shrink the window from the left
                if (s[l] == '1') {
                    onesCount--;
                }
                l++;
            }
        }
        
        // If bestLeft wasn't updated, no valid substring containing k '1's was found
        return (bestLeft == -1) ? "" : s.substr(bestLeft, minLength);
    }
};

