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

// NOTE: Operating Speed
// Run Time: #define MIN( val1, val2 ) << function min
// REASON: 
// FIND_MIN( FindMinDepth( root->left ), FindMinDepth( root->right ) )
// =  ( FindMinDepth( root->left ) <= FindMinDepth( root->right ) ? FindMinDepth( root->left ) : FindMinDepth( root->right ) )
#define USE_BUILDIN_MIN_FUNC ( 1 )

#if USE_BUILDIN_MIN_FUNC
#define FIND_MIN( val1, val2 ) min( val1, val2 )
#else
#define FIND_MIN( val1, val2 ) ( val1 <= val2 ? val1 : val2 )
#endif

class Solution {

	int minDepthHuaHua( TreeNode *root )
	{
		if( !root )
			return 0;
		if( !root->left && !root->right )
			return 1;
		int l = root->left ? minDepth( root->left ) : INT_MAX;
		int r = root->right ? minDepth( root->right ) : INT_MAX;
		return min( l, r ) + 1;
	}

	int FindMinDepth( TreeNode *root ) {
	// here the node should be exist
		
		if( root->left == nullptr ) {
			if( root->right == nullptr ) return 1;
			else return 1 + FindMinDepth( root->right );
		}
		else {
			if( root->right == nullptr ) return 1 + FindMinDepth( root->left );
			else return 1 + min( FindMinDepth( root->left ), FindMinDepth( root->right ) );
		}
	}

public:
    int minDepth(TreeNode* root) {

		if( root == nullptr ) return 0;
		return FindMinDepth( root );
	}
};
// @lc code=end

