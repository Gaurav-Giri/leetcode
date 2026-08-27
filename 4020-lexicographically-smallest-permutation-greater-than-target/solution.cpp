#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> counts(26, 0);
        
        // Count all the available characters from s
        for (char c : s) {
            counts[c - 'a']++;
        }
        
        // Count character requirements to form the full target string
        vector<int> target_counts(26, 0);
        for (char c : target) {
            target_counts[c - 'a']++;
        }
        
        // Step 1: Iterate backwards (from right to left) to find the ideal split-point index 'i'
        // where we can diverge from target by making the character at 'i' strictly greater.
        for (int i = n - 1; i >= 0; --i) {
            // Reclaim/remove the requirement for the suffix character target[i]
            target_counts[target[i] - 'a']--;
            
            // Validate if the current prefix can be successfully matched up to index i-1
            bool can_form_prefix = true;
            for (int j = 0; j < 26; ++j) {
                if (counts[j] < target_counts[j]) {
                    can_form_prefix = false;
                    break;
                }
            }
            
            // If the matching prefix cannot be formed, continue shifting left
            if (!can_form_prefix) {
                continue;
            }
            
            // Find the smallest character greater than target[i] available in our frequency pool
            int target_char_idx = target[i] - 'a';
            int chosen_char_idx = -1;
            
            for (int j = target_char_idx + 1; j < 26; ++j) {
                // Tentatively consume character 'j'
                counts[j]--;
                
                // Ensure remaining pool counts are enough to satisfy the prefix requirements
                bool valid = true;
                for (int k = 0; k < 26; ++k) {
                    if (counts[k] < target_counts[k]) {
                        valid = false;
                        break;
                    }
                }
                
                counts[j]++; // Backtrack 
                
                if (valid) {
                    chosen_char_idx = j;
                    break; // Pick the smallest valid option to keep the permutation smallest
                }
            }
            
            // Step 2: If a valid larger character was found, construct the resulting string
            if (chosen_char_idx != -1) {
                string result = "";
                
                // A. Append the identical matching prefix from 0 to i-1
                for (int j = 0; j < i; ++j) {
                    result += target[j];
                    counts[target[j] - 'a']--;
                }
                
                // B. Append the strictly larger character at index i
                result += (char)('a' + chosen_char_idx);
                counts[chosen_char_idx]--;
                
                // C. Greedily fill the remaining positions in ascending order ('a' to 'z')
                for (int j = 0; j < 26; ++j) {
                    while (counts[j] > 0) {
                        result += (char)('a' + j);
                        counts[j]--;
                    }
                }
                return result;
            }
        }
        
        // If no permutation can be constructed that is strictly greater than target
        return "";
    }
};

