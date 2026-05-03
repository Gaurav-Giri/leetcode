class Solution {
public:
    bool rotateString(string s, string goal) {
        // If lengths differ, goal cannot be a rotation of s
        if (s.length() != goal.length()) {
            return false;
        }
        
        // Concatenate s with itself. Any rotation of s is a substring of s+s.
        string doubled = s + s;
        
        // Check if goal is a substring of doubled string
        return doubled.find(goal) != string::npos;
    }
};
