---
LeetCodeSeq: 15
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150Num: 8
LeetCode150ConceptOk: 8
LeetCode150TestPass: 8
LeetCode150Finish: 8
LeetCode150Review: 8
LeetCode150Rev2: 8
ParentTask2:
  - "[[NeetCode 250 MainPage]]"
LeetCode250Num: 6
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---
#### Concept
- **Greedy 的型態，通常可能類似 Backtracking 或是 DP，但只要求「能不能做到」或「最大 / 最小值」或『唯一valid solution』**
	- **-> 即「大部分中間資訊可以省略的型態」**
- 由於可以省略中間資訊，所以『不一定要像 DP 那樣把中間資訊記錄起來』
- 要思考 **取得哪個資訊後，就不可以不檢查其他分支資訊**

#### 模板
- 走到終點的題目
	- 可以試著從起始點開始走，看最遠能不能走到目標（或是最快走到目標）
	- 有點邊走邊看的概念
	- [[55. Jump Game - Main]]
	- [[45. Jump Game II - Main]]
- 針對『一定有解』的情況
	- 有可能是沒辦法一次 Try 到底，會需要換東西來 try，但在換東西 Try 的途中，可以不用一個一個試
	- 很有可能換東西 try 的時候，前面 try 過的可以不用再 try
	- [[134. Gas Station - Main]]
- 目標如果是 yes / no 的情況
	- 可以先看 overall condition 有沒有符合
	- [[134. Gas Station - Main]]
- match 的題目，有兩種方式
	- 把不符合的都踢掉，再把剩下的拿來做 match -> 速度比較慢
	- 直接檢查每一個是否為 valid match，並且一旦match 到 target，直接 early return -> 速度比較快
	- [[1899. Merge Triplets to Form Target Triplet - Main]]
- 針對有分支的情況，如果只判斷『可行 / 不可行』 -> **最難的類型**
	- Greedy 是看能不能把 branch condition 的 upper / lower case 呈現出來，並且確保 target condition 落在這個範圍內
	- **要確保 branch condition upper / lower bound 可以用來判斷『題目需求是否能被達成』**
	- [[678. Valid Parenthesis String - Main]]

### Greedy

#### LeetCode 150


| #   | Problem                                                                                                             | Difficulty | Solution                                                                    | Concept | PassTest | Finish | Review | Review2 | Note                                                                                              |
| --- | ------------------------------------------------------------------------------------------------------------------- | ---------- | --------------------------------------------------------------------------- | ------- | -------- | ------ | ------ | ------- | ------------------------------------------------------------------------------------------------- |
| 122 | [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)                                             | Medium     | [Link](https://neetcode.io/solutions/maximum-subarray)                      | 7/15    | 7/20     | 9/21   | 9/21   | 11/06   | [[53. Maximum Subarray - Main]]                                                                   |
| 123 | [55. Jump Game](https://leetcode.com/problems/jump-game/)                                                           | Medium     | [Link](https://neetcode.io/solutions/jump-game)                             | 7/16    | 7/20     | 9/21   | 9/21   | 11/06   | [[55. Jump Game - Main]] - **複習想很久沒想到最佳解(2nd)**                                                   |
| 124 | [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)                                                     | Medium     | [Link](https://neetcode.io/solutions/jump-game-ii)                          | 7/16    | 7/20     | 9/21   | 9/21   | 11/07   | [[45. Jump Game II - Main]] - **難題，邊界條件和 update 機制要先想好（1st)** / **執行流程要先想好(2nd)**                 |
| 125 | [134. Gas Station](https://leetcode.com/problems/gas-station/)                                                      | Medium     | [Link](https://neetcode.io/solutions/gas-station)                           | 7/16    | 7/20     | 9/21   | 9/21   | 11/07   | [[134. Gas Station - Main]] - **難題，寫蠻久（1st）** / **想很久，還沒完全連結到模板(2nd)**                            |
| 126 | [846. Hand of Straights](https://leetcode.com/problems/hand-of-straights/)                                          | Medium     | [Link](https://neetcode.io/solutions/hand-of-straights)                     | 7/17    | 7/20     | 9/21   | 9/21   | 11/07   | [[846. Hand of Straights - Main]] - *bulk sort*                                                   |
| 127 | [1899. Merge Triplets to Form Target Triplet](https://leetcode.com/problems/merge-triplets-to-form-target-triplet/) | Medium     | [Link](https://neetcode.io/solutions/merge-triplets-to-form-target-triplet) | 7/17    | 7/21     | 9/24   | 9/24   | 11/07   | [[1899. Merge Triplets to Form Target Triplet - Main]] - *好幾種做法可以看* / **練習match和exclude模板 (2nd)** |
| 128 | [763. Partition Labels](https://leetcode.com/problems/partition-labels/)                                            | Medium     | [Link](https://neetcode.io/solutions/partition-labels)                      | 7/17    | 7/21     | 9/24   | 9/24   | 11/07   | [[763. Partition Labels - Main]] - 資料結構設計，類有點類似 stack 的題型                                         |
| 129 | [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)                            | Medium     | [Link](https://neetcode.io/solutions/valid-parenthesis-string)              | 7/17    | 7/22     | 9/25   | 9/25   | 11/07   | [[678. Valid Parenthesis String - Main]] - **很難** / **複習第二次還是寫很久 (2nd)**                          |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 860 | [860. Lemonade Change](https://leetcode.com/problems/lemonade-change/) | Easy | [Link](https://neetcode.io/solutions/lemonade-change) | | | | | [[860. Lemonade Change - Main]] |
| 918 | [918. Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) | Medium | [Link](https://neetcode.io/solutions/maximum-sum-circular-subarray) | | | | | [[918. Maximum Sum Circular Subarray - Main]] |
| 978 | [978. Longest Turbulent Subarray](https://leetcode.com/problems/longest-turbulent-subarray/) | Medium | [Link](https://neetcode.io/solutions/longest-turbulent-subarray) | | | | | [[978. Longest Turbulent Subarray - Main]] |
| 1871 | [1871. Jump Game VII](https://leetcode.com/problems/jump-game-vii/) | Medium | [Link](https://neetcode.io/solutions/jump-game-vii) | | | | | [[1871. Jump Game VII - Main]] |
| 649 | [649. Dota2 Senate](https://leetcode.com/problems/dota2-senate/) | Medium | [Link](https://neetcode.io/solutions/dota2-senate) | | | | | [[649. Dota2 Senate - Main]] |
| 135 | [135. Candy](https://leetcode.com/problems/candy/) | Hard | [Link](https://neetcode.io/solutions/candy) | | | | | [[135. Candy - Main]] |
