class Solution {
public:
    int sumRootToLeaf(TreeNode* root){
        return dfs(root, 0);
    }

private:
    int dfs(TreeNode* node, int currentSum){
        if (node == nullptr) {
            return 0;
        }
        
        currentSum = currentSum * 2 + node->val; 

        if(node->left == nullptr && node->right == nullptr){
            return currentSum;
        }

        return dfs(node->left, currentSum) + dfs(node->right, currentSum);
    }
};