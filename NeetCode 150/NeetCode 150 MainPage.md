---
Level: Main
Status: Not Started
StartDate: 2024-03-21
DueDate: 2024-06-21
FinishDate: 
Urgency: "20"
tags:
  - leetcode
  - algorithm
ParentTask:
  - "[[刷題機制和策略規劃]]"
---

# NeetCode RoadMap
[Roadmap](https://neetcode.io/roadmap)

# NeetCode 150 Progress Tracker

```dataviewjs
// Get all files in the NeetCode 150 folder except this one
const pages = dv.pages('"'+this.current().file.folder+'"')
    .filter(p => p.file.name != this.current().file.name )
    .sort(p => p.NeetCodeSeq);

// Calculate total statistics
let totalProblems = 0;
let totalCompleted = 0;
for (let page of pages) {
    totalProblems += page.LeetCodeNum || 0;
    totalCompleted += page.LeetCodeFinish || 0;
}
const overallProgress = Math.round((totalCompleted / totalProblems) * 100);

// Create a table with the information
const table = dv.markdownTable(
    ["Category", "Problems ("+totalProblems.toString()+")", "Completed ("+totalCompleted.toString()+")", "Progress ("+overallProgress.toString()+"%)", "NeetCodeSeq"],
    [
        ...pages.map(p => [
            p.file.link,
            p.LeetCodeNum || 0,
            p.LeetCodeFinish || 0,
            p.LeetCodeNum ? Math.round((p.LeetCodeFinish || 0) / p.LeetCodeNum * 100) + '%' : '0%',
            p.NeetCodeSeq || ''
        ])
    ]
);

dv.header(3, "Progress Overview");
dv.paragraph(table);
``` 
