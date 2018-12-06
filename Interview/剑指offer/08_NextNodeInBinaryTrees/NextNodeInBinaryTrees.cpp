// 面试题8：二叉树的下一个结点
// 题目：给定一棵二叉树和其中的一个结点，如何找出中序遍历顺序的下一个结点？
// 树中的结点除了有两个分别指向左右子结点的指针以外，还有一个指向父结点的指针。

#include <cstdio>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if(pNode == nullptr)
        {
            return nullptr;
        }
        
        TreeLinkNode* pNext = nullptr;
        
        if(pNode->right != nullptr)
        {
            TreeLinkNode* pRight = pNode->right;
            while(pRight->left != nullptr)
            {
                pRight = pRight->left;
            }
            pNext =  pRight;
        }
        else if(pNode->next != nullptr)
        {
            TreeLinkNode* pCurrent = pNode;
            TreeLinkNode* pParent = pNode->next;
            
            while(pParent != nullptr && pCurrent == pParent->right)
            {
                pCurrent = pParent;
                pParent = pParent->next;
            }
            pNext = pParent;
        }
        
        return pNext;
    }
};