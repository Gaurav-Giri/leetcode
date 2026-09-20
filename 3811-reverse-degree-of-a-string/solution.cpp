class Solution {
public:
    int reverseDegree(string s) {
        int totalReverseDegree = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Calculate the 1-indexed position of the character in the string
            int stringPosition = i + 1;
            
            // Calculate the position in the reversed alphabet ('a' = 26, 'b' = 25, ..., 'z' = 1)
            int reverseAlphabetPosition = 26 - (s[i] - 'a');
            
            // Add the product to the running total
            totalReverseDegree += stringPosition * reverseAlphabetPosition;
        }
        
        return totalReverseDegree;
    }
};

