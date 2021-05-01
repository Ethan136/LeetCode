/*
 * @lc app=leetcode id=19 lang=cpp
 *
 * [19] Remove Nth Node From End of List
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#define CONNECT_NODE( NodeFirst, NodeSecond ) \
	if( NodeFirst != nullptr ) {              \
		NodeFirst->next = NodeSecond;         \
	}

#define MAX_NODE_NUM ( 30 )

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

		// use a stack to record node
		ListNode *NodeRecord[ MAX_NODE_NUM ] = {};

		// store head node
		int nNodeNum = 0;

		// here head means "remained head"
		while( head != nullptr ) {

			// record the node
			NodeRecord[ nNodeNum ] = head;

			// update node num
			nNodeNum++;

			// advance to next node
			head = head->next;
		}

		// if remove head is required
		if( n == nNodeNum ) {
			return NodeRecord[ 1 ];
		}

		// remove node after the head
		NodeRecord[ nNodeNum - n - 1 ]->next = NodeRecord[ nNodeNum - n ]->next;
		return NodeRecord[ 0 ];
	}
};
// @lc code=end

