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
    - [2.4.1 A Simple Example](#241-a-simple-example)
    - [2.4.2 General Rules](#242-general-rules)
    - [2.4.3 Solutions for the Maximum Subsequence Sum Problem](#243-solutions-for-the-maximum-subsequence-sum-problem)
    - [2.4.4 Logarithms in the Running Time](#244-logarithms-in-the-running-time)


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

If two programs are expected to take similar times, probably the bestway to decide which is faster is to code them both and run them!

To simplify the analysis, we will adopt the convention that there are no particular units of time.  
Thus, we throw away leading constants.  
We will also throw away low-order terms, so what we are essentially doing is computing a Big-Oh running time.  
Since Big-Oh is an upper bound, we must be careful never to underestimate the running timeof the program.  
In effect, the answer provided is a guarantee that the program will ter-minate within a certain time period.  
The program may stop earlier than this, but neverlater.


#### 2.4.1 A Simple Example

Here is a simple program fragment to calculate $\sum_{i=1}^N i^3$:

```cs
int sum(int n)
{
    int partialSum;
    
    partialSum = 0;                 // Line 1
    for(int i = 1; i <= n; ++i)     // Line 2
        partialSum += i * i * i;    // Line 3
    
    return partialSum;              // Line 4
}
```

The analysis of this fragment is simple.  
The declarations count for no time.  
Lines 1 and 4 count for one unit each.  
Line 3 counts for four units per time executed (two multiplica-tions, one addition, and one assignment) and is executed N times, for a total of 4N units.  
Line 2 has the hidden costs of initializing i, testing i≤N, and incrementing i.  
The total cost of all these is 1 to initialize, N+1 for all the tests, and N for all the increments, whichis 2N+2.  
We ignore the costs of calling the function and returning, for a total of 6N+4.  
Thus, we say that this function is O(N).

If we had to perform all this work every time we needed to analyze a program, the task would quickly become infeasible.  
Fortunately, since we are giving the answer in termsof Big-Oh, there are lots of shortcuts that can be taken without affecting the final answer.  
For instance, line 3 is obviously an O(1) statement (per execution), so it is silly to count precisely whether it is two, three, or four units;  
it does not matter.  
Line 1 is obviouslyin significant compared with the for loop, so it is silly to waste time here.  
This leads to several general rules.


#### 2.4.2 General Rules


###### Rule 1 - FOR loops

The running time of a for loop is at most the running time of the statements inside the for loop (including tests) times the number of iterations.


###### Rule 2 - Nested loops

Analyze these inside out.  
The total running time of a statement inside a group of nested loops is the running time of the statement multiplied by the product of the sizes of all the loops.

As an example, the following program fragment is $O(N^2)$:

```cs
for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
        ++k;
```


###### Rule 3 - Consecutive Statements

These just add (which means that the maximum is the one that counts;  
see rule 1 on page 52).

As an example, the following program fragment, which has $O(N)$ work followed by $O(N^2)$ work, is also $O(N^2)$:

```cs
for (i = 0; i < n; ++i)
    a[i]=0;
for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
        a[i] += a[j] + i + j;
```


###### Rule 4 - If/Else

For the fragment

```cs
if (condition)
    S1
else
    S2
```

the running time of an if/else statement is never more than the running time of the test plus the larger of the running times of S1 and S2.

Clearly, this can be an overestimate in some cases, but it is never an underestimate.

Other rules are obvious, but a basic strategy of analyzing from the inside (or deepest part) out works.  
If there are function calls, these must be analyzed first.  
If there are recursive functions, there are several options.  
If the recursion is really just a thinly veiled for loop, the analysis is usually trivial.  
For instance, the following function is really just a simple loop and is $O(N)$:

```cs
long factorial(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}
```

This example is really a poor use of recursion.  
**When recursion is properly used, it is difficult to convert the recursion into a simple loop structure.**  
In this case, the analysis will involve a recurrence relation that needs to be solved.  
To see what might happen, consider the following program, which turns out to be a terrible use of recursion:

```cs
long fib(int n)
{
    if (n <= 1)                         // Line 1
        return 1;                       // Line 2
    else
        return fib(n - 1) + fib(n - 2); // Line 3
}
```

At first glance, this seems like a very clever use of recursion.  
However, if the program is coded up and run for values of N around 40, it becomes apparent that this program is terribly inefficient.

The analysis is fairly simple.  
Let T(N) be the running time for the function call `fib(n)`.  
If N=0 or N=1, then the running time is some constant value, which is the time to do the test at line 1 and return.  
We can say that $T(0)=T(1)=1$ because constants do not matter.  
The running time for other values of N is then measured relative to the running time of the base case.  
For N>2, the time to execute the function is the constant work at line 1 plus the work at line 3.  
Line 3 consists of an addition and two function calls.  
Since the function calls are not simple operations, they must be analyzed by themselves.  
The first function call is fib(n-1) and hence, by the definition of T, requires T(N−1) units of time.  
A similar argument shows that the second function call requires T(N−2) units of time.  
The total time required is then $T(N−1)+T(N−2)+2$, where the 2 accounts for the work at line 1 plus the addition at line 3.  
Thus, for N≥2, we have the following formula for the running time of fib(n):

$$ T(N) = T(N−1) + T(N−2) + 2 $$

Since `fib(n) = fib(n-1) + fib(n-2)`, it is easy to show by induction that T(N)≥fib(n).  
In Section 1.2.5, we showed that $fib(N)<(5/3)^N$.  
A similar calculation shows that (for N>4) $fib(N)≥(3/2)^N$, and so the running time of this program grows *exponentially*.  
This is about as bad as possible.  
By keeping a simple array and using a for loop, the running time can be reduced substantially.

This program is slow because there is a huge amount of redundant work being performed, violating the fourth major rule of recursion (the compound interest rule), which was presented in Section 1.3.  
Notice that the first call on line 3, fib(n-1), actually computes fib(n-2) at some point.  
This information is thrown away and recomputed by thesecond call on line 3.  
The amount of information thrown away compounds recursively and results in the huge running time.  
This is perhaps the finest example of the maxim “Don’t compute anything more than once” and should not scare you away from using recursion.  
Throughout this book, we shall see outstanding uses of recursion.


#### 2.4.3 Solutions for the Maximum Subsequence Sum Problem

We will now present four algorithms to solve the maximum subsequence sum  problem posed earlier.

The first algorithm, which merely exhaustively tries all possibilities, is depicted in Figure 2.5.  
The indices in the for loop reflect the fact that in C++, arrays begin at 0 instead of 1.  
Also, the algorithm does not compute the actual subsequences;  
additional code is required to do this.


###### Figure 2.5 Algorithm 1

```cs
/*01*/  /**
/*02*/   * Cubic maximum contiguous subsequence sum algorithm.
/*03*/   */
/*04*/  int maxSubSum1( const vector<int> & a )
/*05*/  {
/*06*/      int maxSum = 0;
/*07*/  
/*08*/      for( int i = 0; i < a.size( ); ++i )
/*09*/          for( int j = i; j < a.size( ); ++j )
/*10*/          {
/*11*/              int thisSum = 0;
/*12*/  
/*13*/              for( int k = i; k <= j; ++k )
/*14*/                  thisSum += a[ k ];
/*15*/  
/*16*/              if( thisSum > maxSum )
/*17*/                  maxSum = thisSum;
/*18*/          }
/*19*/  
/*20*/      return maxSum;
/*21*/  }
```

Convince yourself that this algorithm works (this should not take much convincing).  
The running time is $O(N^3)$ and is entirely due to lines 13 and 14, which consist of an O(1) statement buried inside three nested for loops.  
The loop at line 8 is of size N.

The second loop has size N−i, which could be small but could also be of size N.  
We must assume the worst, with the knowledge that this could make the final bound a bit high.  
The third loop has size j−i+1, which again we must assume is of size N.  
The total is $O(1·N·N·N)=O(N^3)$.  
Line 6 takes only O(1) total, and lines 16 and 17 take only O(N^2) total, since they are easy expressions inside only two loops.

It turns out that a more precise analysis, taking into account the actual size of theseloops, shows that the answer is $Θ(N^3)$ and that our estimate above was a factor of 6 too high (which is all right, because constants do not matter).  
This is generally true in thesekinds of problems.  
The precise analysis is obtained from the sum $\sum_{i=0}^{N-1} \sum_{j=i}^{N-1} \sum_{k=i}^j 1$, which tells how many times line 14 is executed.  
The sum can be evaluated inside out,using formulas from Section 1.2.3.  
In particular, we will use the formulas for the sum ofthe firstNintegers and firstNsquares.  
First we have

$$ \sum_{k=i}^j 1 = j−i+1 $$

Next we evaluate

$$ \sum^{N−1}_{j=i} (j−i+1) = \frac{(N−i+1)(N−i)}{2} $$

This sum is computed by observing that it is just the sum of the first N−i integers.  
Tocomplete the calculation, we evaluate

$$ \sum^{N−1}_{i=0} \frac{(N−i+1)(N−i)}{2} = \sum^N_{i=1} \frac{(N−i+1)(N−i+2)}{2} $$
$$ = 1/2 \sum^N_{i=1} i^2 − (N+3/2) \sum^N_{i=1} i + 1/2(N^2+3N+2) \sum^N_{i=1} 1 $$
$$ = 1/2 \frac{N(N+1)(2N+1)}{6} − (N+3/2) \frac{N(N+1)}{2} + \frac{N^2+3N+2}{2} N $$
$$ = \frac{N^3+3N^2+2N}{6} $$

We can avoid the cubic running time by removing a for loop.  
This is not always possible, but in this case there are an awful lot of unnecessary computations present in thealgorithm.  
The inefficiency that the improved algorithm corrects can be seen by noticing that $\sum^j_{k=i} A_k = A_j + \sum^{j−1}_{k=i} A_k$, so the computation at lines 13 and 14 in algorithm 1 is unduly expensive.  
Figure 2.6 shows an improved algorithm.  
Algorithm 2 is clearly $O(N^2)$;  
the analysis is even simpler than before.


###### Figure 2.6 Algorithm 2

```cs
/*01*/  /**
/*02*/   * Quadratic maximum contiguous subsequence sum algorithm.
/*03*/   */
/*04*/  int maxSubSum2( const vector<int> & a )
/*05*/  {
/*06*/      int maxSum = 0;
/*07*/  
/*08*/      for( int i = 0; i < a.size( ); ++i )
/*09*/      {
/*10*/          int thisSum = 0;
/*11*/          for( int j = i; j < a.size( ); ++j )
/*12*/          {
/*13*/              thisSum += a[ j ];
/*14*/  
/*15*/              if( thisSum > maxSum )
/*16*/              maxSum = thisSum;
/*17*/          }
/*18*/      }
/*19*/  
/*20*/      return maxSum;
/*21*/  }
```

There is a recursive and relatively complicated $O(NlogN)$ solution to this problem, which we now describe.  
If there didn’t happen to be an O(N) (linear) solution, this wouldbe  an  excellent  example  of  the  power  of  recursion.  
The  algorithm  uses  a  “divide-and-conquer” strategy.  
The idea is to split the problem into two roughly equal subproblems, which are then solved recursively.  
This is the “divide” part.  
The “conquer” stage consistsof patching together the two solutions of the subproblems, and possibly doing a smallamount of additional work, to arrive at a solution for the whole problem.

In our case, the maximum subsequence sum can be in one of three places.  
Either itoccurs entirely in the left half of the input, or entirely in the right half, or it crosses themiddle and is in both halves.  
The first two cases can be solved recursively.  
The last casecan be obtained by finding the largest sum in the first half that includes the last elementin the first half, and the largest sum in the second half that includes the first element inthe second half.  
These two sums can then be added together.  
As an example, consider thefollowing input:

```
First Half | Second Half
------------------------
 4 −3 5 −2 | −1 2 6 −2
```

The maximum subsequence sum for the first half is 6 (elementsA1throughA3)andforthe second half is 8 (elementsA6throughA7).

The maximum sum in the first half that includes the last element in the first half is 4(elementsA1throughA4), and the maximum sum in the second half that includes the firstelement in the second half is 7 (elementsA5throughA7).  
Thus, the maximum sum thatspans both halves and goes through the middle is 4+7=11 (elementsA1throughA7).

We see, then, that among the three ways to form a large maximum subsequence, forour example, the best way is to include elements from both halves.  
Thus, the answer is 11.  
Figure 2.7 shows an implementation of this strategy.


###### Figure 2.7 Algorithm 3

```cs
/*01*/  /**
/*02*/   * Recursive maximum contiguous subsequence sum algorithm.
/*03*/   * Finds maximum sum in subarray spanning a[left..right].
/*04*/   * Does not attempt to maintain actual best sequence.
/*05*/   */
/*06*/  int maxSumRec( const vector<int> & a, int left, int right )
/*07*/  {
/*08*/      if( left == right )  // Base case
/*09*/          if( a[ left]>0)
/*10*/              return a[ left ];
/*11*/          else
/*12*/              return 0;
/*13*/  
/*14*/  int center = ( left + right ) / 2;
/*15*/  int maxLeftSum  = maxSumRec( a, left, center );
/*16*/  int maxRightSum = maxSumRec( a, center + 1, right );
/*17*/  
/*18*/  int maxLeftBorderSum = 0, leftBorderSum = 0;
/*19*/  for( int i = center; i >= left; --i )
/*20*/  {
/*21*/      leftBorderSum += a[ i ];
/*22*/      if( leftBorderSum > maxLeftBorderSum )
/*23*/          maxLeftBorderSum = leftBorderSum;
/*24*/  }
/*25*/  
/*26*/  int maxRightBorderSum = 0, rightBorderSum = 0;
/*27*/  for( int j = center + 1; j <= right; ++j )
/*28*/  {
/*29*/      rightBorderSum += a[ j ];
/*30*/      if( rightBorderSum > maxRightBorderSum )
/*31*/          maxRightBorderSum = rightBorderSum;
/*32*/  }
/*33*/  
/*34*/  return max3( maxLeftSum, maxRightSum,
/*35*/              maxLeftBorderSum + maxRightBorderSum );
/*36*/  }
/*37*/  
/*38*/  /**
/*39*/   * Driver for divide-and-conquer maximum contiguous
/*40*/   * subsequence sum algorithm.
/*41*/   */
/*42*/  int maxSubSum3( const vector<int> & a )
/*43*/  {
/*44*/      return maxSumRec( a, 0, a.size( ) - 1 );
/*45*/  }
```

The code for algorithm 3 deserves some comment.  
The general form of the call for therecursive function is to pass the input array along with the left and right borders, whichdelimits the portion of the array that is operated upon.  
A one-line driver program sets thisup by passing the borders 0 andN−1 along with the array.

Lines 8 to 12 handle the base case.  
Ifleft == right, there is one element, and it isthe maximum subsequence if the element is nonnegative.  
The caseleft > rightis notpossible unlessNis negative (although minor perturbations in the code could mess thisup).  
Lines 15 and 16 perform the two recursive calls.  
We can see that the recursive callsare always on a smaller problem than the original, although minor perturbations in thecode could destroy this property.  
Lines 18 to 24 and 26 to 32 calculate the two maxi-mum sums that touch the center divider.  
The sum of these two values is the maximumsum that spans both halves.  
The routinemax3(not shown) returns the largest of the threepossibilities.

Algorithm 3 clearly requires more effort to code than either of the two previous algo-rithms.  
However, shorter code does not always mean better code.  
As we have seen in theearlier table showing the running times of the algorithms, this algorithm is considerablyfaster than the other two for all but the smallest of input sizes.

The running time is analyzed in much the same way as for the program that computesthe Fibonacci numbers.  
LetT(N) be the time it takes to solve a maximum subsequencesum problem of sizeN.IfN=1, then the program takes some constant amount of timeto execute lines 8 to 12, which we shall call one unit. Thus,T(1)=1.  
Otherwise, the program must perform two recursive calls, the twoforloops between lines 19 and 32, andsome small amount of bookkeeping, such as lines 14 and 34.  
The twoforloops combineto touch every element in the subarray, and there is constant work inside the loops, so thetime expended in lines 19 to 32 isO(N).  
The code in lines 8 to 14, 18, 26, and 34 is alla constant amount of work and can thus be ignored compared withO(N).  
The remainderof the work is performed in lines 15 and 16.  
These lines solve two subsequence problemsof sizeN/2 (assumingNis even).  
Thus, these lines takeT(N/2) units of time each, for atotal of 2T(N/2).  
The total time for the algorithm then is 2T(N/2)+O(N).  
This gives the equations

$$ T(1) = 1 $$
$$ T(N) = 2T(N/2)+O(N) $$

To simplify the calculations, we can replace theO(N) term in the equation above withN;sinceT(N) will be expressed in Big-Oh notation anyway, this will not affect the answer.  
In  Chapter  7,  we  shall  see  how  to  solve  this  equation  rigorously.  
For  now,  ifT(N)=2T(N/2)+N,andT(1)=1, thenT(2)=4=2∗2,T(4)=12=4∗3,T(8)=32=8∗4,andT(16)=80=16∗5.  
The pattern that is evident, and can be derived, is that if $N=2^k$, then $T(N)=N∗(k+1)=NlogN+N=O(NlogN)$.

This analysis assumesNis even, since otherwiseN/2 is not defined.  
By the recursivenature of the analysis, it is really valid only whenNis a power of 2, since otherwise weeventually get a subproblem that is not an even size, and the equation is invalid.  
WhenNis not a power of 2, a somewhat more complicated analysis is required, but the Big-Ohresult remains unchanged.

In future chapters, we will see several clever applications of recursion.  
Here, we presenta fourth algorithm to find the maximum subsequence sum.  
This algorithm is simpler toimplement than the recursive algorithm and also is more efficient.  
It is shown in Figure 2.8.


###### Figure 2.8 Algorithm 4

```cs
/*01*/  /**
/*02*/   * Linear-time maximum contiguous subsequence sum algorithm.
/*03*/   */
/*04*/  int maxSubSum4( const vector<int> & a )
/*05*/  {
/*06*/      int maxSum = 0, thisSum = 0;
/*07*/  
/*08*/      for( int j = 0; j < a.size( ); ++j )
/*09*/      {
/*10*/          thisSum += a[ j ];
/*11*/  
/*12*/          if( thisSum > maxSum )
/*13*/              maxSum = thisSum;
/*14*/          else if( thisSum < 0 )
/*15*/              thisSum = 0;
/*16*/      }
/*17*/  
/*18*/      return maxSum;
/*19*/  }
```

It should be clear why the time bound is correct, but it takes a little thought to see whythe algorithm actually works.  
To sketch the logic, note that like algorithms 1 and 2, j is representing the end of the current sequence, whileiis representing the start of the currentsequence.  
It happens that the use ofican be optimized out of the program if we do notneed to know where the actual best subsequence is, but in designing the algorithm, let’spretend thatiis needed and that we are trying to improve algorithm 2.  
One observationis that ifa[i]is negative, then it cannot possibly be the start of the optimal subsequence,since any subsequence that begins by includinga[i]would be improved by beginningwitha[i+1].  
Similarly, any negative subsequence cannot possibly be a prefix of the optimalsubsequence (same logic).  
If, in the inner loop, we detect that the subsequence froma[i]toa[j]is negative, then we can advancei.  
The crucial observation is that not only can weadvanceitoi+1, but we can also actually advance it all the way toj+1.  
To see this, letpbeany index betweeni+1andj.  
Any subsequence that starts at indexpis not larger than thecorresponding subsequence that starts at indexiand includes the subsequence froma[i]toa[p-1], since the latter subsequence is not negative (jis the first index that causes thesubsequence starting at indexito become negative).  
Thus, advancingitoj+1is risk free;we cannot miss an optimal solution.

This  algorithm  is  typical  of  many  clever  algorithms:  
The  running  time  is  obvious,but the correctness is not.  
For these algorithms, formal correctness proofs (more formal than the sketch above) are almost always required;  
even then, many people still are notconvinced.  
Also, many of these algorithms require trickier programming, leading to longerdevelopment.  
But when these algorithms work, they run quickly, and we can test muchof the code logic by comparing it with an inefficient (but easily implemented) brute-forcealgorithm using small input sizes.

An extra advantage of this algorithm is that it makes only one pass through the data,and oncea[i]is read and processed, it does not need to be remembered.  
Thus, if thearray is on a disk or is being transmitted over the Internet, it can be read sequentially, andthere is no need to store any part of it in main memory.  
Furthermore, at any point in time,the algorithm can correctly give an answer to the subsequence problem for the data it hasalready read (the other algorithms do not share this property).  
Algorithms that can do thisare called **online algorithms**.  
An online algorithm that requires only constant space andruns in linear time is just about as good as possible.


#### 2.4.4 Logarithms in the Running Time