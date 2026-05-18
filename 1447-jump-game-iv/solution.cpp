class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        if (n == 1)
            return 0;

        unordered_map<int, vector<int>> mp;

        // Store indices for each value
        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }

        queue<int> q;
        vector<int> visited(n, 0);

        q.push(0);
        visited[0] = 1;

        int steps = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                int idx = q.front();
                q.pop();

                // Reached last index
                if (idx == n - 1)
                    return steps;

                // Move to idx - 1
                if (idx - 1 >= 0 && !visited[idx - 1]) {
                    visited[idx - 1] = 1;
                    q.push(idx - 1);
                }

                // Move to idx + 1
                if (idx + 1 < n && !visited[idx + 1]) {
                    visited[idx + 1] = 1;
                    q.push(idx + 1);
                }

                // Move to same value indices
                for (int next : mp[arr[idx]]) {
                    if (!visited[next]) {
                        visited[next] = 1;
                        q.push(next);
                    }
                }

                // Important optimization
                mp[arr[idx]].clear();
            }

            steps++;
        }

        return -1;
    }
};
