/*
 * @lc app=leetcode id=124 lang=cpp
 *
 * [124] Binary Tree Maximum Path Sum
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
// Note:
// (1) Similar to 687
// (2) Declare local "After Iteration Call"
#define FIND_MAX( val1, val2 ) ( val1 > val2 ? val1 : val2 )

class Solution {
    int FindMaxDownwardPathSum( TreeNode* Node, int &nPathSumMax ) {

		if( Node == nullptr ) return 0;

		int nPathSumOfLeftNode = 0;
		if( Node->left ) nPathSumOfLeftNode = FindMaxDownwardPathSum( Node->left, nPathSumMax );

		int nPathSumOfRightNode = 0;
		if( Node->right ) nPathSumOfRightNode = FindMaxDownwardPathSum( Node->right, nPathSumMax );

		nPathSumMax = FIND_MAX( nPathSumMax, nPathSumOfLeftNode + nPathSumOfRightNode + Node->val );

		int nDownWardPathSum = Node->val + FIND_MAX( nPathSumOfLeftNode, nPathSumOfRightNode );
		return ( nDownWardPathSum > 0 ) ? ( nDownWardPathSum ) : 0;
    }
public:
    int maxPathSum(TreeNode* root) {

		int nPathSumMax = INT_MIN;
		FindMaxDownwardPathSum( root, nPathSumMax );
		return nPathSumMax;
    }
};
// @lc code=end

