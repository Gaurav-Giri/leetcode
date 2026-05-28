class Solution {
public:

    struct TrieNode {
        int child[26];
        int idx;

        TrieNode() {
            memset(child, -1, sizeof(child));
            idx = -1;
        }
    };

    vector<TrieNode> trie;
    vector<string>* words;

    bool better(int a, int b) {
        if (b == -1) return true;

        if ((*words)[a].size() != (*words)[b].size())
            return (*words)[a].size() < (*words)[b].size();

        return a < b;
    }

    void insert(const string& s, int index) {
        int node = 0;

        if (better(index, trie[node].idx))
            trie[node].idx = index;

        for (int i = s.size() - 1; i >= 0; i--) {
            int c = s[i] - 'a';

            if (trie[node].child[c] == -1) {
                trie[node].child[c] = trie.size();
                trie.push_back(TrieNode());
            }

            node = trie[node].child[c];

            if (better(index, trie[node].idx))
                trie[node].idx = index;
        }
    }

    int search(const string& s) {
        int node = 0;

        for (int i = s.size() - 1; i >= 0; i--) {
            int c = s[i] - 'a';

            if (trie[node].child[c] == -1)
                break;

            node = trie[node].child[c];
        }

        return trie[node].idx;
    }

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {

        words = &wordsContainer;

        trie.reserve(500000 + 5);
        trie.push_back(TrieNode());

        for (int i = 0; i < wordsContainer.size(); i++) {
            insert(wordsContainer[i], i);
        }

        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (auto& q : wordsQuery) {
            ans.push_back(search(q));
        }

        return ans;
    }
};
