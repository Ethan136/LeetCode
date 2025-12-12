---
LeetCodeSeq: 16
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 6
LeetCode150ConceptOk: 6
LeetCode150TestPass: 6
LeetCode150Finish: 6
LeetCode150Review: 6
LeetCode150Rev2: 6
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 1
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
### 模板
#### 核心概念
**Interval 可能會需要取兩個 index 比對，比較適合用 while loop**

#### Interval Array Merge
**類似 merge sort two sorted link list array 的作法**
- 兩個 array 各自依照 interval start 進行 sort
- 然後每個 loop 從兩個 interval array 挑選出 start point 比較小的進
	- 檢查是否需要和 result[ last ] 進行 merge（merge 後 interval end 採用 max{ result.back()[1], add interval[1]}
	- 如果不用 merge，則 selected interval 直接加入 result

#### Interval Array Check Overlay
- 先執行 Sort
- 然後使用 while loop
	- base idx：當前的基準 interval，選用『兩個 interval 比較前面的』
	- cmp idx：和 base idx 比較大 interval
	- 比對後選一個保留，留下來的當作 base idx，隨後更新 cmp idx 到下一個位置

#### Sorted Intervals Conver Sorted Points
- 如果某個 interval[i] start 在 point[j] 前面，則 interval[i] 一定也在 point[j+N] 前面 -> *用來剔除不包含的 interval*
- 如果某個 interval[i] end 在 point[j] 後面，則 interval[i] 不一定在 point[j+N] 後面 -> *用來選擇包含 point[j] 的 interval*
- 如果某個 interval[i] 包含 point[j]，則 interval[i] 可能包含 point[j]，但也可能不包含

### Intervals

#### LeetCode 150


| #   | Problem                                                                                                               | Difficulty | Solution                                                                     | Concept | TestPass | Finish | Review | Review 2nd | Note                                                                                                                              |
| --- | --------------------------------------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------------------------- | ------- | -------- | ------ | ------ | ---------- | --------------------------------------------------------------------------------------------------------------------------------- |
| 130 | [57. Insert Interval](https://leetcode.com/problems/insert-interval/)                                                 | Medium     | [Link](https://neetcode.io/solutions/insert-interval)                        | 7/18    | 7/23     | 9/25   | 9/25   | 11/03      | [[57. Insert Interval - Main]] - **如果要直接改原始 vector 符合答案，就蠻難的(1st)** / **構思 2 interval arrays 萬用解 (2nd)**                          |
| 131 | [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)                                                 | Medium     | [Link](https://neetcode.io/solutions/merge-intervals)                        | 7/18    | 7/23     | 9/25   | 9/25   | 11/03      | [[56. Merge Intervals - Main]] - **練習通用格式 (2nd)**                                                                                 |
| 132 | [435. Non-Overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)                            | Medium     | [Link](https://neetcode.io/solutions/non-overlapping-intervals)              | 7/18    | 7/23     | 9/25   | 9/25   | 11/03      | [[435. Non-Overlapping Intervals - Main]] - *interval 整體來說不一定適合用 for loop / 練習模板 (2nd)*                                           |
| 133 | [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms/)                                                    | Easy       | [Link](https://neetcode.io/solutions/meeting-rooms)                          | 7/18    | 7/23     | 10/08  | 10/08  | 11/03      | [[252. Meeting Rooms - Main]]                                                                                                     |
| 134 | [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/)                                              | Medium     | [Link](https://neetcode.io/solutions/meeting-rooms-ii)                       | 7/18    | 7/23     | 10/08  | 10/08  | 11/03      | [[253. Meeting Rooms II - Main]] - **難題，一開始的想法是錯的，但寫錯的code剛好答對(1st) / 使用 heap 來記錄每個 room 到情況 (2nd)**                              |
| 135 | [1851. Minimum Interval to Include Each Query](https://leetcode.com/problems/minimum-interval-to-include-each-query/) | Hard       | [Link](https://neetcode.io/solutions/minimum-interval-to-include-each-query) | 7/23    | 7/23     | 10/08  | 10/08  | 11/05      | [[1851. Minimum Interval to Include Each Query - Main]] - **難題：double sort + match + resotre index (1st)** / *不容易想到要如何搭配模板，(2nd)* |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 2402 | [2402. Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/) | Hard | [Link](https://neetcode.io/solutions/meeting-rooms-iii) | | | | | |