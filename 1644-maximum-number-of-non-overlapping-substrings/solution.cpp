class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> first(26, -1), last(26, -1);
        
        // Step 1: Find the first and last occurrence of each character
        for (int i = 0; i < n; ++i) {
            if (first[s[i] - 'a'] == -1) {
                first[s[i] - 'a'] = i;
            }
            last[s[i] - 'a'] = i;
        }
        
        vector<pair<int, int>> intervals;
        
        // Step 2: Generate valid intervals starting at each character's first occurrence
        for (int i = 0; i < 26; ++i) {
            if (first[i] == -1) continue;
            
            int start = first[i];
            int end = last[i];
            bool valid = true;
            
            // Expand the interval to cover all enclosed characters completely
            for (int j = start; j <= end; ++j) {
                int charIdx = s[j] - 'a';
                if (first[charIdx] < start) {
                    // Encountered a character that started before our 'start'
                    valid = false;
                    break;
                }
                end = max(end, last[charIdx]);
            }
            
            if (valid) {
                intervals.push_back({end, start}); // Store as {end, start} for easier sorting
            }
        }
        
        // Step 3: Greedy selection of non-overlapping intervals
        sort(intervals.begin(), intervals.end());
        
        vector<string> result;
        int lastEnd = -1;
        
        for (auto& interval : intervals) {
            int end = interval.first;
            int start = interval.second;
            
            // If the current interval starts after the last selected interval ends
            if (start > lastEnd) {
                result.push_back(s.substr(start, end - start + 1));
                lastEnd = end;
            }
        }
        
        return result;
    }
};

