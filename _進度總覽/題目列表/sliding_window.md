---
LeetCodeSeq: 3
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
LeetCode250Num: 3
LeetCode250ConceptOk:
LeetCode250TestPass:
LeetCode250Finish:
LeetCode250Review:
LeetCode250Rev2:
---

### Sliding Window
**標準化作法：flexible window**
- 判斷 match -> **使用 statistic**
- **sliding window -> 使用 start index + length**
- **固定流程：先擴充 window right -> 檢查及執行收縮 window left (最多可以收縮到 window len = 0) -> 針對題目所需的情況擷取資訊 (max / check / ..)**
	- 向右收縮
		- **收縮依據1：如果 add new char 後檢查 add point 造成有多餘的內容 -> update start 直到沒有多餘內容（也可能造成 window len = 0）**
		- **收縮依據2：如果 add new char 後檢查 start point 有冗余內容 -> update start 直到沒有多餘內容（也可能造成 window len = 0）**
	- 向左收縮 -> 最好不要
		- **收縮依據3：如果 add new char 後檢查 add point 造成多餘的內容 -> update length 直到沒有多餘內容（也可能造成 window len = 0）**
			- **這個操作要注意，如果後續某個元素 add 到 range 裡面後，造成 length 擴增好幾個，那必須跑一個 for loop 大幅度擴增 statistic**
- 比較好的做法是
	- 右邊擴張，左邊收縮
	- 需要MinValidWindow的時候，不要收縮右邊，而是每個Loop檢查當下的Valid Window有沒有比之前紀錄的Valid Window 更小
- 題目
	- [[3. Longest Substring Without Repeating Characters - Main]]
	- [[424. Longest Repeating Character Replacement - Main]]
	- [[567. Permutation in String]]
	- [[76. Minimum Window Substring - Main]]


**標準化作法：fixed window**
- 判斷 matc -> 使用 statistic
- window length 固定，但是每次 move 的時候更新 statistic
- 一旦發生all match 的情況，把結果記錄下來
- 題目
	- [[567. Permutation in String]]
	- [[239. Sliding Window Maximum - Main]]

#### LeetCode 150


| #   | Problem                                                                                                                            | Difficulty | Solution                                                                             | Status      | Review | Review2 | Note                                                                                        |
| --- | ---------------------------------------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------------------------------------------ | ----------- | ------ | ------- | ------------------------------------------------------------------------------------------- |
| 15  | [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)                             | Easy       | [Link](https://neetcode.io/solutions/best-time-to-buy-and-sell-stock)                | 6/14 Finish | 9/14   | 10/29   | [[121. Best Time to Buy and Sell Stock - Main]]                                             |
| 16  | [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | Medium     | [Link](https://neetcode.io/solutions/longest-substring-without-repeating-characters) | 6/14 Finish | 9/14   | 10/29   | [[3. Longest Substring Without Repeating Characters - Main]] - **最佳解沒想到，額外想的優化卡了一陣(2nd)**   |
| 17  | [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)             | Medium     | [Link](https://neetcode.io/solutions/longest-repeating-character-replacement)        | 6/14 Finish | 9/15   | 10/30   | [[424. Longest Repeating Character Replacement - Main]] - **容易寫錯，要複習(1st) / 完全想不到要怎做(2nd)** |
| 18  | [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)                                                 | Medium     | [Link](https://neetcode.io/solutions/permutation-in-string)                          | 6/14 Finish | 9/15   | 10/29   | [[567. Permutation in String]] - **難題，要複習(1st) / 想了一陣，邊界條件容易錯，每次解法都不太一樣(2nd)**              |
| 19  | [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)                                            | Hard       | [Link](https://neetcode.io/solutions/minimum-window-substring)                       | 6/14 Finish | 9/15   | 10/30   | [[76. Minimum Window Substring - Main]] - **邊界條件要注意(1st) / window 收縮條件要注意 (2nd)**           |
| 20  | [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)                                               | Hard       | [Link](https://neetcode.io/solutions/sliding-window-maximum)                         | 6/14 Finish | 9/15   | 10/30   | [[239. Sliding Window Maximum - Main]] - **邊界條件要注意(1st) / 特性和其他的 sliding window 不一樣 (2nd)** |

#### LeetCode 151-250

| # | Problem | Difficulty | Solution | PassTest | Finish | Review | Review 2nd | Note |
|---|---|---|---|---|---|---|---|---|
| 219 | [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/) | Easy | [Link](https://neetcode.io/solutions/contains-duplicate-ii) | | | | | |
| 209 | [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | Medium | [Link](https://neetcode.io/solutions/minimum-size-subarray-sum) | | | | | |
| 658 | [658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/) | Medium | [Link](https://neetcode.io/solutions/find-k-closest-elements) | | | | | |
