/*
 * @lc app=leetcode id=111 lang=cpp
 *
 * [111] Minimum Depth of Binary Tree
 */

// @lc code=start
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
#define FIND_MIN( val1, val2 ) ( val1 < val2 ? val1 : val2 )

class Solution {

public:
    int minDepth(TreeNode* root) {

		// check root 
		if( root == nullptr ) return 0;

		// set initial condition
		int nMinDepth = INT_MAX;
		int nBranchDepth = 1;

		// to record the divert node
		TreeNode *pNodeToPushInStack = nullptr;
		TreeNode *pStack = nullptr;

		// explore to every leaf
		while( root ) {

			if( root->left && root->right ) {
				pNodeToPushInStack = root;
				root = root->left;

				pNodeToPushInStack->left = pStack;
				pStack = pNodeToPushInStack;
				pStack->val = nBranchDepth;
			}

			else if( root->left ) {
				root = root->left;
			}

			else if( root->right ) {
				root = root->right;
			}

			else {
				nMinDepth = FIND_MIN( nMinDepth, nBranchDepth );

				if( pStack == nullptr ) break;
				root = pStack->right;
				nBranchDepth = pStack->val;

				pStack = pStack->left;
			}

			nBranchDepth++;
		}

		return nMinDepth;
    }
};
// @lc code=end

