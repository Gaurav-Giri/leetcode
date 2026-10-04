class Solution {
public:
    bool checkValidString(string s) {
        int minOpen = 0; // Minimum possible open parentheses
        int maxOpen = 0; // Maximum possible open parentheses

        for (char c : s) {
            if (c == '(') {
                minOpen++;
                maxOpen++;
            } else if (c == ')') {
                minOpen--;
                maxOpen--;
            } else { // c == '*'
                // If '*' is treated as ')', minOpen decreases
                minOpen--;
                // If '*' is treated as '(', maxOpen increases
                maxOpen++;
            }

            // If maxOpen is negative, it means we have too many ')' 
            // and even converting all '*' to '(' cannot save it.
            if (maxOpen < 0) {
                return false;
            }

            // minOpen cannot be negative because we can't have negative open brackets.
            // If it goes below 0, it means we treated some '*' as ')' when we shouldn't have,
            // so we reset it to 0 (treating them as empty strings instead).
            if (minOpen < 0) {
                minOpen = 0;
            }
        }

        // The string is valid if it's possible to have exactly 0 open parentheses at the end.
        return minOpen == 0;
    }
};

