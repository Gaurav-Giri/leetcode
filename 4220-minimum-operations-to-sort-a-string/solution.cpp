class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        
        // Step 1: Check if the string is already sorted
        bool sorted = true;
        for (int i = 1; i < n; ++i) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted) return 0;
        
        // Step 2: Handle impossible edge case
        // If length is 2 and it's unsorted (e.g., "ba"), we can't select any valid substring
        if (n == 2) return -1;
        
        // Step 3: Find global minimum and maximum characters
        char mn = s[0];
        char mx = s[0];
        for (char c : s) {
            mn = min(mn, c);
            mx = max(mx, c);
        }
        
        // Case 1: Minimum is at the start OR Maximum is at the end -> 1 operation
        // We can just sort the rest of the string leaving the correct extreme untouched.
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }
        
        // Case 2: Minimum or Maximum exists somewhere in the middle -> 2 operations
        for (int i = 1; i < n - 1; ++i) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }
        
        // Case 3: Minimum is exclusively at the end AND Maximum is exclusively at the start -> 3 operations
        return 3;
    }
};

