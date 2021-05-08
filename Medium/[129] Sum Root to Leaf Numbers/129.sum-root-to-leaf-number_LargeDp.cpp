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
#define FIND_LINK_TYPE( Node ) \
						( IS_NODE_LEFT_NULL( Node ) ? \
						( IS_NODE_RIGHT_NULL( Node ) ? NodeType_Leaf : NodeType_LinkRight ) : \
						( IS_NODE_RIGHT_NULL( Node ) ? NodeType_LinkLeft : NodeType_LinkBoth ) )

class Solution {
    int SumPathToLeafNum( TreeNode* Node, int nNumFromTopToNode ) {
    // here the input node is supposed to exist

		while( Node ) {
            
            // calc value for next node
            nNumFromTopToNode = nNumFromTopToNode * 10 + Node->val;
            
            // trasverse to end node
			switch( FIND_LINK_TYPE( Node ) ) {
                    
			case NodeType_LinkLeft:
				Node = Node->left;
				break;

			case NodeType_LinkRight:
				Node = Node->right;
				break;

			case NodeType_LinkBoth:
				return SumPathToLeafNum( Node->left, nNumFromTopToNode ) + SumPathToLeafNum( Node->right, nNumFromTopToNode );

			case NodeType_Leaf:
				return nNumFromTopToNode;

			default:
				return 0;
			}
		}
		return nNumFromTopToNode;
	}

public:
    int sumNumbers(TreeNode* root) {
        if( root == nullptr ) return 0;
		return SumPathToLeafNum( root, 0 );
    }
};
// @lc code=end

