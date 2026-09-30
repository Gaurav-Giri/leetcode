class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans;
        ans.reserve(seq.length()); // Optimize memory allocation
        int depth = 0;
        
        for (const char c : seq) {
            if (c == '(') {
                // Assign current depth group, then increment depth
                ans.push_back(depth % 2);
                depth++;
            } else {
                // Decrement depth first, then assign depth group
                depth--;
                ans.push_back(depth % 2);
            }
        }
        
        return ans;
    }
};

