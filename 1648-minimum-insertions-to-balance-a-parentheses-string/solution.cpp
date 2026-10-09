#include <string>
#include <iostream>

class Solution {
public:
    int minInsertions(std::string s) {
        int insertions = 0;
        int neededRight = 0; // Number of ')' needed

        for (char c : s) {
            if (c == '(') {
                // Each '(' needs 2 ')'
                // If neededRight is odd, it means we have a single ')' hanging.
                // We must insert 1 ')' to complete the pair before opening a new one.
                if (neededRight % 2 == 1) {
                    insertions++;   // Insert 1 missing ')'
                    neededRight--;  // That single needed ')' is now satisfied
                }
                neededRight += 2;
            } else { // c == ')'
                neededRight--;
                
                // If neededRight falls below 0, it means we got an extra ')' without an '('
                if (neededRight < 0) {
                    insertions++;    // Insert 1 missing '('
                    neededRight += 2; // The newly inserted '(' requires 2 ')', but since we just consumed one, we need 1 more ')' total
                }
            }
        }
        
        // At the end, if any neededRight remains, it's the number of missing ')'
        return insertions + neededRight;
    }
};

