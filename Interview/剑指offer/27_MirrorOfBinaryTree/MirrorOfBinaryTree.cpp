// 面试题27：二叉树的镜像
// 题目：请完成一个函数，输入一个二叉树，该函数输出它的镜像。


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(nullptr), right(nullptr) {
	}
};
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot == nullptr)
        {
            return;
        }
        
        swap(pRoot->left, pRoot->right);
        if(pRoot->left != nullptr)
        {
            Mirror(pRoot->left);
        }
        
        if(pRoot->right != nullptr)
        {
            Mirror(pRoot->right);
        }
    }
};