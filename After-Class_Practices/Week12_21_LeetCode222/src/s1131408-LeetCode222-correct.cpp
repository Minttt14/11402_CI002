class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;

        int leftDepth = 0;
        int rightDepth = 0;
        
        TreeNode* l = root;
        TreeNode* r = root;

        while(l != nullptr){
            leftDepth++;
            l = l->left;
        }

        while(r != nullptr){
            rightDepth++;
            r = r->right;
        }

        if(leftDepth == rightDepth){
            return (1 << leftDepth) - 1; 
        }

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};