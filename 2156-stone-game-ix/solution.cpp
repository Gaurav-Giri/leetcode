#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
public:
    bool stoneGameIX(std::vector<int>& stones) {
        // Step 1: Count occurrences of remainders 0, 1, and 2
        std::vector<int> count(3, 0);
        for (int stone : stones) {
            count[stone % 3]++;
        }
        
        // Step 2: Apply Game Theory strategy based on '0' remainder parity
        if (count[0] % 2 == 0) {
            // Even number of 0s do not change the game's final turn outcome.
            // Alice needs both Type 1 and Type 2 stones to control the flow.
            return std::min(count[1], count[2]) > 0;
        }
        
        // Odd number of 0s can swap the player turn parity.
        // Alice wins if the discrepancy between Type 1 and Type 2 stones is wide enough.
        return std::abs(count[1] - count[2]) > 2;
    }
};

