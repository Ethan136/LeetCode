---
LeetCodeSeq: 9
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 7
LeetCode150ConceptOk: 7
LeetCode150TestPass: 7
LeetCode150Finish: 7
LeetCode150Review: 7
LeetCode150Rev2: 7
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 5
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
### Concept
#### Double Heap (min-max)
- 概念
	- 隨時取得最小的 n-th
		- max heap: 放最小的 N 個
		- min heap: 放剩餘更大的 -> **非必要**
	- 隨時取得最大的 n-th
		- max heap：放剩餘更小的 -> **非必要**
		- min heap：放最大的 N 個
	- 隨時取得 mid
		- max heap：minHalfHeap - 放最小的一半數字
			- **number cnt = odd 的時候放 mid**
			- **number cnt = even 的時候放 left mid**
		- min heap：maxHalfHeap - 放最大的一半數字
			- **number cnt = even 的時候放 right mid**
		- 再用一個額外變數記得當下 num cnt 是 odd / even
- 速記
	- **min heap -> compare max -> max K-th (K-th on top)**
	- **max heap -> compare min -> min K-th (K-th on top)**
- 維護方式
	- 最小的 n-th
		- 加入數字的時候
		- 如果比 max Heap 裡面的 smallest n-th 大 -> 直接加入 min heap
		- 如果比 max Heap 裡面的 smallest n-th 小 -> 加入 max heap 更新 min n，然後 max heap pop 一個出來，換到 min heap
	- 最大的 n-th
		- 加入數字的時候
		- 如果比 min Heap 裡面的 max n-th 小 -> 直接加入 max heap
		- 如果比 min Heap 裡面的 max n-th 大 -> 加入 min heap 更新 max n，然後 min heap pop 一個出來，換到 max heap
	- middle value
		- 加入數字的時候
		- 如果加入數字前是 odd num cnt -> *舊的 mid 在 minHalfHeap (max heap)* -> **加入 new num 後變成偶數：加到左邊，擠出一個到右邊當 new double right mid**
			- new num 先加到 minHalfHeap 用來和『加入 new num 前的 old mid 比較』
			- 然後 minHalfHeap 的 top 傳遞給 maxHalfHeap -> **new num / old mid 比較後比較大的，傳遞到 maxHalfHeap**
		- 如果加入數字前是 even num cnt -> *新的 mid 在 maxHalfHeap (min heap)* -> **加入 new num 後變成奇數：加到右邊，擠出一個到左邊當 new single mid**
			- new num 先加到 maxHalfHeap 用來和『加入 new num 前的 right mid 比較』
			- 然後 maxHalfHeap 的 top 傳遞給 minHalfHeap -> **new num / old right mid 比較後比較小的，傳遞到 minHalfHeap**
- 模板：K-th
	- 宣告 Heap (*compare large - max k-th*) / maxHeap (*compare min - min k-th*)
		- cmpFunc: 比對資料結構 或是 **`less<int>`** / **`greater<int>`**
		- minHeap (cmp large / max k-th) 或 maxHeap (cmp min / min k-th)
	- 把 node 加入 heap: for( each node )
		- if( heap.size() < k ): add node to heap
		- if( node **不會**影響 heap ): ignore this node
			- **max k**: node < heap.top()
			- **min k:** node > heap.top()
		- else ( node **會影響 heap** ): update heap
			- heap.push( node )
			- heap.pop()
- 模板：middle value
	- 宣告 Heap
		- minHalfHeap (max heap 裝 min value)
		- maxHalfHeap (min heap 裝 max value)
		- m_numCnt
	- 加入數字的時候
		- 加入數字到 heap
			- 如果加入數字前是奇數-> **加入 new num 後變成偶數：加到左邊，擠出一個到右邊當 new double right mid**
				- minHalfHeap.push( new num )
				- maxHalfHeap.push( minHalfHeap.top() )
				- minHalfHeap.pop();
			- 如果加入數字前是偶數-> **加入 new num 後變成奇數：加到右邊，擠出一個到左邊當 new single mid**
				- maxHalfHeap.push( new num )
				- minHalfHeap.push( maxHalfHeap.top() )
				- maxHalfHeap.pop()
		- 更新 number cnt
			- m_numCnt++
- 題目
	- [[703. Kth Largest Element in a Stream - Main]]
	- [[215. Kth Largest Element in an Array - Main]]
	- [[973. K Closest Points to Origin - Main]]
	- [[295. Find Median from Data Stream - Main]] -> **必練**

#### Priority Queue Scheduling
- 概念
	- 從 task types 裡面找從剩餘最多 / 最少 task cnt 的開始 schedule
	- **每一輪一種 task type 只能處理一次，每一輪有限制可以處理的 task 數量**
	- 每次 schedule 後減少 remain task cnt
	- 並且處理後的 task type，如果還要 task cnt -> **下一輪繼續處理**
	- 當輪沒處理完的 task types，全部要轉換到 next term arrangement
- 模板
	- 初始化 arbiter
		- thisTermHeap
		- nextTermHeap
	- all tasks 放到 heap 裡面
		- thisTermHeap.push( taskInfo )
	- 分配 tasks
		- while( thisTermHeap.size() )
			- **處理這一輪的 scheduling**： for( int i = 0; i < **taskNumOneTerm**; i++)
				- if( thisTermHeap.empty() && nextTermHeap.empty() ) -> *break: all tasks finished 結束 scheduling*
				- if( thisTermHeap.empty() ) -> *continue: 要等這一輪跑完，才能開始下一輪 scheduling*
				- **處理 task**
					- taskInfo = thisTermHeap.top()
					- taskInfo.taskCnt--
				- **還有剩餘task放到 next term heap**
					- if(taskInfo.taskCnt) nextTermHeap.push( taskInfo )
			- **這一輪剩下的 task 放到下一輪**
				- while( thisTermHeap.size() )
					- nextTermHeap.push( thisTermHeap.top() )
					- thisTermHeap.pop()
			- **this term / next term 對調**
				- swap( thisTermHeap, nextTermHeap )
- 題目
	- [[621. Task Scheduler - Main]]

### Heap / Priority Queue

#### LeetCode 150


| #   | Problem                                                                                                | Difficulty | Solution                                                              | Pass | Finish | Review | Review2 | Note                                                                               |
| --- | ------------------------------------------------------------------------------------------------------ | ---------- | --------------------------------------------------------------------- | ---- | ------ | ------ | ------- | ---------------------------------------------------------------------------------- |
| 64  | [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/) | Easy       | [Link](https://neetcode.io/solutions/kth-largest-element-in-a-stream) | 7/01 | 9/23   | 9/23   | 11/29   | [[703. Kth Largest Element in a Stream - Main]] - 之後要再練一下 (2nd)                    |
| 65  | [1046. Last Stone Weight](https://leetcode.com/problems/last-stone-weight/)                            | Easy       | [Link](https://neetcode.io/solutions/last-stone-weight)               | 7/01 | 9/23   | 9/23   | 11/29   | [[1046. Last Stone Weight - Main]]                                                 |
| 66  | [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)           | Medium     | [Link](https://neetcode.io/solutions/k-closest-points-to-origin)      | 7/01 | 9/23   | 9/23   | 11/29   | [[973. K Closest Points to Origin - Main]]                                         |
| 67  | [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) | Medium     | [Link](https://neetcode.io/solutions/kth-largest-element-in-an-array) | 7/02 | 9/23   | 9/23   | 11/29   | [[215. Kth Largest Element in an Array - Main]] - 之後要再練一下 (2nd)                    |
| 68  | [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/)                                   | Medium     | [Link](https://neetcode.io/solutions/task-scheduler)                  | 7/03 | 9/24   | 9/24   | 11/29   | [[621. Task Scheduler - Main]] - **難題，必須要複習(1st)** / **細節還要更熟悉 (2nd)**             |
| 69  | [355. Design Twitter](https://leetcode.com/problems/design-twitter/)                                   | Medium     | [Link](https://neetcode.io/solutions/design-twitter)                  | 7/03 | 9/24   | 9/24   | 11/30   | [[355. Design Twitter - Main]] - **實作複雜，必須練習(1st)** / *不是最佳解，但想起來比較直覺(2nd)*        |
| 70  | [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)       | Hard       | [Link](https://neetcode.io/solutions/find-median-from-data-stream)    | 7/03 | 9/24   | 9/24   | 11/30   | [[295. Find Median from Data Stream - Main]] - **情況判斷容易搞錯(1st)** / *模板化寫法練習 (2nd)* |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 1834 | [1834. Single Threaded CPU](https://leetcode.com/problems/single-threaded-cpu/) | Medium | [Link](https://neetcode.io/solutions/single-threaded-cpu) | | | | | |
| 767 | [767. Reorganize String](https://leetcode.com/problems/reorganize-string/) | Medium | [Link](https://neetcode.io/solutions/reorganize-string) | | | | | |
| 1405 | [1405. Longest Happy String](https://leetcode.com/problems/longest-happy-string/) | Medium | [Link](https://neetcode.io/solutions/longest-happy-string) | | | | | |
| 1094 | [1094. Car Pooling](https://leetcode.com/problems/car-pooling/) | Medium | [Link](https://neetcode.io/solutions/car-pooling) | | | | | |
| 502 | [502. IPO](https://leetcode.com/problems/ipo/) | Hard | [Link](https://neetcode.io/solutions/ipo) | | | | | |
