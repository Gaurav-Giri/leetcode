class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> pair(n);
        stack<int> st;

        // Step 1: Pair up the matching parentheses indices
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        // Step 2: Traverse and build the result string
        string result = "";
        int direction = 1; // 1 means moving right, -1 means moving left

        for (int i = 0; i < n; i += direction) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i];       // "Teleport" to the matching parenthesis
                direction = -direction; // Reverse the traversal direction
            } else {
                result += s[i];    // Append regular characters
            }
        }

        return result;
    }
};

