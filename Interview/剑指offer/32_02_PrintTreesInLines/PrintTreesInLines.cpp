// 面试题32（二）：分行从上到下打印二叉树
// 题目：从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层
// 打印到一行。


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
    vector<vector<int>> Print(TreeNode* pRoot) {
        vector<vector<int>> result;
        vector<int> sub;
        if(pRoot == nullptr)
        {
            return result;
        }
        
        queue<TreeNode*> q;
        // 在这一层还剩多少个
        int toBePrint = 1;
        // 下一层有多少个
        int nextLevel = 0;
        
        q.push(pRoot);
        while(!q.empty())
        {
            TreeNode* pCur = q.front();
            q.pop();
            sub.push_back(pCur->val);
            if(pCur->left != nullptr)
            {
                q.push(pCur->left);
                ++nextLevel;
            }
            if(pCur->right != nullptr)
            {
                q.push(pCur->right);
                ++nextLevel;
            }
            
            --toBePrint;
            if(toBePrint == 0)
            {
                result.push_back(sub);
                sub.clear();
                toBePrint = nextLevel;
                nextLevel = 0;
            }
        }
        
        return result;
    }
};