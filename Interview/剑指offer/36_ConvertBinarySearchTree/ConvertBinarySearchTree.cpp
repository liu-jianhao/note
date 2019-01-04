// 面试题36：二叉搜索树与双向链表
// 题目：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求
// 不能创建任何新的结点，只能调整树中结点指针的指向。


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
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(pRootOfTree == nullptr)
        {
            return nullptr;
        }
        TreeNode* pLastNode = nullptr;
        Convert(pRootOfTree, &pLastNode);

        while(pLastNode != nullptr && pLastNode->left != nullptr)
        {
            pLastNode = pLastNode->left;
        }

        return pLastNode;
    }

    // lastNode是pRoot左子树已经构建好的双向链表的最后一个节点
    void Convert(TreeNode* pRoot, TreeNode** lastNode)
    {
        if(pRoot == nullptr)
        {
            return;
        }

        // 以下分为三个部分，左子树，根节点调整链表指针，右子树
        if(pRoot->left != nullptr)
        {
            Convert(pRoot->left, lastNode);
        }

        pRoot->left = *lastNode;
        if(*lastNode != nullptr)
        {
            (*lastNode)->right = pRoot;
        }

        *lastNode = pRoot;

        if(pRoot->right != nullptr)
        {
            Convert(pRoot->right, lastNode);
        }
    }
};
