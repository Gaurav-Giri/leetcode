class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        // Store the key-value pairs in a hash map for O(1) lookups
        unordered_map<string, string> dict;
        for (const auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }
        
        string result = "";
        string current_key = "";
        bool inside_brackets = false;
        
        for (char c : s) {
            if (c == '(') {
                inside_brackets = true;
            } else if (c == ')') {
                inside_brackets = false;
                // Check if the key exists in our map
                if (dict.count(current_key)) {
                    result += dict[current_key];
                } else {
                    result += "?";
                }
                current_key = ""; // Reset the key for the next bracket pair
            } else {
                if (inside_brackets) {
                    current_key += c;
                } else {
                    result += c;
                }
            }
        }
        
        return result;
    }
};

