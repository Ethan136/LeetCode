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

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

		// create a node window
		ListNode *pWindowHead = head;
		ListNode *pWindowTail = head;

		// expand the boundary of queue until the length of window equals to n
		for( int nStoreIndex = 0; nStoreIndex < n - 1; nStoreIndex++ ) {
			pWindowTail = pWindowTail->next;
		}

		// to remove certain node, we should have the node "Before the window"
		ListNode *pNodeBeforeWindow = nullptr;

		// scan to the last node
		while( pWindowTail->next != nullptr ) {

			// record the nore before window
			pNodeBeforeWindow = pWindowHead;

			// update head of window
			pWindowHead = pWindowHead->next;

			// update tail of window
			pWindowTail = pWindowTail->next;
		}

		// if remove head is required
		if( pNodeBeforeWindow == nullptr ) {
			return head->next;
		}

		// remove node after the head
		pNodeBeforeWindow->next = pWindowHead->next;
		return head;
	}
};
// @lc code=end

