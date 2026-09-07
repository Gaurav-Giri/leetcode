#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
    int distinctSubseqII(std::string s) {
        constexpr int kMod = 1'000'000'007;
        
        // endsIn[i] stores the number of unique subsequences ending with character ('a' + i)
        std::vector<long> endsIn(26, 0);
        
        for (const char c : s) {
            int charIndex = c - 'a';
            
            // Total subseqs up to now = sum of all existing subseqs + 1 (the single character itself)
            long currentTotal = 1;
            for (long count : endsIn) {
                currentTotal = (currentTotal + count) % kMod;
            }
            
            // Update the count for the current character
            endsIn[charIndex] = currentTotal;
        }
        
        // Sum up all subsequences ending in any character
        long totalDistinctSubseqs = 0;
        for (long count : endsIn) {
            totalDistinctSubseqs = (totalDistinctSubseqs + count) % kMod;
        }
        
        return totalDistinctSubseqs;
    }
};

