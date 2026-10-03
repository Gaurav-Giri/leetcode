class Solution {
public:
    void backtrack(vector<string>& result, string current, int open, int close, int max) {
        // Base case: If the current string reaches the maximum length, add it to results
        if (current.length() == max * 2) {
            result.push_back(current);
            return;
        }

        // If we can still add an opening parenthesis, do so
        if (open < max) {
            backtrack(result, current + "(", open + 1, close, max);
        }
        
        // If we have more opening than closing parentheses, we can safely add a closing one
        if (close < open) {
            backtrack(result, current + ")", open, close + 1, max);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }
};

