class Solution {
public:
    int scoreOfParentheses(string s) {
        int totalScore = 0;
        int depth = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                // Entering a deeper level of nesting, so multiply factor increases
                depth++;
            } else {
                // Leaving a level of nesting
                depth--;
                
                // If we find a core "()", its value is 2^depth
                if (s[i - 1] == '(') {
                    totalScore += (1 << depth);
                }
            }
        }
        
        return totalScore;
    }
};

