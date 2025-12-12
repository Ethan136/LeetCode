---
LeetCodeSeq: 6
LeetCode150Finish: 11
LeetCode150Num: 11
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150ConceptOk: 11
LeetCode150TestPass: 11
LeetCode150Review: 11
LeetCode150Rev2: 11
---
### Concept
#### Link List Basic Operation
##### Insert Node
- 模板
	- **取得 insert position 的前一個位子的 node: prevNodeToInsert***
	- backup origin next node
		- nextNode = prevNodeToInsert->next
	- prev node link to new node
		- prevNodeToInsert->next = insertNode / new Node(val)
	- new node link to origin next node
		- (prevNodeToInsert->next)->next = nextNode

##### TakeOut Node
- 模板
	- **取得 takeout position 的前一個位子的 node: prevNodeToTakeOut**
	- backup origin next node
		- nextNode = prevNodeToTakeOut->next
	- cur node link to next next node
		- prevNodeToTakeOut->next = (prevNodeToTakeOut->next->next)
	- unlink origin next node from list
		- nodeNode->next = nullptr

#### Reverse List
- 模板
	- Init prevNode of head
		- prevNode = nullptr
	- Init reverse tail
		- reverseTail = head
	- traverse through list: while( node )
		- backup origin next node
			- nextNode = node->next
		- current node link to prevNode & update prev node
			- node->next = prevNode
			- prevNode = node
		- current node traverse to next node
			- node =nextNode
	- Finish
		- return prevNode
- 題目
	- [[206. Reverse Linked List - Main]]
	- [[25. Reverse Nodes in K-Group - Main]]

#### List Middle Point
##### MIddle Point Node (left of double middle)
- 說明
	- double middle point 的時候
		- prevNode 停在 middle left node 前一個
		- slowNode 停在 middle left node
		- fastNode 停在 null ptr （TravCnt = 2N + 1 -> *Not Match Valid Node Cnt*）
	- single middle point 的時候
		- prevNode 停在 middle node 前一個
		- slowNode 停在 middle node
		- fastNode 停在 tail valid node （TRavCnt = 2N + 1 -> *Match Valid Node Cnt* ）
- 模板
	- init prevNode
	- init slow / fast ptr
		- slowNode = head
		- fastNode = head->next
	- fast ptr traverse through list: while( fastNode && fastNode->next )
		- prevNode = slowNode
		- slowNode = slowNode->next;
		- fastNode = fastNode->next->next;

##### Middle Point Right Node (right of double middle)
- 說明
	- double middle point 的時候
		- prevNode 停在 middle left node
		- slowNode 停在 middle right node
		- fastNode 停在 tail valid node（TravCnt = 2N） -> *Match Valid Node Cnt*
	- single middle point 的時候
		- prevNode 停在 middle node 前一個
		- slowNode 停在 middle node
		- fastNode 停在 nullptr （TravCnt = 2N） -> *Not Match Valid Node Cnt*
- 模板
	- init prevNode
	- init slow / fast ptr
		- slowNode = head
		- fastNode = head
	- fast ptr traverse through list: while( fastNode && fastNode->next )
		- prevNode = slowNode
		- slowNode = slowNode->next;
		- fastNode = fastNode->next->next;

##### List Split in Mid
- 模板: 左邊比右邊多一個 node -> **slow / fast ptr 要停在 middle left -> 最少要兩顆 node**
	- 檢查 mid point 
		- 檢查最少兩個 node: if(!head || !head->next) return
		- slow / fast ptr init
			- slow = head
			- fast = head->next
		- while(fast && fast->next)
			- slow = slow->next
			- fast = fast->next->next
		- mid = slow
	- 設定 head2
		- **mid (mid left) point next = head of right part of list**
			- head2 = mid->next
	- 切開 list in two parts
		- mid->next = nullptr
- 題目
	- [[143. Reorder List - Main]]

##### check list node num
- 觀念
	- 從 head 開始 traverse
	- 如果 head  = nullptr -> lsit node num = 0
- 模板 checkListNodeNum(head)
	- init
		- node = head
		- travCnt = 0
	- traverse to nullptr
		- while(node)
			- node = node->next
			- travCnt ++
	- finish
		- return travCnt
- 題目
	- [[148. SortList - Main]]

##### n-th Node from current node
- 觀念
	- 需要使用 augmentedHead
	- 從 augmentedHead 往後 traverse n nodes
- 模板: getKthNodeFromStart(node, k)
	- augment head init
		- augmentedHead
		- augmentedHead->next = startNode
	- traverse init
		- travCnt = 0
		- travNode = &augmentedHead
	- traverse: while(travNode && (travCnt < n))
		- travNode = travNode->next
		- travCnt++
	- 要嚴格 n-th node
		- return (travCnt == n) ? (travNode) : (nullptr)
- 題目
	- [[25. Reverse Nodes in K-Group - Main]]
	- [[148. SortList - Main]]

##### at most n-th Node from current node
- 觀念
	- 需要使用 augmentedHead
	- 從 augmentedHead 往後 traverse n nodes
		- **如果不足 n nodes，則回傳最後一個 valid**
		- **如果 start 爲 nullptr，則回傳 nullptr**
- 模板: getAtMostKthNodeFromStart(node, k)
	- **check start node valid**
		- if(!node) return node;
	- augment head init
		- augmentedHead
		- augmentedHead->next = startNode
	- traverse init
		- travCnt = 0
		- travNode = &augmentedHead
	- traverse: while(**travNode->next** && (travCnt < n))
		- travNode = travNode->next
		- travCnt++
	- 只要最後一個 traverse 的
		- return (trav)
- 題目
	- [[148. SortList - Main]]

##### n-th Node from Tail Valid Node
- 觀念
	- 需要使用 augmentedHead
	- 需要使用 slow / fast ptr
		- fast ptr 先走到 head 開始 (n+1) -> **搭配上面的 n-th Node from current node 模板**
		- slow ptr 再和 fast ptr 一起走 -> **fast ptr 停在 last valid node** 的時候，slow ptr 就是 **位在 n-th node fram tail 的qian前一個**
- 模板
	- Init augmented Head
		- augmentedHead
		- augmentedHead->next = head
	- Fast ptr traverse N nodes
		- fast = **使用上面的『嚴格 n-th node from start 模板，augmentedHead 開始往後走 n+1 個』** = getKthNodeFromStart(&augmentedHead, n+1)
	- Slow ptr traverse with Fast ptr until fast reach last valid tail
		- slow = &augmentedHead
		- while( fast && fast->next )
			- slow = slow->next
			- fast = fast->next
	- n-th node from tail = **next of slow ptr**
		- NthNodeFromTail = slow->next
- 題目
	- [[19. Remove Nth Node From End of List - Main]]

##### Link List 中間某一段剪下來
- 概念
	- 需要先記錄 boundary node
		- node before cut off
		- node after cut off
	- 需要記錄剪下來那段當下的 head / tail
		- cut off head
		- cut off tail
	- 需要把要處理的段落剪下來
		- node before cut off head -> next = nullptr
		- cut off tail -> next = nullptr
- 模板
	- 中間某一段剪下來: CutOffKNodeSubList(nodePrevToCutOff, k, Node\*& cutOffHead, Node\*& cutOffTail, Node\*& nodeAfterCutOff)
		- 取得 cut off origin range
			- cutOffHead = nodePrevToCutOff->next
			- cutOffTail = **使用先前的 K-th node from start 模板** = getKthNodeFromStart(cutOffHead, k)
		- 取得 tail boundary
			- nodeAfterCutOff = cutOffTail->next
		- 執行 cut off
			- nodePrevToCutOff->next = nullptr
			- cutOffTail->next = nullptr
- 題目
	- [[148. SortList - Main]]
	- [[25. Reverse Nodes in K-Group - Main]]

##### Link List 中間某一段剪下來處理後放回去
- 概念
	- 使用先前的『**中間某一段剪下來的模板**』
		- prevNodeToCutOff
		- cutOffHead
		- cutOffTail
		- nodeAfterCutOff
	- 處理剪下來的那段 + 記錄new head / tail
		- new cut off head
		- new cut off tail
	- 剪下來的那段接回去
		- node before cut off->next = new cut off head
		- new cut off tail->next = node after cut off
- 模板
	- 使用 augmented head
		- augmentHead(0, head)
	- 初始化 node before cut off -> **走到要開始 cut off 的地方**
		- nodeBeforeCutOff = **搭配上面的 n-th Node from current node 模板** = getKthNodeFromStart(&augmentedHead, n+1)
	- 把要處理的部分切下來
		- CutOffKNodeSubList(nodePrevToCutOff, k, Node\*& cutOffHead, Node\*& cutOffTail, Node\*& nodeAfterCutOff)
	- 切下來的部分進行處理
		- ( new cutoff head , new cutoff tail ) = proceed(cutOffHead, cutOffTail )
	- 處理完接回去
		- nodePrevToCutOff->next = new cutoff head
		- new cutoff tail->next = nodeAfterCutOff

- 題目
	- [[25. Reverse Nodes in K-Group - Main]]
	- [[148. SortList - Main]]

#### Array Link List
- 觀念
	- nums.size() = N
	- nums[i] 裏面每個數字的範圍在 1 to N-1 之間 -> **每個 nums[i] 指向另外一個 nums idx**
	- 每個 index -> **可以視爲 node**
	- nums[ idx ] -> **可以視爲 node->next**
- Traverse
	- traverse from head 
		- ptr = 0 (初始位置在 head = idx 0)
		- ptr = nums[ptr] -> **nums[ptr] 等於 ptr->next**
	- cycled link list
		- slow fast ptr from head
			- slow = 0
			- fast = 0
		- slow fast ptr traverse to meet node
			- while(true)
				- slow = nums[slow]
				- fast = nums[ nums[fast] ]
				- if(slow == fast) break
			- meetNode = slow
		- slow ptr traverse from head & meetNode traverse at the same time
			- slow = 0
			- while(true)
				- slow = nums[slow]
				- meetNode = nums[meetNode]
				- if(slow == meetNode) break -> **meetNode->next = slow->next = duplicate node**
			- **duplicateNode = slow**
- 題目
	- [[287. Find the Duplicate Number - Main]]

#### Cycled Link List
- 觀念
	- cycled node -> **有兩個不同的 node->next 指向同一個地方**
- 模板
	- init slow / fast ptr
		- slowPtr = head
		- fastPtr = head
	- Traverse to meet point if cycle: while(fastPtr && fastPtr->next)
		- trav slow
			- slowPtr = slowPtr->next
		- trav fast
			- fastPtr = fastPtr->next->next
		- stop if slow = fast -> **先 traverse 再檢查 slow = fast，否則一開始還沒 traverse 就會直接 slow = fa s t 誤判**
			- if( slowPtr = fastPtr) break
	- init new trav node from head
		- node = head
	- Re-Traverse to cycled point: while(node)
		- stop if trav node = slow
			- if( node = slowPtr ) break
		- trav slow
			- slowPtr = slowPtr->next
		- trav node from head
			- node = node->next
	- Record cycled point
		- cycleNode = node
- 題目
	- [[141. Linked List Cycle - Main]]
	- [[287. Find the Duplicate Number - Main]]

#### two list merge
- 模板
	- Helper Func - CmpNode
		- Node \*& FuncSelectNode( Node \*&node1, Node \*&node2 )
		- **helper function 也可以做比較複雜的運算**
	- 初始化一個 merged list
		- Node augmentedHead;
		- Node \*mergedNode = &augmentedHead
	- 執行 merge
		- while( node1 || node2 )
			- 比對 node 資訊並且選其中一個連到 merged list
				- Node \*&selectNode = CmpAndSelectNode( node1, node2 )
				- mergedNode->next = selectNode
			- Traverse MergeNode & selectedNode
				- mergedNode = mergedNode->next
				- selectNode = selectNode->next
			- if( !node1 || !node2 ) && (**special requirements**)  -> *條件允許的情況下把另外一個 list 剩餘部分接到 merge list 並結束*
				- mergedNode->next = (node1) ? (node1) : (node2)
				- break
		- **最後 mergedNode 會停在 last valid tail node**
	- 執行 Post Add Node
		- if( **need additional node** ) -> 如果 merge 後需要額外的 node
			- mergedNode->next = new Node( *some value* )
	- 完成
		- return augmentedHead**.next**
- 題目
	- [[21. Merge Two Sorted Lists - Main]]
	- [[2. Add Two Numbers - Main]] -> **helper function 做複雜運算

#### Multiple List Merge
- 模板
	- Helper Func - CmpNode
		- Node \*& FuncSelectNode( Node \*&node1, Node \*&node2 )
	- Helper Func - merge two lists
		- **使用上面 merge two list 模板**
	- 檢查是否 lists valid
		- if(lists.empty()) return nullptr
	- 初始化一個 merged list
		- Node augmentedHead;
		- Node \*mergedNode = &augmentedHead
	- 執行 merge - 兩個兩個合併 -> *一直merge直到剩下一個 list*
		- remainListNum = lists.size()
		- while(remainListNum > 1)
			- 前 + 後 list 合併，存到前面的位子: for(int l = 0, r = lists.size()-1; l < r; l++, r--)
				- lists[l] = merge two lists( lists[l], lists[r] )
				- remainListNum--
	- 完成 -> 最後存在 lists\[0\]
		- return lists[0]
- 題目
	- [[23. Merge K Sorted Lists - Main]]
	- [[148. SortList - Main]] - **merge sort**

#### Ringed Linked List
- 概念
	- 特殊 ring queue 處理機制
	- 使用一個 ringed link list
		- 雙向 link list 快速查找
	- entry node 是額外擴充的，作為入口點
		- entry node prev = tail
		- entry node next = head
- 模板
	- init -> *entry node 自成一環*
		- entryNode->prev = *entry node*
		- entryNode->next = *entry node*
	- Add node to new Head / Tail -> *entry node 後面 / 前面 新增一個 node*
		- nodePrevToInsert = 
			- add new Head: entryNode
			- add new Tail: entryNode->prev
		- nodeAfterInsert
			- nodeAfterInsert = nodePrevToInsert->next
		- build new next link
			- nodePrevToInsert->next = insertNode
			- (nodePrevToInsert->next)->next = nodeAfterInsert
		- build new prev link
			- nodeAfterInsert->prev = insertNode
			- (nodeAfterInsert->prev)->prev = nodePrevToInsert
	- TakeOutNode From Head / Tail -> *entry node 後一個 / 前一個 node 拿掉*
		- 如果只剩下entryNode：if(entryNode->next == entryNode) return
		- nodePrevToTakeOut = 
			- takeout old Head: entryNode
			- takeout old Tail: entryNode->prev->prev
		- nodeAfterTakeOut
			- nodeAfterTakeOut = nodePrevToTakeOut->next->next
		- fetch node to take out
			- takeOutNode = nodePrevToTakeOut->next
		- build new next / prev link
			- nodePrevToTakeOut->next = nodeAfterTakeOut
			- nodeAfterTakeOut->prev = nodePrevToTakeOut
		- old node dis-connect
			- takeOutNode->next = nullptr
			- takeOutNode->prev = nullptr


### Linked List

| #   | NeetCode | Problem                                                                                                 | Difficulty | Solution                                                               | Status      | Review | Review 2nd | Note                                            |                                                                                          |
| --- | -------- | ------------------------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------------------- | ----------- | ------ | ---------- | ----------------------------------------------- | ---------------------------------------------------------------------------------------- |
| 35  | 150      | [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)                          | Easy       | [Link](https://neetcode.io/solutions/reverse-linked-list)              | Finish 7/03 | 9/19   | 11/26      | [[206. Reverse Linked List - Main]]             |                                                                                          |
| 36  | 150      | [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)                     | Easy       | [Link](https://neetcode.io/solutions/merge-two-sorted-lists)           | Finish 7/03 | 9/19   | 11/26      | [[21. Merge Two Sorted Lists - Main]]           | **練習 refernce to pointer (1st)** / 模板化寫法 (2nd)                                           |
| 37  | 150      | [143. Reorder List](https://leetcode.com/problems/reorder-list/)                                        | Medium     | [Link](https://neetcode.io/solutions/reorder-list)                     | Finish 7/03 | 9/19   | 11/28      | [[143. Reorder List - Main]]                    | **比較難，需要複習(1st)** / *可以練很多操作 (2nd)*                                                      |
| 38  | 150      | [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) | Medium     | [Link](https://neetcode.io/solutions/remove-nth-node-from-end-of-list) | Finish 7/04 | 9/19   | 11/28      | [[19. Remove Nth Node From End of List - Main]] | **偏難，要想好 boundary cond (1st)** / 值得練習 (2nd)                                              |
| 39  | 150      | [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)      | Medium     | [Link](https://neetcode.io/solutions/copy-list-with-random-pointer)    | Finish 7/04 | 9/19   | 11/28      | [[138. Copy List with Random Pointer - Main]]   | **執行流程要想清楚(1st)** / *使用 Graph Copy 模板 (2nd)*                                             |
| 40  | 150      | [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)                                    | Medium     | [Link](https://neetcode.io/solutions/add-two-numbers)                  | Finish 7/05 | 9/19   | 11/26      | [[2. Add Two Numbers - Main]]                   | **模板化寫法練習 (2nd)**                                                                        |
| 41  | 150      | [141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)                              | Easy       | [Link](https://neetcode.io/solutions/linked-list-cycle)                | Finish 7/05 | 9/19   | 11/26      | [[141. Linked List Cycle - Main]]               | 模板化寫法，注意 check slow = fast 的位置 (2nd)                                                     |
| 42  | 150      | [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)              | Medium     | [Link](https://neetcode.io/solutions/find-the-duplicate-number)        | Finish 7/05 | 9/20   | 11/27      | [[287. Find the Duplicate Number - Main]]       | **很難，要複習(1st)** / **還是需要想一下 (2nd)**                                                      |
| 43  | 150      | [146. LRU Cache](https://leetcode.com/problems/lru-cache/)                                              | Medium     | [Link](https://neetcode.io/solutions/lru-cache)                        | Finish 7/05 | 9/20   | 11/27      | [[146. LRU Cache - Main]]                       | **很難，容易搞錯 (1st)** / *熟悉度還沒那麼足夠 (2nd)*                                                    |
| 44  | 150      | [23. Merge K Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)                         | Hard       | [Link](https://neetcode.io/solutions/merge-k-sorted-lists)             | Finish 7/05 | 9/20   | 11/26      | [[23. Merge K Sorted Lists - Main]]             | **概念沒有很難，但很多細節容易出錯**<br>**練習用 reference to pointer 來實作 list merge (1st)** / 通用模板練習 (2nd) |
| 45  | 150      | [25. Reverse Nodes in K-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)                 | Hard       | [Link](https://neetcode.io/solutions/reverse-nodes-in-k-group)         | Finish 7/05 | 9/20   | 11/28      | [[25. Reverse Nodes in K-Group - Main]]         | **實作複雜 (1st)** / **必練3rd，多重模板運用(2nd)**                                                   |
| 148 |          | [148. Sort List](https://leetcode.com/problems/sort-list/description/)                                  | Medium     |                                                                        | Finish 9/20 | 9/20   | 11/28      | [[148. SortList - Main]]                        | **練習 merge sort (1st)** / **必練3rd，多重模板運用 (2nd)**                                         |
