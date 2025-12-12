---
LeetCodeSeq: 5
LeetCode150Finish: 7
LeetCode150Num: 7
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150ConceptOk: 7
LeetCode150TestPass: 7
LeetCode150Review: 7
LeetCode150Rev2: 7
---
### Concept
#### 先決條件
- 是 **需要搜尋的題目，但希望不要用 linear search**
- 是 **一旦搜尋了任何一個位子，可以依照搜尋結果，馬上知道下一次要搜尋哪個方向** 的情況 

#### 執行模板：單一 Section - Head / Tail Valid -> 收斂後檢查 mid 和 mid+1
- 初始化 - 不用特別設值，因為 binary search for loop 會設定
	- head: **不一定是搜尋範圍的 first entry，必須是『某種概念上的 lower / upper bound』**
		- head
	- tail: **不一定是搜尋範圍的 last entry，必須是『某種概念上的 upper / lower bound』
		- tail
	- mid: 初始化即可，但不用特別設值，因為 binary search for loop 會設定
		- mid
- Binary Search
	- for( INITIAL_COND; CONTINUE_COND; UPDATE_MID )
		- INTIAL_COND
			- head = valid lower bound
			- tail = valid upper bound
		- CONTINUE_COND
			- 非線性儲存 entry (*完整概念*): **head 和 tail 距離為 2 以上**
			- 線性儲存 entry (簡化的結果): head < (tail - 1) -> **最後收斂到 head = tail 或 head, tail 並排，就算結束**
		- UPDATE_MID
			- 非線形儲存 entry (*完整概念*): **mid 更新為 head / tail 的中間**
			- 線性儲存 entry (簡化的結果): mid = (head + tail) / 2
	- for 內部結構
		- if( Val(mid) == target ) -> **找到目標**
			- early return mid
		- if(  **Val( mid ) = \[Val( head ), target\)**  )  -> mid idx 取得的數值，在 (head 對應數值 ~ target) 之間 
			- -> **代表 target 在 Val(mid) to Val(tail) 之間** -> **更新 head 到 mid
				- head = mid
		- else -> mid idx 取得的數值，在 (target ~ tail ) 之間
			- -> **代表 target 在 Val(head) to Val(mid) 之間** -> **更新 tail 到 mid**
				- tail = mid
		- **注意：如果是 non linear entry storage，通常需要一個額外 func 檢查下列情況**
			- helper func 檢查 Val( mid ) == target
			- helper func 檢查 Val( mid ) \[ Val( head ), Target ) 之間
- Final Check -> **如果 binary search 最後收斂到 head, tail 並排，才會走這邊**
	- 說明：**head / tail 都是 valid，而且 mid = (head + tail) / 2 的情況下，最後可能無法收斂到單一數值**
		- 比如 head = 2, tail = 3 -> mid 算出來是2 
		- -> **假如 Val(mid) = \[ Val(head), target ] aka 這個情況下 target 在 Val(tail)** -> 但 head 只能更新到 mid -> mid 依舊是 2
	- 執行
		- if( Val(head) == target ) -> 檢查 head 是否為 solution (**在 head / tail 並排情況下，head = mid**) -> 是的話 return head
			- return head
		- if( Val(tail) == target ) -> 檢查 tail 是否為 solution (在 head / tail 並排情況下，tail = mid+1) -> 是的話 return mid
			- return mid
		- **如果走到這邊，則代表無解**
			- return "INVALID"
- 題目
	- Binary Search 基本類型
		- [[704. Binary Search - Main]]
		- [[74. Search a 2D Matrix - Main]]
	- Binary Search 概念應用
		- [[875. Koko Eating Bananas - Main]]
	- 特殊的終止條件
		- [[981. Time-Based Key-Value Store - Main]]
		- [[4. Median of Two Sorted Arrays - Main]]

#### 執行模板：多重 sub-Section - Head / Tail Valid -> 先讓 Target 和 Mid 收斂到同一個 sub-Section
- 情況
	- Head - Tail 之間不是線性關係，類似說 *[ Val(head) , Val(tail) ] 不是線性排列*
	- **但 [ Val(head) , Val(tail) ] 之間可以切成多個線性排列的 sub-section [ Val(head) , Val(X)], [Val(X+1), Val(tail)]**
		- [ Val(head) , Val(X)] 是一個線性區間
		- [Val(X+1), Val(tail)] 是一個線性區間
		- 但 **X** 的位子不知道
	- 這時候必須要符合下列條件，才能用 binary search
		- **要能夠從 Val(head) / Val(tail) / Target  判斷 Target 在哪個區間**
		- **要能夠從 Val(head) / Val(tail) / Val(Mid) 判斷 mid 在哪個區間**
- 流程
	- 階段1：先用 binary search 讓 Val(Mid) 和 Target 在同一個區間
	- 階段2：再用 binary search 在 Val(Mid) , Target 所在的區間中，執行數值比對的基本 binary search
	- 上面兩個階段，可能沒辦法拆開，而是寫在同一個 binary search 架構裡面
- 模板
	- for(head = 0, tail = end, mid = (head+tail)/2; head < (tail - 1); mid = (head+tail)/2 )
		- if(Val(mid) == target) return mid
		- if(mid 和 target 位在不同 section ) -> *mid 所在的 section 調整*
			- 更新 head / tail 來讓 mid 往另外一個 section 移動
		- else (mid 和 target 在同一個 section) -> *一般 binary search 作法*
			- if(Val(mid) < target) head = mid
			- else (target < Val(mid))tail = mid
- 題目
	- [[33. Search in Rotated Sorted Array - Main]]
	- [[153. Find Minimum in Rotated Sorted Array - Main]]


### Binary Search

| #   | Problem                                                                                                          | Difficulty | Solution                                                                   | Status      | Review | Review2nd | Note                                                                                                                  |
| --- | ---------------------------------------------------------------------------------------------------------------- | ---------- | -------------------------------------------------------------------------- | ----------- | ------ | --------- | --------------------------------------------------------------------------------------------------------------------- |
| 28  | [704. Binary Search](https://leetcode.com/problems/binary-search/)                                               | Easy       | [Link](https://neetcode.io/solutions/binary-search)                        | 6/15 Finish | 9/17   | 12/10     | [[704. Binary Search - Main]]<br>*基本模板寫法 (2nd)*                                                                       |
| 29  | [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/description/)                          | Medium     | [Link](https://neetcode.io/solutions/search-a-2-d-matrix)                  | 6/15 Finish | 9/17   | 12/10     | [[74. Search a 2D Matrix - Main]]<br>*index 轉換 + 模板化寫法 (2nd)*                                                         |
| 30  | [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)                                   | Medium     | [Link](https://neetcode.io/solutions/koko-eating-bananas)                  | 6/16 Finish | 9/17   | 12/10     | [[875. Koko Eating Bananas - Main]]<br>**難題，很難想到 (1st)**<br>*變形的 binary search -> 先思考 linear search (2nd)*            |
| 31  | [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)              | Medium     | [Link](https://neetcode.io/solutions/search-in-rotated-sorted-array)       | 6/16 Finish | 9/17   | 12/10     | [[33. Search in Rotated Sorted Array - Main]]<br> **很難，條件判斷不容易簡化(1st)**<br>**必須先分 section，再看情況做 binary search (2nd)** |
| 32  | [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) | Medium     | [Link](https://neetcode.io/solutions/find-minimum-in-rotated-sorted-array) | 6/16 Finish | 9/18   | 12/11     | [[153. Find Minimum in Rotated Sorted Array - Main]]<br>*模板化寫法 (2nd)*                                                 |
| 33  | [981. Time-Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)                     | Medium     | [Link](https://neetcode.io/solutions/time-based-key-value-store)           | 6/16 Finish | 9/18   | 12/11     | [[981. Time-Based Key-Value Store - Main]]<br>*物件實作練習 + 特殊終止條件 (2nd)*                                                 |
| 34  | [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)                     | Hard       | [Link](https://neetcode.io/solutions/median-of-two-sorted-arrays)          | 6/16 Finish | 9/19   |           | [[4. Median of Two Sorted Arrays - Main]]<br>**太複雜，複習2nd先跳過**                                                         |
