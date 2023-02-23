# Lab 1

## 题目：
1. Write code for insertion sort. 
2. Write code for merge sort. 
3. The running time of merge sort can be improved in practice by taking advantage of the fast 
running time of insertion sort when its input is “nearly” sorted. When merge sort is called on a 
subarray with fewer than k elements, use insertion sort to sort the subarray. Argue that this sorting 
algorithm runs in O(f(n, k)) expected time. What is f(n, k) and how should k be picked, both in 
theory and in practice by experiments? 
4. Write code for improved version of sorting algorithm which combines merge sort with insertion 
sort. 
5. All document for the answers of the above questions.

## 提交要求：
第 1、2、4 题提交分别名为 insertion.cpp、merge.cpp、improved.cpp 的代码
（无需编译），第3题提交名为 t3的文档文件。
## 代码要求：
第 1、2、4 题要求实现完整的代码，即给程序标准输入，要求程序进行排序并输出排序结果。
(1) 第 1、2 题输入格式：第一行一个整数 n，表示数据个数；第二行 n 个空格分隔的
整数，表示初始数据。
(2) 第 4 题输入格式：第一行两个空格隔开的整数 n 和 k，分别表示数据个数以及进行
插入排序的规模；第二行 n 个空格分隔的整数，表示初始数据。
(3) 1、2、4 题的输出格式：一行 n 个空格分隔的整数，表示使用所要求的排序算法对
初始数据从小到大排序后的结果。
## 其他要求
第 3 题要求：在 t3 文档中，给出 f(n,k)的详细推导过程，并说明 k 应该如何选取。
并在第 4 题代码中，编写过程 selectK()，实现：对给定输入 n 和数据，从实验角度选择合适的 K 并返回。

