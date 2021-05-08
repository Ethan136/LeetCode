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

		// the definition of stack is:
		// (1) left = next stack
		// (2) right = node has not been checked yet
		// (3) value = "nNumFromTopToNode" for the node that has not been checked (i.e. nNumFromTopToNode in respect of node->right)
		TreeNode *pStack = nullptr;
		TreeNode *pNodeBackUp = nullptr;
        
		int nPathSum = 0;
		while( Node ) {

            // calc value for next node
            nNumFromTopToNode = nNumFromTopToNode * 10 + Node->val;
            
            // trasverse to end node
			switch( FIND_LINK_TYPE( Node ) ) {

			case NodeType_LinkLeft:
                    
                // go to next node
				Node = Node->left;
				break;

			case NodeType_LinkRight:
                    
                // go to next node
				Node = Node->right;
				break;

			case NodeType_LinkBoth:
                    
				// backup current node
				pNodeBackUp = Node;

				// go to left node
				Node = Node->left;

				// backup right node
				pNodeBackUp->left = pStack;
				pStack = pNodeBackUp;

				// store the current num info in stack
				pStack->val = nNumFromTopToNode;
				break;

			case NodeType_Leaf:

				// update sum when the end node is reached
				nPathSum += nNumFromTopToNode;

				// if there is no un-checked node within the stack
				if( pStack == nullptr ) {
					return nPathSum;
				}

				// restore the condition and check the "right node" within the stack
				Node = pStack->right;
				nNumFromTopToNode = pStack->val;

				// pop out the top of the stack
				pStack = pStack->left;
				break;

			default:
				return 0;
			}
		}
		return nPathSum;
	}

public:
    int sumNumbers(TreeNode* root) {
		return SumPathToLeafNum( root, 0 );
    }
};
// @lc code=end

