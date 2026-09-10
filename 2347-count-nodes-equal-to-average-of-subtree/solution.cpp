/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int matchingNodesCount = 0;

    // Helper function that returns {sum_of_nodes, count_of_nodes}
    pair<int, int> calculateSubtree(TreeNode* node) {
        if (!node) {
            return {0, 0};
        }

        // Post-order traversal: Solve left and right subtrees first
        auto leftSubtree = calculateSubtree(node->left);
        auto rightSubtree = calculateSubtree(node->right);

        // Calculate total sum and total node count for the current subtree
        int totalSum = leftSubtree.first + rightSubtree.first + node->val;
        int totalCount = leftSubtree.second + rightSubtree.second + 1;

        // Check if the current node's value equals the floor average of the subtree
        if (node->val == (totalSum / totalCount)) {
            matchingNodesCount++;
        }

        return {totalSum, totalCount};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        matchingNodesCount = 0;
        calculateSubtree(root);
        return matchingNodesCount;
    }
};

