提交要求：
(1) 提交的代码应实现一个二叉查找树，每个元素具有 key 值和 value 值，实现以下功
能函数（在满足功能的同时保证二叉查找树的性质）：
1 search_recursion(x,k)，search_iterative(x,k)：查找 x 为根的子树中 key 值为 k 的
元素的 value，没有则返回-1。
2 minimum(x)，maximum(x)：查找 x 为根的子树中 key 值最小/大的元素的 value。
3 successor(x)，predecessor(x)：查找比 x 的 key 值大/小的最小/大 key 值的元素
的 value。
4 insert(T,z)：在树中插入一个新节点 z。
5 delete(T,z)：在树中删除节点 z（以 z 的 key 值作为判断）。
6 traversal()：分别实现树的先序、中序、后序遍历，得到 value 值序列。