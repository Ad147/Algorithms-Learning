DSAA-Ch02-Analysis.md


Notes of Data Structures and Algorithm Analysis in C++
================================================================================

Ad  
<ar><r>

Init: 19Mar04


Chapter 2 Algorithm Analysis
--------------------------------------------------------------------------------

An **algorithm** is a clearly specified set of simple instructions to be followed to solve aproblem.  
Once an algorithm is given for a problem and decided (somehow) to be correct,an important step is to determine how much in the way of resources, such as time or space,the algorithm will require.

In this chapter, we shall discuss...

- How to estimate the time required for a program.
- How to reduce the running time of a program from days or years to fractions of asecond.
- The results of careless use of recursion.
- Very efficient algorithms to raise a number to a power and to compute the greatestcommon divisor of two numbers.

--------------------------------------------------------------------------------

- [Chapter 2 Algorithm Analysis](#chapter-2-algorithm-analysis)
  - [2.1 Mathematical Background](#21-mathematical-background)
  - [2.2 Model](#22-model)
  - [2.3 What to Analyze](#23-what-to-analyze)
  - [2.4 Running-Time Calculations](#24-running-time-calculations)

--------------------------------------------------------------------------------


### 2.1 Mathematical Background


###### Definition 2.1

$T(N) = O(f(N))$ if there are positive constants c and n0 such that $T(N) ≤ cf(N)$ when $N ≥ n_0$.


###### Definition 2.2

$T(N) = Ω(g(N))$ if there are positive constants c and n0 such that $T(N) ≥ cg(N)$ when $N ≥ n0$.


###### Definition 2.3

$T(N) = Θ(h(N))$ if and only if $T(N) = O(h(N))$ and $T(N) = Ω(h(N))$.


###### Definition 2.4

$T(N) = o(p(N))$ if, for all positive constants c, there exists an n0 such that $T(N) < cp(N)$ when $N > n0$.  
Less formally, $T(N) = o(p(N))$ if $T(N) = O(p(N))$ and $T(N) ≠ Θ(p(N))$.

The idea of these definitions is to establish a relative order among functions.  
Given two functions, there are usually points where one function is smaller than the other.  
So it doesnot make sense to claim, for instance, f(N) < g(N).  
Thus, we compare theirrelative ratesof growth.  
When we apply this to the analysis of algorithms, we shall see why this is the important measure.

Although 1,000Nis larger than N^2 for small values of N, N^2 grows at a faster rate, and thus N^2 will eventually be the larger function.  
The turning point isN=1,000 in this case.  
The first definition says that eventually there is some point n0 past which c·f(N) is alwaysat least as large asT(N), so that if constant factors are ignored,f(N) is at least as big asT(N).  
In our case, we haveT(N)=1,000N,f(N)=N^2,n0=1,000, andc=1.  
We could also use n0=10 and c=100.  
Thus, we can say that 1,000N = O(N^2) (orderN-squared).  
This notation is known as **Big-Oh notation**.  
Frequently, instead of saying “order...,” one says “Big-Oh....”

If we use the traditional inequality operators to compare growth rates, then
- The first definition says that the growth rate ofT(N) is less than or equal to (≤) that of f(N).
- The second definition,T(N)=Ω(g(N)) (pronounced “omega”), says that the growth rate ofT(N) is greater than or equal to (≥)that of g(N).
- The third definition,T(N) = Θ(h(N)) (pronounced “theta”), says that the growth rate of T(N) equals(=) the growth rate ofh(N).
- The last definition,T(N)=o(p(N)) (pronounced “little-oh”), says that the growth rate ofT(N) is less than (<) the growth rate ofp(N).  
  This is different from Big-Oh, because Big-Ohallows the possibility that the growth rates are the same.

To prove that some functionT(N)=O(f(N)), we usually do not apply these defini-tions formally but instead use a repertoire of known results.  
In general, this means that a proof (or determination that the assumption is incorrect) is a very simple calculation and should not involve calculus, except in extraordinary circumstances (not likely to occur inan algorithm analysis).

When we say thatT(N)=O(f(N)), we are guaranteeing that the functionT(N) grows at a rate no faster thanf(N);  
thus f(N) is an **upper bound** on T(N).  
Since this implies thatf(N)=Ω(T(N)), we say thatT(N)is a **lower bound** on f(N).

As an example, $N^3$ grows faster thanN^2, so we can say that $N^2=O(N^3)$ or N^3=(N^2).  
$f(N)=N^2$ and g(N)=2N^2grow at the same rate, so both $f(N)=O(g(N))$ andf(N)=(g(N)) are true.  
When two functions grow at the same rate, then the decision ofwhether or not to signify this with Θ() can depend on the particular context.  
Intuitively,if $g(N)=2N^2$, then $g(N)=O(N4)$, $g(N)=O(N^3)$, and $g(N)=O(N^2)$ are all technically correct, but the last option is the best answer.  
Writingg(N)=(N^2) says not only that $g(N)=O(N^2)$ but also that the result is as good (tight) as possible.

Here are the important things to know:


###### Rule 1

If $T_1(N) = O(f(N))$ and $T_2(N) = O(g(N))$, then  
- (a) $T_1(N) + T_2(N) = O(f(N) + g(N))$ (intuitively and less formally it is $O(max(f(N), g(N)))$)
- (b) $T1(N) ∗ T2(N) = O(f(N) ∗ g(N))$.


###### Rule 2

If T(N) is a polynomial of degreek, then $T(N) = Θ(N^k)$.


###### Rule 3

$log^kN = O(N)$ for any constant k.  
This tells us that logarithms grow very slowly.

This information is sufficient to arrange most of the common functions by growth rate (see Fig. 2.1).


###### Figure 2.1Typical growth rates

| Function | Name        |
| -------- | ----------- |
| c        | Constant    |
| logN     | Logarithmic |
| log2N    | Log-squared |
| N        | Linear      |
| NlogN    |
| N^2      | Quadratic   |
| N^3      | Cubic       |
| 2^N      | Exponential |

Several points are in order.  

First, it is very bad style to include constants or low-orderterms inside a Big-Oh.  
Do not sayT(N)=O(2N^2)orT(N)=O(N^2+N).  
In both cases, thecorrect form isT(N)=O(N^2).  
This means that in any analysis that will require a Big-Ohanswer, all sorts of shortcuts are possible.  
Lower-order terms can generally be ignored, andconstants can be thrown away.  
Considerably less precision is required in these cases.

Second, we can always determine the relative growth rates of two functionsf(N)and g(N) by computing $lim_{N→∞}f(N)/g(N)$, using L’Hôpital’s rule if necessary.  
The limit canhave four possible values:

- The limit is 0: This means that $f(N) = o(g(N))$.
- The limit is $c ≠ 0$: This means that $f(N) = Θ(g(N))$.
- The limit is $∞$: This means that $g(N) = o(f(N))$.
- The limit does not exist: There is no relation (this will not happen in our context).

Using this method almost always amounts to overkill.  
Usually the relation betweenf(N)andg(N) can be derived by simple algebra.  
For instance, if f(N)=NlogN and g(N)=N^1.5, then to decide which off(N)andg(N) grows faster, one really needs to determine which of logN and N0.5 grows faster.  
This is like determining which of log2N or N growsfaster.  
This is a simple problem, because it is already known thatNgrows faster than anypower of a log.  
Thus,g(N) grows faster thanf(N).

One stylistic note: It is bad to sayf(N)≤O(g(N)), because the inequality is implied bythe definition.  
It is wrong to writef(N)≥O(g(N)), because it does not make sense.

As an example of the typical kinds of analyses that are performed, consider the prob-lem of downloading a file over the Internet.  
Suppose there is an initial 3-sec delay (toset up a connection), after which the download proceeds at 1.5M(bytes)/sec.  
Then it fol-lows that if the file isNmegabytes, the time to download is described by the formulaT(N)=N/1.5+3.  
This is alinear function. Notice that the time to download a 1,500Mfile (1,003 sec) is approximately (but not exactly) twice the time to download a 750M file(503 sec).  
This is typical of a linear function.  
Notice, also, that if the speed of the con-nection doubles, both times decrease, but the 1,500M file still takes approximately twicethe time to download as a 750M file.  
This is the typical characteristic of linear-time algo-rithms, and it is the reason we writeT(N)=O(N), ignoring constant factors.  
(Althoughusing big-theta would be more precise, Big-Oh answers are typically given.)

Observe, too, that this behavior is not true of all algorithms.  
For the first selectionalgorithm described in Section 1.1, the running time is controlled by the time it takes toperform a sort.  
For a simple sorting algorithm, such as the suggested bubble sort, when theamount of input doubles, the running time increases by a factor of four for large amountsof input.  
This is because those algorithms are not linear.  
Instead, as we will see when wediscuss sorting, trivial sorting algorithms areO(N^2), or quadratic.

--------------------------------------------------------------------------------


### 2.2 Model

In order to analyze algorithms in a formal framework, we need a model of computation.  
Our model is basically a normal computer in which instructions are executed sequentially.  
Our model has the standard repertoire of simple instructions, such as addition, multiplica-tion, comparison, and assignment, but, unlike the case with real computers, it takes exactlyone time unit to do anything (simple).  
To be reasonable, we will assume that, like a moderncomputer, our model has fixed-size (say, 32-bit) integers and no fancy operations, such asmatrix inversion or sorting, which clearly cannot be done in one time unit.  
We also assumeinfinite memory.

This model clearly has some weaknesses. Obviously, in real life, not all operations takeexactly the same time. In particular, in our model, one disk reads counts the same as anaddition, even though the addition is typically several orders of magnitude faster. Also, byassuming infinite memory, we ignore the fact that the cost of a memory access can increasewhen slower memory is used due to larger memory requirements.

--------------------------------------------------------------------------------


### 2.3 What to Analyze

The most important resource to analyze is generally the running time.  
Several factors affect the running time of a program.  
Some, such as the compiler and computer used, are obviously beyond the scope of any theoretical model, so, although they are important, we cannot deal with them here.  
The other main factors are the algorithm used and the input to the algorithm.

Typically, the size of the input is the main consideration.  
We define two functions, $T_{avg}(N)$ and $T_{worst}(N)$, as the average and worst-case running time, respectively, used by an algorithm on input of size N. Clearly, $T_{avg}(N) < T_{worst}(N)$.  
If there is more than one input, these functions may have more than one argument.

Occasionally, the best-case performance of an algorithm is analyzed.  
However, this isoften of little interest, because it does not represent typical behavior.  
Average-case perfor-mance often reflects typical behavior, while worst-case performance represents a guaranteefor performance on any possible input.

Notice also that, although in this chapter we ana-lyze C++code, these bounds are really bounds for the algorithms rather than programs.  
Programs are an implementation of the algorithm in a particular programming language,and almost always the details of the programming language do not affect a Big-Oh answer.  
If a program is running much more slowly than the algorithm analysis suggests, there maybe an implementation inefficiency.  
This can occur in C++when arrays are inadvertentlycopied in their entirety, instead of passed with references. 

Generally, the quantity required is the worst-case time, unless otherwise specified.  
Onereason for this is that it provides a bound for all input, including particularly bad input,which an average-case analysis does not provide.  
The other reason is that average-casebounds  are  usually  much  more  difficult  to  compute.  
In  some  instances,  the  definitionof “average” can affect the result.  
(For instance, what is average input for the followingproblem?)

As an example, in the next section, we shall consider the following problem:


> ##### Maximum Subsequence Sum Problem
>
> Given (possibly negative) integers $A_1, A_2, ..., A_N$, find the maximum value of $\sum_{k=i}^j A_k$.  
> (For convenience, the maximum subsequence sum is 0 if all the integers are negative.)

This  problem  is  interesting  mainly  because  there  are  so  many  algorithms  to  solveit, and the performance of these algorithms varies drastically.  
We will discuss four algo-rithms to solve this problem.  
The running time on some computers (the exact computer isunimportant) for these algorithms is given in Figure 2.2.


###### Figure 2.2 Running  times  of  several  algorithms  for  maximum  subsequence  sum  (in seconds)

| Input Size  | Algorithm Time | <<<      | <<<      | <<<      |
| ----------- | -------------- | -------- | -------- | -------- |
| ^^^         | 1              | 2        | 3        | 4        |
| ^^^         | O(N^3)         | O(N^2)   | O(NlogN) | O(N)     |
| N=100       | 0.000159       | 0.000006 | 0.000005 | 0.000002 |
| N=1,000     | 0.095857       | 0.000371 | 0.000060 | 0.000022 |
| N=10,000    | 86.67          | 0.033322 | 0.000619 | 0.000222 |
| N=100,000   | NA             | 3.33     | 0.006700 | 0.002205 |
| N=1,000,000 | NA             | NA       | 0.074870 | 0.022711 |

There are several important things worth noting in this table. For a small amount ofinput, the algorithms all run in the blink of an eye.  
So if only a small amount of input is expected, it might be silly to expend a great deal of effort to design a clever algorithm.  
Onthe other hand, there is a large market these days for rewriting programs that were writtenfive years ago based on a no-longer-valid assumption of small input size.  
These programsare now too slow because they used poor algorithms.  
For large amounts of input, algorithm4 is clearly the best choice (although algorithm 3 is still usable).

Second, the times given do not include the time required to read the input.  
For algo-rithm 4, the time merely to read the input from a disk is likely to be an order of magnitudelarger than the time required to solve the problem.  
This is typical of many efficient algo-rithms.  
Reading the data is generally the bottleneck;  
once the data are read, the problemcan  be  solved  quickly.  
For  inefficient  algorithms  this  is  not  true,  and  significant  com-puter resources must be used.  
Thus, it is important that, whenever possible, algorithmsbe efficient enough not to be the bottleneck of a problem.

Notice that for algorithm 4, which is linear, as the problem size increases by a factorof 10, so does the running time.  
Algorithm 2, which is quadratic, does not display thisbehavior;  
a tenfold increase in input size yields roughly a hundredfold (102) increase inrunning time.  
And algorithm 1, which is cubic, yields a thousandfold (103) increase inrunning time.  
We would expect algorithm 1 to take nearly 9,000 seconds (or two and ahalf hours) to complete forN=100,000.  
Similarly, we would expect algorithm 2 to takeroughly 333 seconds to complete forN=1,000,000.  
However, it is possible that algorithm2 could take somewhat longer to complete due to the fact thatN=1,000,000 could alsoyield slower memory accesses thanN=100,000 on modern computers, depending onthe size of the memory cache.

--------------------------------------------------------------------------------


### 2.4 Running-Time Calculations