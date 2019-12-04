#include <iostream>
#include <vector>
using namespace std;

/*
 * https://leetcode.com/contest/weekly-contest-163/problems/find-elements-in-a-contaminated-binary-tree/
 * 这题主要是一个完全二叉树的变形，首先需要回复二叉树，然后查找给定值，恢复的时间复杂度O(n)，查找的时间复杂度是O(log(target))
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };


class FindElements {
public:
    TreeNode *root= nullptr;
    void help(TreeNode* root, int val){
        if(root== nullptr)
            return;
        root->val=val;
        help(root->left, 2*val+1);
        help(root->right, 2*val+2);
    }
    FindElements(TreeNode* root) {
        help(root,0);
        this->root=root;
    }

    TreeNode* _find(int target){
        if(this->root== nullptr)
            return nullptr;
        if(target==0)
            return root;
        TreeNode* fa=_find((target-1)/2);
        if(fa&&target%2&&fa->left)
            return fa->left;
        if(fa&&(target+1)%2&&fa->right)
                return fa->right;
        return nullptr;
    }

    bool find(int target) {
        return _find(target)!= nullptr;
    }
};

int main() {

}