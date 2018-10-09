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
