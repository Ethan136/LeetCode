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

#define MEM_RECOLLECT ( 0 )
/*
	<With Mem Recollect>
	52/52 cases passed (208 ms)
	Your runtime beats 94.74 % of cpp submissions
	Your memory usage beats 99.04 % of cpp submissions (114.2 MB)
*/

/*
	<Without Mem Recollect>
	52/52 cases passed (160 ms)
	Your runtime beats 99.43 % of cpp submissions
	Your memory usage beats 99.16 % of cpp submissions (97.8 MB)
*/


#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
struct TMemRecollect {
	TreeNode **BackUpLinkForDetachNode;
	TreeNode *pLinkToFirstDetachNode;
	TMemRecollect() : BackUpLinkForDetachNode( nullptr ), pLinkToFirstDetachNode( nullptr ) {};
};
#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE


#define USE_BUILDIN_MIN_FUNC ( 0 )
/*
	<use buildin min>
		<Without Mem Recollect>
		52/52 cases passed (152 ms)
		Your runtime beats 99.61 % of cpp submissions
		Your memory usage beats 99.16 % of cpp submissions (97.8 MB)

		<With Mem Recollect>
		52/52 cases passed (192 ms)
		Your runtime beats 98.55 % of cpp submissions
		Your memory usage beats 99.04 % of cpp submissions (114.2 MB)
*/
/*
	<use #define min>
		<Without Mem Recollect>
		52/52 cases passed (164 ms)
		Your runtime beats 99.31 % of cpp submissions
		Your memory usage beats 99.16 % of cpp submissions (97.7 MB)

		<With Mem Recollect>
		52/52 cases passed (200 ms)
		Your runtime beats 97.93 % of cpp submissions
		Your memory usage beats 99.04 % of cpp submissions (114.3 MB)
*/

#if USE_BUILDIN_MIN_FUNC
#define FIND_MIN( val1, val2 ) min( val1, val2 )
#else
#define FIND_MIN( val1, val2 ) ( val1 < val2 ? val1 : val2 )
#endif

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

		#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
		TMemRecollect MemRecollect;
		TreeNode **pPrevNodeLink;
		if( root->left && root->right ) {
			MemRecollect.BackUpLinkForDetachNode = &root->right;
			pPrevNodeLink = &MemRecollect.pLinkToFirstDetachNode;
		}
		else {
			pPrevNodeLink = &root->left;
		}

		TreeNode *pUsedStack = nullptr;
		TreeNode *pStackNodeToPop = nullptr;
		#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

		// explore to every leaf
		while( root ) {

			if( root->left && root->right ) {
				#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
				*pPrevNodeLink = root->left;
				#endif 				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

				pNodeToPushInStack = root;
				root = root->left;

				pNodeToPushInStack->left = pStack;
				pStack = pNodeToPushInStack;
				pStack->val = nBranchDepth;
			}

			else if( root->left ) {
				#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
				pPrevNodeLink = &root->left;
				#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

				root = root->left;
			}

			else if( root->right ) {
				#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
				pPrevNodeLink = &root->right;
				#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

				root = root->right;
			}

			else {
				nMinDepth = FIND_MIN( nMinDepth, nBranchDepth );

				if( pStack == nullptr ) {
					break;
				}

				#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
				root->right = pStack->right;
				pPrevNodeLink = &root->right;
				#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

				root = pStack->right;
				nBranchDepth = pStack->val;

				#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
				pStackNodeToPop = pStack;
				#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

				pStack = pStack->left;

				#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
				pStackNodeToPop->right = nullptr;
				pStackNodeToPop->left = pUsedStack;
				pUsedStack = pStackNodeToPop;
				#endif				// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
			}

			nBranchDepth++;
		}

		#if MEM_RECOLLECT	// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE
		// (1) the Overall Root must be a "divert node" and now is the head of the pUsedStack
		// and the link "pLinkToFirstDetachNode" links to certain detached node
		if( MemRecollect.BackUpLinkForDetachNode ) {
			*MemRecollect.BackUpLinkForDetachNode = MemRecollect.pLinkToFirstDetachNode;
		}
		// (2) the Overall Root is a "single link node" and the "current root" is connected to it
		// and the "pUsedStack" is detached
		else {
			root->right = pUsedStack;
		}
		#endif			// FOR MEMORY RECOLLECTION, WILL DEGRADE BOTH MEM AND SPEED IN LEET CODE

		return nMinDepth;
    }
};
// @lc code=end
