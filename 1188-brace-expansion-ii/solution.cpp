class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        unordered_set<string> visited;
        vector<string> result;
        
        // Helper function to perform DFS / string reduction
        auto dfs = [&](auto& self, string exp) -> void {
            // Find the first closing brace
            size_t j = exp.find_first_of('}');
            
            // Base case: If no braces are left, insert the fully expanded string
            if (j == string::npos) {
                visited.insert(exp);
                return;
            }
            
            // Find the corresponding opening brace before this closing brace
            size_t i = exp.rfind('{', j);
            
            // Segment the string into prefix (a) and suffix (c)
            string prefix = exp.substr(0, i);
            string suffix = exp.substr(j + 1);
            
            // Extract the comma-separated options inside the innermost braces
            string inner = exp.substr(i + 1, j - i - 1);
            stringstream ss(inner);
            string option;
            
            // Split by comma and recursively solve the new expressions
            while (getline(ss, option, ',')) {
                self(self, prefix + option + suffix);
            }
        };
        
        // Initialize the recursive generation
        dfs(dfs, expression);
        
        // Copy unique items to a vector and sort alphabetically
        result.assign(visited.begin(), visited.end());
        sort(result.begin(), result.end());
        
        return result;
    }
};

