---
LeetCodeSeq: 10
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage|NeetCode 150 MainPage]]"
LeetCode150Num: 9
LeetCode150ConceptOk: 9
LeetCode150TestPass: 9
LeetCode150Finish: 9
LeetCode150Review: 9
LeetCode150Rev2: 9
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 7
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---

### Concept

#### General Structure
- check valid setting
	- 檢查 index valid -> **如果 terminate condition 同時也達成，則可能要先考慮 terminate condition**
	- **需要檢查的  setting 如果 terminate condition 不會用到，則先檢查 terminate condition**
- terminate condition - store result
	- 某個條件符合的時候儲存結果
	- return
- for loop / other kind
	- call recursive

#### All Possible Arrangement - 排列
- 概念
	- 考慮各種順序排列
	- element 可能重複 or 不重複
	- 因爲是『任意順序排列』，所以沒辦法從 start idx 一路往後排，而是有可能 traverse idx 不照順序 -> **每次 DFS 都從 idx 0 開始走，中間有走過的就跳過**
- 模板
	- getAllArrangement(array, needNum, curResult, allResultSet)
		- if(needNum = 0) -> *不需要新的 element 了，走完的是這個情況*
			- allResultSet.push_back( curResult )
			- return
		- for( idx 0 to end in array )
			- 檢查是否走過
				- if( array[i] == MARK_TRAVERSED_NUM ) continue
			- 記錄 traverse
				- arrayNum = array[i] -> *backup element value*
				- array[i] = MARK_TRAVERSED_NUM -> *記錄已經走過了*
			- 執行下一次 traverse
				- getAllArrangement( array, needNum-1, curResult, allResultSet )
			- 還原 traverse
				- array[i] = arrayNum
- 題目
	- [[46. Permutations - Main]]

#### SubSets - 組合
- 概念
	- 考慮各種 sub-set size
	- 考慮各種 number 可以重複 or 不能重複的情況
	- 考慮邊界條件 -> **start idx = invalid 的情況，有可能是 sub-set 剛好塞滿** -> **這個題型的 result save 不一定用到 startIdx -> startIdx 通常不用先檢查**
	- **基本模板是不要在 DFS Recursive 加上 true / false return -> 加上這個會複雜很多（容易在一些邊界條件搞錯） -> 先弄基本的，有需求再優化**
- 模板
	- getRepeatNumFromIdx( nums, idx )
		- if(idx >= nums.size()) 
			- return 0
		- repeat = 1
		- for(i = idx+1 to nums.size()-1 )
			- if(nums[i] != nums[idx]) break
			- repeat++
		- return repeat
	- getSubSetsFromIdx( nums, startIdx, needElmtNum (*target*), allSubSets, curSubSet)
		- 概念
			- **從 nums 的 startIdx 開始
			- **依照 needElementNum 把 num 加到 curSubSet**
			- **最後存到 allSubSets**
		- 引數
			- 如果是 array 裏面的數字任意湊 set: needElmtNum
			- 如果是 array 裏面的數字湊 target num: target
		- Code
			- **terminate condition -> 這個要在 startIdx valid 前判斷，因爲可能塞了最後一個 element 後剛好塞滿，並且 next**
				- **array 裏面數字任意湊 set**： if( needElmtNum == 0)
					- allSubSets.push_back( curSubSet )
					- **如果數字有正有負 -> 則有可能正負相消而延伸出多重組合 -> 這邊則不 early return，而是一直計算直到 startIdx = vector end 才停止**
					- **如果數字只有正 -. 則一旦發生 needElmtNum = 0，後續數字一定不會再湊出 needElmtNum = 0 的情況 -> early return**
				- **array 裏面數字湊 target num**
					- 情況1： if( target < 0 ) -> *如果數字都是正的，target < 0 -> 代表後續湊不出來了 -> early return*
					- 情況2： if( target == 0) -> **目標數字湊到了，如果數字有排序過，後續只會是『全部正的』，或『全部負的』 -> 儲存 curSubSet 到 allSubSets**
			- 執行 recursive 測試各種組合
				- for( i = startIdx, **repeatCnt = 0**; i < nums.size(); **i+=repeatCnt** )
					- **rrepeatCnt** = getRepeatNumFromIdx(nums, i)
					- for( r = 1, needCnt = 0; r <= **repeatCnt**; r++) -> **如果 nums 有重複數字 -> 要顯式在同一個 recursive layer try 各種重複量**
						- **這邊可以加速
							- 如果是數字湊 set： if( ( needElementNum - **r** ) < 0 ) break
							- 如果是數字湊 targetNum： if( ( target - **r \* nums[i]** ) < 0 ) break
						- **push to subset repeatedly**
							- needCnt = r
							- while( **needCnt--**) curSubSet.push_back( nums[ i ] )
						- **try next num**
							- 如果是 array 裏面數字任意湊 set：getSubSets( nums, i + **repeat num**, needElementNum - **r**, allSubSets, curSubSet)
							- 如果是 array 裏面數字湊 target num: getSubSets( nums, i + **repeat num**, target - **r \* nums[i]**, allSubSets, curSubSet)
						- **pop from subset repeatedly**
							- needCnt = r
							- while(**needCnt**) curSubSet.pop_back()
	- 大結構: **for loop 處理各種 subset size**
		- 初始化
			- allSubSets
			- curSubSet.reserve(nums.size()) -> **預留空間，後續做 push / pop 速度快很多**
		- 準備階段
			- **如果 nums 有重複數字 -> 要先排序**
		- 處理各種 sub sets
			- for( subSetSize = 0 to nums.size )
				- getSubSetsFromIdx(nums, 0, subSetSize, allSubSets, curSubSet )
- 題目
	- [[78. Subsets - Main]]
	- [[90. Subsets II - Main]]
	- [[39. Combination Sum - Main]]
	- [[40. Combination Sum II - Main]] - **需要把 repeat num 的情況加速**

#### String Traverse
- 概念
	- 從 string 開頭，一次 traverse 一個或多個 char，走到 string 尾端
	- 一次 traverse 一個或多個 char -> **這個是題目給定的條件來決定**
		- **可以設定當前走的範圍就是 (l, r) -> (l, r) 都是當前走『過』的，走過 (l, r) 後，下一次走 (r+1, ...)**
		- **(l, r) 一開始重複在同一個位置 start Idx**
	- 可能需要記錄 traverse 途中的軌跡（也就是每次 traverse 走的 index 把原始 string 切分多段）
- 模板
	- DFS Traverse
		- travCheckWord(word, startIdx, curTravPartition, allTravPartitions) -> **找出從 startIdx 作爲起始點，走到 word end 的所有 partition 軌跡**
			- if(startIdx >= word.size()) -> **條件符合情況下才走，走到 word end -> 記錄當下的 traverse 軌跡到 result set**
				- allTravPartitions.push_back( curTravPartition );
			- for(int l = startIdx, r = startIdx; r < word.size(); r++) -> **嘗試從 startIdx 一次走 1 格, 2格, ... N 格一步走到 word end**
				- 檢查當前 (l , r) 跨距是否可以走
					- if( !ConditionCheckFunc(word, l, r) ) continue -> *如果沒辦法一次走這麼多格，就跳過這個 (l, r) 格距跨度，嘗試下一個*
					- curTravPartition.push_back(word.substr(l, r-l+1)) -> 如果當前的 (l, r) 是可以這樣走，則記錄到當前的 traverse path
				- DFS Recursive 檢查 (l, r) 走完後，**下一次從 r+1 開始走**
					- travCheckWord(word, r+1, curTravPartition, allTravPartitions )
				- DFS Recursive 在 (r+1) 以後的走完後，把當前的 traverse path 退掉
					- curTravPartition.pop_back()
	- 主結構
		- Init
			- 當次 traverse 的軌跡: curTravPartition
			- 所有 traverse 的軌跡組：allTravPartitions
		- 取得 word 從頭到位的所有走法
			- travCheckWord(word, 0, curTravPartition, allTravPartitions)
- 題目
	- [[131. Palindrome Partitioning - Main]]

#### 2D Board + Mark + Traverse 類型
- 有點難說明
	- 總之是 traverse path + mark + 對角線 mark 的類型
	- **Traverse 不一定要以 grid 爲單位，也可以『row 爲單位』 -> 每次 traverse 進到下一層 row，在 DFS func 裏面執行 for loop 檢查 row 裏面每一個 grid**
- 觀念
	- **如果要檢查對角線 row + col = N 及 row - col = N 的情況 -> 使用 unordered_map 比 vector 方便很多 ！！**
	- **正、負對角線，要用兩個獨立的 map**
	- vector 處理對角線，需要做 index shift -> 麻煩
- 題目
	- [[51. N Queens - Main]]

### Backtracking

#### LeetCode 150


| #   | Problem                                                                                                           | Difficulty | Solution                                                                    | Solve | Note | Review | Review 2nd | Note                                                                                                                                |
| --- | ----------------------------------------------------------------------------------------------------------------- | ---------- | --------------------------------------------------------------------------- | ----- | ---- | ------ | ---------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| 71  | [78. Subsets](https://leetcode.com/problems/subsets/)                                                             | Medium     | [Link](https://neetcode.io/solutions/subsets)                               | 7/07  | 9/19 | 9/19   | 11/29      | [[78. Subsets - Main]] - *需要複習(1st)* / **邊界條件注意 (2nd)**                                                                             |
| 72  | [39. Combination Sum](https://leetcode.com/problems/combination-sum/)                                             | Medium     | [Link](https://neetcode.io/solutions/combination-sum)                       | 7/07  | 9/20 | 9/20   | 11/30      | [[39. Combination Sum - Main]] *模板練習 (2nd)*                                                                                         |
| 73  | [46. Permutations](https://leetcode.com/problems/permutations/)                                                   | Medium     | [Link](https://neetcode.io/solutions/permutations)                          | 7/07  | 9/20 | 9/20   | 12/01      | [[46. Permutations - Main]] - 模板練習 (2nd)                                                                                            |
| 74  | [90. Subsets II](https://leetcode.com/problems/subsets-ii/)                                                       | Medium     | [Link](https://neetcode.io/solutions/subsets-ii)                            | 7/07  | 9/20 | 9/20   | 11/29      | [[90. Subsets II - Main]] - *需要複習（1st)* / **模板練習 + 邊界條件 (2nd)**                                                                     |
| 75  | [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)                                       | Medium     | [Link](https://neetcode.io/solutions/combination-sum-ii)                    | 7/07  | 9/20 | 9/20   | 11/30      | [[40. Combination Sum II - Main]] - *需要複習(1st)* / **模板練習 + 練習條件加速 (2nd)**                                                           |
| 76  | [79. Word Search](https://leetcode.com/problems/word-search/)                                                     | Medium     | [Link](https://neetcode.io/solutions/word-search)                           | 7/07  | 9/20 | 9/20   | 12/01      | [[79. Word Search - Main]] - *需要複習(1st)* / 使用 graph 的模板 (2nd)                                                                       |
| 77  | [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)                            | Medium     | [Link](https://neetcode.io/solutions/palindrome-partitioning)               | 7/08  | 9/21 | 9/21   | 12/01      | [[131. Palindrome Partitioning - Main]] - **沒特別難，但題目不容易懂，string 語法要注意(1st)** / *模板化寫法（2nd)*                                         |
| 78  | [17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) | Medium     | [Link](https://neetcode.io/solutions/letter-combinations-of-a-phone-number) | 7/08  | 9/21 | 9/21   | 12/01      | [[17. Letter Combinations of a Phone Number - Main]] - **三種寫法 DFS Iteration / BFS Iteration / DFS Recursive (1st)** / *模板化寫法 (2nd)* |
| 79  | [51. N Queens](https://leetcode.com/problems/n-queens/)                                                           | Hard       | [Link](https://neetcode.io/solutions/n-queens)                              | 7/08  | 9/21 | 9/21   | 12/02      | [[51. N Queens - Main]] - **board 對角線轉換為 index 要熟悉(1st)** / *暴力填色 or 對角線用 map 記錄 (2nd)*                                             |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 1863 | [1863. Sum of All Subsets XOR Total](https://leetcode.com/problems/sum-of-all-subset-xor-totals/) | Easy | [Link](https://neetcode.io/solutions/sum-of-all-subset-xor-totals) | | | | | |
| 77 | [77. Combinations](https://leetcode.com/problems/combinations/) | Medium | [Link](https://neetcode.io/solutions/combinations) | | | | | |
| 47 | [47. Permutations II](https://leetcode.com/problems/permutations-ii/) | Medium | [Link](https://neetcode.io/solutions/permutations-ii) | | | | | |
| 473 | [473. Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/) | Medium | [Link](https://neetcode.io/solutions/matchsticks-to-square) | | | | | |
| 698 | [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/) | Medium | [Link](https://neetcode.io/solutions/partition-to-k-equal-sum-subsets) | | | | | |
| 52 | [52. N Queens II](https://leetcode.com/problems/n-queens-ii/) | Hard | [Link](https://neetcode.io/solutions/n-queens-ii) | | | | | |
| 140 | [140. Word Break II](https://leetcode.com/problems/word-break-ii/) | Hard | [Link](https://neetcode.io/solutions/word-break-ii) | | | | | |