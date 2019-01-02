// 面试题34：二叉树中和为某一值的路径
// 题目：输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所
// 有路径。从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
class Solution {
public:
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        if(root == nullptr)
        {
            return vector<vector<int>>();
        }
        
        vector<vector<int>> result;
        vector<int> sub;
        int currentSum = 0;
        FindPath(result, sub, root, expectNumber, currentSum);
        
        return result;
    }
    
    void FindPath(vector<vector<int>>& result, vector<int>& sub, TreeNode* root, const int expectNumber, int currentSum)
    {
        currentSum += root->val;
        sub.push_back(root->val);
        
        if(root->left == nullptr && root->right == nullptr && currentSum == expectNumber)
        {
            result.push_back(sub);
        }
        
        if(root->left != nullptr)
        {
            FindPath(result, sub, root->left, expectNumber, currentSum);
        }
        if(root->right != nullptr)
        {
            FindPath(result, sub, root->right, expectNumber, currentSum);
        }
        
        sub.pop_back();
    }
};