ds1.md

数据结构
================================================================================

第1章 绪论
================================================================================

A~-1g14

1.2 基本概念和术语
--------------------------------------------------------------------------------

- 数据、数据元素、数据对象、数据结构
- 4类基本结构：
  1. 集合
  2. 线性空间
  3. 树状结构
  4. 图状结构
- 逻辑结构、物理结构/存储结构
- 抽象数据类型（ADT）：
  - 原子类型（atomic）
  - 固定聚合类型（fixed-aggregate）
  - 可变聚合类型（variable-aggregate）
  - 多形数据结构（polymorphic）

1.3 抽象数据类型的表现与实现
--------------------------------------------------------------------------------

```cxx
typedef int Status:
TRUE 1
FALSE 0
OK 1
ERROR 0
INFEASIBLE -1
OVERFLOW -2
```

1.4 算法和算法分析
--------------------------------------------------------------------------------

### 1.4.1 算法

5个特性：

1. 有穷性
2. 确定性
3. 可行性
4. 输入（0个或多个）
5. 输出（1个或多个）

### 1.4.2 算法设计的要求

目标：

1. 正确性（correctness）
2. 可读性（readability）
3. 健壮性（robustness）
4. 效率与低存储量需求

### 1.4.3 算法效率的度量

程序运行时间取决于：

1. 算法策略
2. 问题规模
3. 编写语言
4. 编译质量
5. 机器执行指令速度

为比较算法效率，从算法中选取一种对于所研究的问题（或算法类型是基本操作的原操作，以该操作执行次数作为算法的时间量度。  
算法的时间度量记作 $T(n) = O(f(n))$，表示随问题规模n的增大，执行时间的增长率与f(n)增长率相同，称作渐进时间复杂度（asymptotic time complexity）

### 1.4.4 算法的存储空间需求

空间复杂度（space complexity）$S(n) = O(f(n))$

第2章 线性表
================================================================================

A~-1g15

2.1 线性表的类型定义
--------------------------------------------------------------------------------

线性表（linear list）定义：

```cxx
ADT List { 数据对象：D = { a_i | a_i 属于 ElemSet, i = 1,2,...n, n >= 0 }
           数据关系：Rl = { <a_i-1, a_i> | a_i-1, a_i 属于 D, i = 2,...n }
           基本操作：InitList(&L)
                    DestroyList(&L)
                    ClearList(&L)
                    ListEmpty(L)
                    ListLength(L)
                    GetElem(L, i, &e)
                    LocateElem(L, e, compare())
                    PriorElem(L, cur_e, &pre_e)
                    NextElem(L, cur_e, &next_e)
                    ListInsert(&L, i, e)
                    ListDelete(&L, i, &e)
                    ListTraverse(L, visi())
          }
```

2.2 线性表的顺序表示和实现
--------------------------------------------------------------------------------

- 线性表的顺序表示指的是用一组地址连续的存储单元依次存储
- 容易实现随机存取
- 插入、删除较费时
- 若以线性表进行集合的各种运算，应先进行排序

2.3 线性表的链式表示和实现
--------------------------------------------------------------------------------

### 2.3.1 线性链表

- 用任意存储单元存储元素
- 结点、数据域、指针域
- 静态链表：用一维数组描述链表，在无指针的高级语言中

### 2.3.2 循环链表（circular linked list）

- 最后节点的指针域指向头结点
- 也可设尾节点

### 2.3.3 双向链表（double linked list）

在链表中，元素在线性表中的“位序”（序号）的概念已淡化，而用“位置”

2.4 一元多项式的表示及相加
--------------------------------------------------------------------------------

可用有序链表表示一元多项式，元素为系数和指数。  
与一般线性链表不同在于LocateElem职能不同；  
及增加按有序关系进行插入的操作OrderInsert。

第3章 栈和队列
================================================================================

A~-1g17

3.1 栈
--------------------------------------------------------------------------------

### 3.1.1 抽象数据类型栈的定义

- 栈（stack）是限定仅在表尾进行插入或删除操作的线性表
- 栈顶（top）
- 栈底（bottom）
- 后进先出（LIFO）

### 3.1.2 栈的表示和实现

顺序栈，即栈的顺序存储结构是利用一组地址连续的存储单元依次存放自栈底至栈顶的数据元素；  
另一种为链栈

3.2 栈的应用举例
--------------------------------------------------------------------------------

- 3.2.1 数制转换
  - 十进制数N对进制d取余入栈，再用商取余，循环，最后出栈输出
- 3.2.2 括号匹配的检验
  - 对表达式中的不同种类括号配对检验，左括入栈，遇到右括出栈
- 3.2.3 行编辑程序
  - 接受带有退格和退行符的一行输入，普通字符入栈，退符出栈或清空
- 3.2.4 迷宫求解
  - 寻找可行的迷宫路径。当前位置可通行则入栈并检查相邻位置；若不可通行则出栈寻找下一个具有为访问相邻位置的路径点，直至出口
- 3.2.5 表达式求值
  - 使用两个栈分别储存操作数和运算符，对运算符进行优先级比较，输入操作数入栈，遇到运算符若比栈顶优先，入栈；否则出栈并运算

3.3 栈与递归的实现
--------------------------------------------------------------------------------

在高级语言编制的程序中，调用函数和被调用函数之间的链接及信息交换通过栈进行。

- 通常，当一个函数调用另一个函数时，在运行被调函数之前，系统需要先完成3件事：
  1. 将所有的实在参数、返回地址等信息传递给被调函数保存
  2. 为被调函数的局部变量分配储存区
  3. 将控制转移到被调函数入口
- 而从被调函数返回调用函数前，也需完成3件工作：
  1. 保存被调函数的计算结果
  2. 释放被调函数的数据区
  3. 依照被调函数保存的返回地址将控制转移到调用函数

当多个函数构成嵌套调用时，按“后调用先返回”原则，函数间的信息传递和控制转移，必须通过“栈”实现，即系统将整个程序运行所需要数据空间安排在一个栈中，每当调用一个函数时，就为它在栈顶分配一个存储区，每当从一个函数退出时，就释放它的存储区。

示例：Hinoi塔问题

3.4 队列
--------------------------------------------------------------------------------

- 3.4.1 ADT队列定义
  - queue: FIFO
  - 队尾（rear）
  - 队头（front）
  - 双端队列（deque）可在两端进行插入和删除
- 3.4.2 链队列 —— 队列的链式表示和实现
- 3.4.3 循环队列 —— 队列的顺序表示和实现

3.5 离散事件模拟
--------------------------------------------------------------------------------

计算银行每天平均客户排队时间，使用事件驱动模拟。

使用1个事件队列（有序链表，以时间排序）和n个排队队列，  
当客户到达时，生成并插入下一个客户到达事件到事件队列，插入当前客户到排队队列；  
若排到队头，插入该客户离开事件到事件队列；
当某排队队列队头客户离开时，插入下一个队头客户离开事件到事件队列。

--------------------------------------------------------------------------------

EOF
