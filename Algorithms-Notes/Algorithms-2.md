Algorithms-2.md

Notes of Algorithms 4th edition
================================================================================

Ad  
Init: 2018Oct08

2 Sorting
--------------------------------------------------------------------------------

### 2.1 ELementary Sorts

#### Rules of the game

```java
public class Example
{
    public static void sort(Comparable[] a)
    { /* see Algorithm 2.1, 2.2, 2.3, 2.4, 2.5, or 2.7 */ }

    private static boolean less(Comparable v, Comparable w)
    { return v.compareTo(w) < 0; }
    private static void exch(Comparable[] a, int i, int j)
    { Comparable t = a[i]; a[i] = a[j]; a[j] = t; }
    private static void show(Comparabe[] a)
    {
        // print the array, on a single line
        for (int i = 0; i < a.length; i++)
            StdOut.print(a[i] + " ");
        StdOut.println();
    }

    public static boolean isSorted(Comparable[] a)
    {
        // test whether the array entries are in order
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }
    public static void main(String[] args)
    {
        // read strings from standard input, sort them, and print
        String[] a = In.readStrings();
        sort(a);
        assert isSorted(a);
        show(a);
    }
}
```

This class illustrates our conventions for implementing array sorts.

##### Certification

As a conservative practice, we include the statement assert `isSorted(a);` in our test client to certify that array entries are in order after the sort.
It is reasonable to include this statement in *every* sort implementation.

##### Running time

> Sorting cost model.  
> When studying sorting algorithms, we count compares and exchanges.
> For algorithms that do not use exchanges, we count array accesses.

##### Extra memory

Some algorithms sort in place, the others need enough extra memory to hold another copy.

##### Types of data

The sort code is effective for any item type that implements the `Comparable` interface.

#### Selection sort

First, ﬁnd the smallest item in the array and exchange it with the ﬁrst entry (itself if the ﬁrst entry is already the smallest).
Then, ﬁnd the next smallest item and exchange it with the second entry.
Continue in this way until the entire array is sorted.

This method is called selection sort because it works by repeatedly selecting the smallest remaining item.

###### Algorithm 2.1 Selection sort

```java
public class Selection
{
    public static void sort(Comparable[] a)
    {
        // sort a[] into increasing order
        int N = a.length;
        for (int i = 0; i < N; i++)
        {
            // exchange a[i] with smallest entry in a[i+1...N]
            int min = i;
            for (int j = i + 1; j < N; j++)
                if (less(a[i], a[min])) min = j;
            exch(a, i, min);
        }
    }
    // see former section for other functions
}
```

> **Proposition A.**  
> Selection sort uses ~N^2/2 compares and N exchanges to sort an array of length N.
>
> **Proof:**  
> You can prove this fact by examining the trace, which is an N-by-N table in which unshaded letters correspond to compares. About one-half of the entries in the table are unshaded—those on and above the diagonal. The entries on the diagonal each correspond to an exchange. More precisely, examination of the code reveals that, for each i from 0 to N - 1, there is one exchange and N - 1 - i  compares, so the totals are N exchanges and (N - 1) + (N - 2) + . . . + 2 + 1+ 0 = N(N - 1) / 2 ~ N^2 / 2 compares.

##### Running time is insensitive to input

##### Data movement is minimal

The number of array accesses is a linear function of the array size.
None of the other sorting algorithms that we consider have this property.

#### Insertion sort

Like poker cards sorting, considering the cards one at a time, inserting each into its proper place among those already considered (keeping them sorted).

###### Algorithm 2.2 Insertion sort

```java
public class Insertion
{
    public static void sort(Comparable[] a)
    {
        // sort a[] into increasing order
        int N = a.length;
        for (int i = 1; i < N; i++)
        {
            // insert a[i] among a[i-1], a[i-2], a[i-3]...
            for (int j = i; j > 0 && less(a[j], a[j-1]); j--)
                exch(a, j, j-1);
        }
    }
    // other functions
}
```

> **Proposition B.**  
> Insertion sort uses ~N^2/4 compares and ~N^2/4 exchanges to sort a randomly ordered array of length N with distinct keys, on the average.  
> The worst case is ~N^2/2 compares and ~N^2/2 exchanges and the best case is N - 1 compares and 0 exchanges.
>
> **Proof:**  
> Just as for Proposition A, the number of compares and exchanges is easy to visualize in the N-by-N diagram that we use to illustrate the sort. We count entries below the diagonal—all of them, in the worst case, and none of them, in the best case. For randomly ordered arrays, we expect each item to go about halfway back, on the average, so we count one-half of the entries below the diagonal.  
> The number of compares is the number of exchanges plus an additional term equal to N minus the number of times the item inserted is the smallest so far. In the worst case (array in reverse order), this term is negligible in relation to the total; in the best case (array in order) it is equal to N  1.

**partially sorted**: If the number of inversions in an array is less than a constant multiple of the array size.  
Typical examples of partially sorted arrays are the following:
 - An array where each entry is not far from its ﬁnal position
 - A small array appended to a large sorted array
 - An array with only a few entries that are not in place

Insertion sort is an efﬁcient method for such arrays; selection sort is not. Indeed, when the number of inversions is low, insertion sort is likely to be faster than any sorting method that we consider in this chapter.

> **Proposition C.**  
> The number of exchanges used by insertion sort is equal to the number of inversions in the array, and the number of compares is at least equal to the number of inversions and at most equal to the number of inversions plus the array size minus 1.
>
> **Proof:**  
> Every exchange involves two inverted adjacent entries and thus reduces the number of inversions by one, and the array is sorted when the number of inversions reaches zero. Every exchange corresponds to a compare, and an additional compare might happen for each value of i from 1 to N-1 (when a[i] does not reach the left end of the array).

**In summary**, insertion sort is an excellent method for partially sorted arrays and is also a ﬁne method for tiny arrays. These facts are important not just because such arrays frequently arise in practice, but also because both types of arrays arise in intermediate stages of advanced sorting algorithms, so we will be considering insertion sort again in relation to such algorithms.

#### Visualizing sorting algorithms

#### Comparing two sorting algorithms

> **Property D.**  
> The running times of insertion sort and selection sort are quadratic and within a small constant factor of one another for randomly ordered arrays of distinct values.
>
> **Evidence:**  
> This statement has been validated on many different computers over the past half-century. Insertion sort was about twice as fast as selection sort when the ﬁrst edition of this book was written in 1980 and it still is today, even though it took several hours to sort 100,000 items with these algorithms then and just several seconds today. Is insertion sort a bit faster than selection sort on your computer? To ﬁnd out, you can use the class SortCompare on the next page, which uses the sort() methods in the classes named as command-line arguments to perform the given number of experiments (sorting arrays of the given size) and prints the ratio of the observed running times of the algorithms.

###### Comparing two sorting algorithms code

```java
public class SortCompare
{
    public static double time(String alg, Double[] a)
    {  /* See text. */  }
    public static double timeRandomInput(String alg, int N, int T)
    {
        // Use alg to sort T random arrays of length N.
        double total = 0.0;
        Double[] a = new Double[N];
        for (int t = 0; t < T; t++)
        {
            // Perform one experiment (generate and sort an array).
            for (int i = 0; i < N; i++)
                a[i] = StdRandom.uniform();
            total += time(alg, a);
        }
        return total;
    }
    public static void main(String[] args)
    {
        String alg1 = args[0];
        String alg2 = args[1];
        int N = Integer.parseInt(args[2]);
        int T = Integer.parseInt(args[3]);
        double t1 = timeRandomInput(alg1, N, T); // total for alg1
        double t2 = timeRandomInput(alg2, N, T); // total for alg2
        StdOut.printf("For %d random Doubles\n    %s is", N, alg1);
        StdOut.printf(" %.1f times faster than %s\n", t2/t1, alg2);
    }
}
```

This client runs the two sorts named in the ﬁrst two command-line arguments on arrays of N (the third command-line argument) random Double values between 0.0 and 1.0, repeating the experiment T (the fourth command-line argument) times, then prints the ratio of the total running times.

```java
% java SortCompare Insertion Selection 1000 100
For 1000 random Doubles
  Insertion is 1.7 times faster than Selection
```

#### Shellsort

The idea is to rearrange the array to give it the property that taking every hth entry (starting anywhere) yields a sorted subsequence. Such an array is said to be  h-sorted. Put another way, an h-sorted array is h independent sorted subsequences, interleaved together. By h-sorting for some large values of h, we can move items in the array long distances and thus make it easier to h-sort for smaller values of h. Using such a procedure for any sequence of values of h that ends in 1 will produce a sorted array: that is shellsort.

###### Algorithms 2.3 Shellsort

```java
public class Shell
{
    public static void sort(Comparable[] a)
    {
        // sort a[] into increasing order
        int N = a.length;
        int h = 1;
        while (h < N/3) h = 3 * h + 1; // 1, 4, 13, 40, 121, ....
        while (h >= 1)
        {
            // h-sort the array
            for (int i = h; i < N; i++)
            {
                // insert a[i] among a[i-h], a[i=2*h], a[i=3*h]...
                for (int j = i; j >= h && less(a[j], a[j-h]); j -= h)
                    exch(a, j, j-h);
            }
            h = h / 3;
        }
    }
    // other functions
}
```

If we modify insertion sort (Algorithm 2.2) to h-sort the array and add an outer loop to decrease h through a sequence of increments starting at an increment as large as a constant fraction of the array length and ending at 1, we are led to this compact shellsort implementation.

> **Property E.**  
> The number of compares used by shellsort with the increments 1, 4, 13, 40, 121, 364, . . . is bounded by a small multiple of N times the number of increments used.
>
> **Evidence:**  
> Instrumenting Algorithm 2.3 to count compares and divide by the number of increments used is a straightforward exercise (see Exercise 2.1.12). Extensive experiments suggest that the average number of compares per increment might be N 1/5, but it is quite difﬁcult to discern the growth in that function unless N is huge. This property also seems to be rather insensitive to the input model.

Experienced programmers sometimes choose shellsort because it has acceptable running time even for moderately large arrays; it requires a small amount of code; and it uses no extra space.

In the next few sections, we shall see methods that are more efﬁcient, but they are perhaps only twice as fast (if that much) except for very large N, and they are more complicated.  
If you need a solution to a sorting problem, and are working in a situation where a system sort may not be available (for example, code destined for hardware or an embedded system), you can safely use shellsort, then determine sometime later whether it will be worthwhile to replace it with a more sophisticated method.

#### Q&A of 2.1

Q. Why so many sorting algorithms?  
A. One reason is that the performance of many algorithms depends on the input values, so different algorithms might be appropriate for different applications having different kinds of input. For example, *insertion sort* is the method of choice for partially sorted or tiny arrays. Other constraints, such as space and treatment of equal keys, also come into play. We will revisit this question in Section 2.5.

--------------------------------------------------------------------------------

### 2.2 Mergesort

The mergesort guarantees to sort any array of N items in time proportional to NlogN.  
Its prime disadvantage is that it uses extra space proportional to N.

#### Abstract in-place merge

###### Abstract in-place merge code

```java
public static void merge(Comparable[] a, int lo, int mid, int hi)
{
    // merge a[lo...mid] with a[mid+1..hi]
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) // copy a[lo..hi] to aux[lo..hi]
        aux[k] = a[k];
    for (int k = lo; k <= hi; k++) // merge back to a[lo..hi]
        if      (i > mid)              a[k] = aux[j++];
        else if (j > hi)               a[k] = aux[i++];
        else if (less(aux[j], aux[i])) a[k] = aux[j++];
        else                           a[k] = aux[i++];
}
```

#### Top-down mergesort

> **Proposition F.**  
> Top-down mergesort uses between ½ N lg N and N lg N compares to sort any array of length N.
>
> **Proof:**  
> Let C(N) be the number of compares needed to sort an array of length N. We have C(0) = C(1) = 0 and for N > 0 we can write a   r ecurrence relationship that directly mirrors the recursive sort() method to establish an upper bound: C(N )  C(⎣N/2⎦)   C(⎡N/2⎤)  N The ﬁrst term on the right is the number of compares to sort the left half of the array, the second term is the number of compares to sort the right half, and the third......

###### Algorithm 2.4 Top-down mergesort

```java
public class Merge
{
    private static Comparable[] aux; // auxiliary array for merges
    public static void sort(Comparable[] a)
    {
        aux = new Comparable[a.length]; // allcate space just once
        sort(a, 0, a.length - 1);
    }
    private static void sort(Comparable[] a, int lo, int hi)
    {
        // sort a[lo..hi]
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, lo, mid); // sort left half
        sort(a, mid + 1, hi); // sort right half
        merge(a, lo, mid, hi); // merge results (code on page 271)
    }
}
```

> **Proposition G.**  
> Top-down mergesort uses at most 6N lg N array accesses to sort an array of length N.
>
> **Proof:**  
> Each merge uses at most 6N array accesses (2N for the copy, 2N for the move back, and at most 2N for compares). The result follows from the same argument as for Proposition F.

We can cut the running time of mergesort substantially with some carefully considered modifications.

##### Use insertion sort for small subarrays

Because the recursion guarantees that the method will be used often for small cases, and insertion sort is simple and therefore likely to be faster than mergesort for tiny subarrays.

##### Test whether the array is already in order

##### Eliminate the copy to the auxiliary array

#### Bottom-up mergesort

Another way to implement mergesort is to organize the merges so that we do all the merges of tiny subarrays on one pass, then do a second pass to merge those subarrays in pairs, and so forth, continuing until we do a merge that encompasses the whole array.

###### Bottom-up mergesort code

```java
public class MergeBU
{
    private static Comparable[] aux;
    // see p271 for merger() code

    public static void sort(Comparable[] a)
    {
        // do lg N passes of pairwise merges
        int N = a.length;
        aux = new Comparable[N];
        for (int sz = 1; sz < N; sz = sz+sz) // sz: subarray size
            for (int lo = 0; lo < N - sz; lo += sz + sz) // lo: subarray index
                merge(a, lo, lo + sz - 1, Math.min(lo + sz + sz - 1, N-1));
    }
}
```

> **Proposition H.**  
> Bottom-up mergesort uses between ½ N lg N and N lg N compares  and at most 6N lg N array accesses to sort an array of length N.
>
> **Proof:**  
> The number of passes through the array is precisely ⎣lg N⎦ (that is precisely the value of n such that 2n   N < 2n1). For each pass, the number of array accesses is exactly 6N and the number of compares is at most N and no less than N/ 2.

A version of bottom-up mergesort is the method of choice for sorting data organized in a  *linked list*. Consider the list to be sorted sublists of size 1, then pass through to make sorted subarrays of size 2 linked together, then size 4, and so forth. This method rearranges the links to sort the list *in place* (without creating any new list nodes).

#### The complexity of sorting

> **Proposition I.**  
> No c ompare-based sorting algorithm can guarantee to sort N items with fewer than lg(N !) ~ N lg N compares.
>
> **Proof:**  
> very long...
>
> **Proposition J.**  
> Mergesort is an asymptotically optimal compare-based sorting algorithm.
>
> **Proof:**  
> Precisely, we mean by this statement that both the number of compares used by mergesort in the worst case and the minimum number of compares that any compare-based sorting algorithm can guarantee are ~N lg N. Propositions H and I establish these facts.

--------------------------------------------------------------------------------

### 2.3 Quicksort

The quicksort algorithm’s desirable features are that it is in-place (uses only a small auxiliary stack) and that it requires time proportional to N log N on the average to sort an array of length N.  
Its primary drawback is that it is fragile in the sense that some care is involved in the implementation to be sure to avoid bad performance.

#### The basic algorithm

Quicksort is complementary to mergesort:
for mergesort, we break the array into two subarrays to be sorted and then combine the ordered subarrays to make the whole ordered array;
for quicksort, we rearrange the array such that, when the two subarrays are sorted, the whole array is ordered.
In the ﬁrst instance, we do the two recursive calls before working on the whole array;
in the second instance, we do the two recursive calls after working on the whole array.
For mergesort, the array is divided in half;
for quicksort, the position of the partition depends on the contents of the array.

###### Algorithm 2.5 Quicksort

```java
public class Quick
{
    public static void sort(Comparable[] a)
    {
        StdRandom.shuffle(a); // eliminate dependence on input
        sort(a, 0, a.length - 1);
    }
    private static void sort(Comparable[] a, int lo, int hi)
    {
        if (hi <= lo) return;
        int j = partition(a, lo, hi); // Partition (see p291)
        sort(a, lo, j - 1); // sort left part
        sort(a, j + 1, hi); // sort right part
    }
}
```

It is a  randomized algorithm, because it randomly shufﬂes the array before sorting it.
Our reason for doing so is to be able to predict (and depend upon) its performance characteristics, as discussed below.

To complete the implementation, we need to implement the partitioning method. We use the following general strategy: First, we arbitrarily choose a[lo] to be the   partitioning item—the one that will go into its ﬁnal position. Next, we scan from the left end of the array until we ﬁnd an entry greater than (or equal to) the partitioning item, and we scan from the right end of the array until we ﬁnd an entry less than (or equal to) the partitioning item. The two items that stopped the scans are out of place in the ﬁnal partitioned array, so we exchange them. Continuing in this way, we ensure that no array entries to the left of the left index i are greater than the partitioning item, and no array entries to the right of the right index j are less than the partitioning item. When the scan indices cross, all that we need to do to complete the partitioning process is to exchange the partitioning item a[lo] with the rightmost entry of the left subarray (a[j]) and return its index j.

###### Quicksort partitioning

```java
private static int partition(Comparable[] a, int lo, int hi)
{
    // partition into a[lo..i-1], a[i], a[i+1..hi]
    int i = lo, j = hi + 1; // left and right scan indices
    Comparable v = a[lo]; // partitioning item
    while (true)
    {
        // scan right, scan left, check for san complete, and exchange
        while (less(a[++i], v)) if (i == hi) break;
        while (less(v, a[--j])) if (j == lo) break;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, lo, hi); // put v = a[j] into position
    return j; // with a[lo..j-1] <= a[j] <= a[j+1..hi]
}
```

##### Partitioning in place

##### Staying in bounds

##### Preserving randomness

##### Terminating the loop

##### Handling items with keys equal to the partitioning item's key

It is best to stop the left scan for items with keys greater than or equal to the partitioning item’s key and the right scan for items with key less than or equal to the partitioning item’s key, as in Algorithm 2.5. Even though this policy might seem to create unnecessary exchanges involving items with keys equal to the partitioning item’s key, it is crucial to avoiding quadratic running time in certain typical applications (see Exercise 2.3.11).

##### Terminating the recursion

#### Performance characteristics

The inner loop of quicksort (in the partitioning method) increments an index and compares an array entry against a ﬁxed value. This simplicity is one factor that makes quicksort quick: it is hard to envision a shorter inner loop in a sorting algorithm.

The second factor that makes quicksort quick is that it uses few compares.

> **Proposition K.**  
> Quicksort uses ~ 2N ln N compares (and one-sixth that many exchanges) on the average to sort an array of length N with distinct keys.
>
> **Proof:**  
> long..

Despite its many assets, the basic quicksort program has one potential liability: it can be extremely inefﬁcient if the partitions are unbalanced. For example, it could be the case that the ﬁrst partition is on the smallest item, the second partition on the next smallest item, and so forth, so that the program will remove just one item for each call, leading to an excessive number of partitions of large subarrays. Avoiding this situation is the primary reason that we randomly shufﬂe the array before using quicksort. This action makes it so unlikely that bad partitions will happen consistently that we need not worry about the possibility.

> **Proposition L.**  
> Quicksort uses ~ N 2/2 compares in the worst case, but random shufﬂing protects against this case.

In summary, you can be sure that the running time of Algorithm 2.5 will be within a constant factor of 1.39N lg N whenever it is used to sort N items.

#### Algorithmic improvaments

##### Cutoff to insertion sort

 - Quicksort is slower than insertion sort for tiny subarrays
 - Being recursive, quicksort's sort() is certain to call itself for tiny subarrays

A simple change to Algorithm 2.5 accomplishes this improvement: replace the statement  
`if (hi <= lo) return;`  
in sort() with a statement that invokes insertion sort for small subarrays:  
`if (hi <= lo + M) {  Insertion.sort(a, lo, hi); return;  }`  
The optimum value of the cutoff M is system-dependent, but any value between 5 and 15 is likely to work well in most situations  (see Exercise 2.3.25).

##### Median-of-three partitioning

##### Entropy-optimal sorting

Arrays with large numbers of duplicate keys arise frequently in applications.
In such situations, the quicksort implementation that we have considered has acceptable performance, but it can be substantially improved.
For example, a subarray that consists solely of items that are equal (just one key value) does not need to be processed further, but our implementation keeps partitioning down to small subarrays.
In a situation where there are large numbers of duplicate keys in the input array, the recursive nature of quicksort ensures that subarrays consisting solely of items with keys that are equal will occur often.
There is potential for signiﬁcant improvement, from the linearithmic-time performance of the implementations seen so far to linear-time performance.

One straightforward idea is to partition the array into    three parts, one each for items with keys smaller than, equal to, and larger than the partitioning item’s key.

Dijkstra’s solution to this problem leads to the remarkably simple partition code shown on the next page.
It is based on a single left-to-right pass through the array that maintains a pointer lt such that a[lo..lt-1] is less than v, a pointer gt such that a[gt+1, hi] is greater than v, and a pointer i such that a[lt..i-1] are equal to v and a[i..gt] are not yet examined.
Starting with i equal to lo, we process a[i] using the 3-way comparison given us by the Comparable interface (instead of using less()) to directly handle the three possible cases:
 - a[i] less than v: exchange a[lt] with a[i] and increment both lt and
 - a[i] greater than v: exchange a[i] with a[gt] and decrement gt
 - a[i] equal to v: increment i

Each of these operations both maintains the invariant and decreases the value of gt-i (so that the loop terminates). Furthermore, every item encountered leads to an exchange except for those items with keys equal to the partitioning item’s key.

###### Quicksort with 3-way partitioning

```java
public class
{
    private static void sort(Comparable[] a, int lo, int hi)
    {
        // see p289 for public sort() that calls this method
        if (hi <= lo) return;
        int lt = lo, i = lo + 1, gt = hi;
        Comparable v = a[lo];
        while (i <= gt)
        {
            int cmp = a[i].compareTo(v);
            if (cmp < 0) exch(a, lt++, i++);
            if (cmp > 0) exch(a, i, gt--);
            else i++;
        } // now a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]
        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
    }
}
```

it uses many more exchanges than the standard 2-way partitioning method for the common case when the number of duplicate keys in the array is not high.
In the 1990s  J. Bentley and  D. McIlroy developed a clever implementation that overcomes this problem (see Exercise 2.3.22), and observed that 3-way partitioning makes quicksort asymptotically faster than mergesort and other methods in practical situations involving large numbers of equal keys.

> **Proposition M.**  
> No compare-based s orting algorithm can guarantee to sort N items  with fewer than NH - N compares, where H is the  Shannon entropy, deﬁned from the frequencies of key values.
>
> **Proof sketch:**  
> This result follows from a (relatively easy) generalization of the lower bound proof of Proposition I in Section 2.2.
>
> **Proposition N.**  
> Quicksort with 3 -way partitioning uses ~ (2ln 2) N H compares to sort N items, where H is the Shannon entropy, deﬁned from the frequencies of key values.
>
> **Proof sketch:**  
> This result follows from a (relatively difﬁcult) generalization of the average-case analysis of quicksort in Proposition K. As with distinct keys, this costs about 39 percent more than the optimum (but within a constant factor) .

#### Q&A of 2.3

Q. Randomly shufﬂing the array seems to take a signiﬁcant fraction of the total time for the sort. Is doing so really worthwhile?  
A. Yes. It protects against the worst case and makes the running time predictable. Hoare proposed this approach when he presented the algorithm in 1960—it is a prototypical (and among the ﬁrst) randomized algorithm.

--------------------------------------------------------------------------------

### 2.4 Priority Queues

We can use any priority queue as the basis for a sorting algorithm by inserting a sequence of items, then successively removing the smallest to get them out, in order.
An important sorting algorithm known as heapsort also follows naturally from our heapbased priority-queue implementations.

#### API of priority queues

###### API for a generic priority queue

| `public class`       | `MaxPQ< Key extends Comparable<Key>>`           |
| -------------------- | ----------------------------------------------- |
| `MaxPQ()`            | create a priority queue                         |
| `MaxPQ(int max)`     | create a priority queue of initial capacity max |
| `MaxPQ(Key[] a)`     | create a priority queue from the keys in a[]    |
| `void insert(Key v)` | insert a key into the priority queue            |
| `Key max()`          | return the largest key Key                      |
| `delMax()`           | return and remove the largest key               |
| `boolean isEmpty()`  | is the priority queue empty?                    |
| `int size()`         | number of keys in the priority queue            |

##### A priority-queue client

###### A priority-queue client code

```java
public class TopM
{
    public static void main(String[] args)
    {
        // Print the top M lines in the input stream.
        int M = Integer.parseInt(args[0]);
        MinPQ<Transaction> pq = new MinPQ<Transaction>(M+1);
        while (StdIn.hasNextLine())
        {
            // Create an entry from the next line and put on the PQ.
            pq.insert(new Transaction(StdIn.readLine()));
            if (pq.size() > M)
                pq.delMin(); // Remove minimum if M+1 entries on the PQ.
        } // Top M entries are on the PQ.
        Stack<Transaction> stack = new Stack<Transaction>();
        while (!pq.isEmpty()) stack.push(pq.delMin());
        for (Transaction t : stack) StdOut.println(t);
    }
}
```

Given an integer M from the command line and an input stream where each line contains a transaction, this MinPQ client prints the M lines whose numbers are the highest.
It does so by using our Transaction class (see page 79, Exercise 1.2.19, and Exercise 2.1.21) to build a priority queue using the numbers as keys, deleting the minimum after each insertion once the size of the priority queue reaches M.
Once all the transactions have been processed, the top M come off the priority queue in increasing order, so this code puts them on a stack, then iterates through the stack to reverse the order and print them in increasing order.

#### Elementary implementations

We can use an array or a linked list, kept in order or unordered. These implementations are useful for small priority queues, situations where one of the two operations are predominant, or situations where some assumptions can be made about the order of the keys involved in the operations.

##### Array representation (unordered)

##### Array representation (ordered)

##### Linked-list representations

The signiﬁcant difference between implementing stacks or queues and implementing priority queues has to do with performance. For stacks and queues, we were able to develop implementations of all the operations that take constant time; for priority queues, all of the elementary implementations just discussed have the property that either the insert or the remove the maximum operation takes linear time in the worst case.
The *heap* data structure that we consider next enables implementations where both operations are guaranteed to be fast.

#### Heap definitions

> **Definition.**  
> A binary tree is *heap-ordered* if the key in each node is larger than or equal to the keys in that node’s two children (if any).
>
> **Proposition O.**  
> The  largest key in a heap-ordered binary tree is found at the root.
>
> **Proof:**  
> By induction on the size of the tree.

##### Binary heap representation

If we use a linked representation for heap-ordered binary trees, we would need to have three links associated with each key to allow travel up and down the tree (each node would have one pointer to its parent and one to each child).

It is particularly convenient, instead, to use a *complete binary tree* like the one drawn at right.
We draw such a structure by placing the root node and then proceeding down the page and from left to right, drawing and connecting two nodes beneath each node on the previous level until we have drawn N nodes.
Complete trees provide the opportunity to use a compact array representation that does not involve explicit links. Speciﬁcally, we represent complete binary trees sequentially within an array by putting the nodes in  level order, with the root at position 1, its children at positions 2 and 3, their children in positions 4, 5, 6, and 7, and so on.

> **Definition.**  
> A binary heap is a collection of keys arranged in a complete heap-ordered binary tree, represented in level order in an array (not using the ﬁrst entry).

In a heap, the parent of the node in position k is in position *⎣k /2⎦* and, conversely, the two children of the node in position k are in positions *2k* and *2k + 1*.

Instead of using explicit links (as in the binary tree structures that we will consider in Chapter 3), we can travel up and down by doing simple arithmetic on array indices: to move up the tree from a[k] we set k to k/2; to move down the tree we set k to 2\*k or 2\*k+1.

> **Proposition P.**  
> The height of a complete  binary tree of size N is ⎣ lg N ⎦ .
>
> **Proof:**  
> The stated result is easy to prove by induction or by noting that the height increases by 1 when N is a power of 2.

