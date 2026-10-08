#include <string>

class Solution {
public:
    std::string removeOuterParentheses(std::string s) {
        std::string result = "";
        int opened = 0; // Tracks the current nesting depth
        
        for (char c : s) {
            if (c == '(') {
                // If opened > 0, this '(' is NOT the outermost one
                if (opened > 0) {
                    result += c;
                }
                opened++;
            } else {
                opened--;
                // If opened > 0, this ')' is NOT the outermost one
                if (opened > 0) {
                    result += c;
                }
            }
        }
        
        return result;
    }
};

