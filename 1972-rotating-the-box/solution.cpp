class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();

        // Step 1: simulate gravity (stones fall to the right)
        for (int i = 0; i < m; i++) {
            int writePos = n - 1; // where next stone should go

            for (int j = n - 1; j >= 0; j--) {
                if (boxGrid[i][j] == '*') {
                    writePos = j - 1; // reset after obstacle
                }
                else if (boxGrid[i][j] == '#') {
                    swap(boxGrid[i][j], boxGrid[i][writePos]);
                    writePos--;
                }
            }
        }

        // Step 2: rotate matrix
        vector<vector<char>> result(n, vector<char>(m));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[j][m - 1 - i] = boxGrid[i][j];
            }
        }

        return result;
    }
};
