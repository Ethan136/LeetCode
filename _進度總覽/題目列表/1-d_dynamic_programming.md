---
LeetCodeSeq: 13
LeetCode150Finish: 12
LeetCode150Num: 12
ParentTask:
  - "[[LeetCode/_進度總覽/NeetCode 150 MainPage]]"
LeetCode150ConceptOk: 12
LeetCode150TestPass: 12
LeetCode150Review: 12
LeetCode150Rev2: 12
---
### Concept
- **針對可以選擇一次 traverse 1 格 or 多格的情況：一律以當前 index 為基準**
	- 方式1：當前 index 為需要更新的目標
		- Top Down：用先前 DP[i-n] 更新當前 DP[i]
		- Bottom Up：用後續 DP[i+n] 更新當前 DP[i]
	- 方法2：當前 index 拿來更新後續 index
		- Top Down：用當前 DP[i] 更新後續 DP[i+n]
		- Bottom Up：用當前 DP[i] 更新往前 DP[i-n]
- 起始點多個選擇 -> 可能要每種起始點獨立設定一次，再開始 DP 沿著路徑檢查
	- [[746. Min Cost Climbing Stairs - Main]]
	- [[198. House Robber - Main]]
- 相鄰不可連續採用 -> 可以採用『前一個』或『前前一個』
	- *這時候『行為』和『狀態』，是不一樣的 -> 參考 [[309. Best Time to Buy and Sell Stock with Cooldown - Main]]*
	- [[198. House Robber - Main]]
	- [[213. House Robber II - Main]]
- 路徑可以多種方式 traverse - 可以一次一格或多格
	- 基本類型
		- [[746. Min Cost Climbing Stairs - Main]]
		- [[91. Decode Ways - Main]]
	- 變形類型（題目需求不同，但概念類似）
		- [[322. Coin Change - Main]]
		- [[139. Word Break - Main]]
- 小數字組成大數字
	- [[322. Coin Change - Main]]
	- [[518. Coin Change II - Main]]
- 簡化後變成 Greedy
	- [[152. Maximum Product Subarray - Main]]
- 從 array num 湊某個 target num -> **Transition State 本身是一個 sub-set 的情況（類似 BFS 的題目）**
	- [[416. Partition Equal Subset Sum - Main]]


### 1-D Dynamic Programming

| #   | Problem                                                                                              | Difficulty | Solution                                                             | PassTest | Finish | Review | Review 2nd | Note                                                                                                                                    |
| --- | ---------------------------------------------------------------------------------------------------- | ---------- | -------------------------------------------------------------------- | -------- | ------ | ------ | ---------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| 99  | [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)                                | Easy       | [Link](https://neetcode.io/solutions/climbing-stairs)                | 7/09     | 10/11  | 10/11  | 11/11      | [[70. Climbing Stairs - Main]]                                                                                                          |
| 100 | [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)             | Easy       | [Link](https://neetcode.io/solutions/min-cost-climbing-stairs)       | 7/09     | 10/11  | 10/11  | 11/11      | [[746. Min Cost Climbing Stairs - Main]]                                                                                                |
| 101 | [198. House Robber](https://leetcode.com/problems/house-robber/)                                     | Medium     | [Link](https://neetcode.io/solutions/house-robber)                   | 7/09     | 10/11  | 10/11  | 11/11      | [[198. House Robber - Main]] - *之後還要再來練習，要想一下才寫的出來 (1st)* / **第二次寫還是搞錯作法 ，能練習模板(2nd)**                                                  |
| 102 | [213. House Robber II](https://leetcode.com/problems/house-robber-ii/)                               | Medium     | [Link](https://neetcode.io/solutions/house-robber-ii)                | 7/09     | 10/11  | 10/11  | 11/11      | [[213. House Robber II - Main]] - **能練習模板 + ring back (2nd)**                                                                           |
| 103 | [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)     | Medium     | [Link](https://neetcode.io/solutions/longest-palindromic-substring)  | 7/09     | 10/12  | 10/12  | 11/13      | [[5. Longest Palindromic Substring - Main]] - **要再回來練，two pointer / DP 難題 (1st)** / **不容易想到 1D DP -> 直覺想到 2D DP，實際上是 two pointer(2nd)** |
| 104 | [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)                 | Medium     | [Link](https://neetcode.io/solutions/palindromic-substrings)         | 7/09     | 10/13  | 10/13  | 11/13      | [[647. Palindromic Substrings - Main]] - *這題也是 two pointer 回文 (2nd)*                                                                    |
| 105 | [91. Decode Ways](https://leetcode.com/problems/decode-ways/)                                        | Medium     | [Link](https://neetcode.io/solutions/decode-ways)                    | 7/10     | 10/13  | 10/13  | 11/14      | [[91. Decode Ways - Main]] - **套用模板不好寫，要再練習(2nd)**                                                                                      |
| 106 | [322. Coin Change](https://leetcode.com/problems/coin-change/)                                       | Medium     | [Link](https://neetcode.io/solutions/coin-change)                    | 7/10     | 10/13  | 10/13  | 11/14      | [[322. Coin Change - Main]]                                                                                                             |
| 107 | [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)             | Medium     | [Link](https://neetcode.io/solutions/maximum-product-subarray)       | 7/11     | 10/13  | 10/13  | 11/14      | [[152. Maximum Product Subarray - Main]] - **套用模板的話不好寫，簡化後變成 Greedy (2nd)**                                                             |
| 108 | [139. Word Break](https://leetcode.com/problems/word-break/)                                         | Medium     | [Link](https://neetcode.io/solutions/word-break)                     | 7/14     | 10/14  | 10/14  | 11/16      | [[139. Word Break - Main]] - *複習的時候一度想不到解法，之後要再練 (1st)* / **跳格子變化題，一開始想不到解法 (2nd)**                                                     |
| 109 | [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | Medium     | [Link](https://neetcode.io/solutions/longest-increasing-subsequence) | 7/14     | 10/14  | 10/14  | 11/16      | [[300. Longest Increasing Subsequence - Main]] - *複習的時候一度想不到解法，之後要再練(1st)*                                                              |
| 110 | [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)         | Medium     | [Link](https://neetcode.io/solutions/partition-equal-subset-sum)     | 7/14     | 10/14  | 10/14  | 11/16      | [[416. Partition Equal Subset Sum - Main]] - **很難，一直寫錯(1st)** / **一開始完全想不到(2nd)**                                                       |
