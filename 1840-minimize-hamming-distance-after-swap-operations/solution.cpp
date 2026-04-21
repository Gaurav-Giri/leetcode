class Solution {
public:
    vector<int> parent;

    int find(int x){
        if (parent[x]!=x)
        parent[x] = find(parent[x]);//path compression
        return parent[x];
    }
    void unite(int a, int b){
        int pa = find(a);
        int pb = find(b);
        if (pa != pb)
            parent[pa] = pb;
    }
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();

        // step1: initialise dsu
        parent.resize(n);
        for(int i = 0; i< n; i++)
            parent[i]= i;

        // step2: build connected components
        for (auto &p : allowedSwaps)
            unite(p[0], p[1]);
        
        // step3: Group indices by parent
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i<n; i++){
            groups[find(i)].push_back(i);
        }

        int result = 0;

        // step4: processeach group
        for (auto &g : groups){
            unordered_map<int, int> freq;

            // count values in source
            for (int idx : g.second)
            freq[source[idx]]++;

            // match with target
            for (int idx : g.second){
                if (freq[target[idx]] > 0)
                freq[target[idx]]--;
                else
                result++;//mismatch
            }
        }
        
        return result;
    }
};
