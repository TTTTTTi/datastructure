# 提交要求：
## (1) 
提交的文档中要包含 lab3 中除代码实现外的题目答案。
## (2) 
提交的代码应使用数组实现一个 d-ary max-heap：对任意的 n 和 d 以及初始数据（可
以读入或随机生成），能构造一个 d-ary max-heap，并实现以下函数：
### 1 EXTRACT-MAX()：
返回 heap 中最大值，并将该元素从 heap 中删除。
### 2 INSERT(x)：
在 heap 中加入一个值为 x 的元素。
### 3 INCREASE-KEY(A,i,k)：
先将 A[i]赋值成 max(A[i], k)，再更新 A 这个 d-ary
max-heap。