/*
 * @lc app=leetcode id=129 lang=cpp
 *
 * [129] Sum Root to Leaf Numbers
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

enum ENodeType {
	NodeType_Null,
	NodeType_LinkLeft,
	NodeType_LinkRight,
	NodeType_LinkBoth,
	NodeType_Leaf,
};

#define IS_NODE_LEFT_NULL( Node ) ( Node->left == nullptr )
#define IS_NODE_RIGHT_NULL( Node ) ( Node->right == nullptr )
#define FIND_NODE_TYPE( Node ) \
						( Node == nullptr ) ? ( NodeType_Null ) : \
						( IS_NODE_LEFT_NULL( Node ) ? \
						( IS_NODE_RIGHT_NULL( Node ) ? NodeType_Leaf : NodeType_LinkRight ) : \
						( IS_NODE_RIGHT_NULL( Node ) ? NodeType_LinkLeft : NodeType_LinkBoth ) )

class Solution {
    int SumPathToLeafNum( TreeNode* Node, int nNumFromTopToNode ) {

		switch( FIND_NODE_TYPE( Node ) ) {
		case NodeType_LinkLeft:
			return SumPathToLeafNum( Node->left, ( nNumFromTopToNode * 10 + Node->val ) );

		case NodeType_LinkRight:
			return SumPathToLeafNum( Node->right, ( nNumFromTopToNode * 10 + Node->val ) );

		case NodeType_LinkBoth:
			return SumPathToLeafNum( Node->left, ( nNumFromTopToNode * 10 + Node->val ) ) + SumPathToLeafNum( Node->right, ( nNumFromTopToNode * 10 + Node->val ) );

		case NodeType_Leaf:
			return ( nNumFromTopToNode * 10 + Node->val );

		case NodeType_Null:
		default:
			return 0;
		}
	}

public:
    int sumNumbers(TreeNode* root) {
		return SumPathToLeafNum( root, 0 );
    }
};
// @lc code=end

