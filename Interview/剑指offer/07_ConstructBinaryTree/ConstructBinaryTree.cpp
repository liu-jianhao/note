// 面试题7：重建二叉树
// 题目：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输
// 入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,
// 2, 4, 7, 3, 5, 6, 8}和中序遍历序列{4, 7, 2, 1, 5, 3, 8, 6}，则重建出
// 图2.6所示的二叉树并输出它的头结点。

#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
  public:
    TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin)
    {
        if (pre.empty() || vin.empty())
        {
            return nullptr;
        }

        return constructTree(pre, 0, vin, 0, vin.size());
    }

    // indexOfPre是先序遍历的下标
    TreeNode *constructTree(const vector<int> pre, unsigned long indexOfPre, const vector<int> vin, int startVin, int endVin)
    {
        TreeNode *root = nullptr;
        if (indexOfPre < pre.size())
        {
            for (int i = startVin; i < endVin; ++i)
            {
                if (vin[i] == pre[indexOfPre])
                {
                    root = new TreeNode(pre[indexOfPre]);

                    root->left = constructTree(pre, indexOfPre + 1, vin, startVin, i);

                    root->right = constructTree(pre, indexOfPre + (i - startVin + 1), vin, i + 1, endVin);

                    return root;
                }
            }
        }

        return root;
    }
};