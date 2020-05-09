em2_algebra.md

Elementary Methematics: 2 Algebra
================================================================================

A~-1h01

--------------------------------------------------------------------------------

- [2.1 Rational Numbers](#21-rational-numbers)
- [2.2 Monomials and Polynomials](#22-monomials-and-polynomials)
- [2.3 Formulas of Abridged Multiplication](#23-formulas-of-abridged-multiplication)
- [2.4 Division of Polynomials](#24-division-of-polynomials)
- [2.5 Divisibility of Binomials](#25-divisibility-of-binomials)
- [2.6 Proportions](#26-proportions)
- [2.7 Equations: Common Information](#27-equations-common-information)
- [2.8 Main Ways Used at Solving of Equations](#28-main-ways-used-at-solving-of-equations)
- [2.9 Systems of 2 Simultaneous Linear Equations in 2 Unknowns](#29-systems-of-2-simultaneous-linear-equations-in-2-unknowns)
- [2.10 Systems of 3 Simultaneous Linear Equationss in 3 Unknowns](#210-systems-of-3-simultaneous-linear-equationss-in-3-unknowns)
- [2.11 Irrational Numbers](#211-irrational-numbers)
- [2.12 Quadratic Equation](#212-quadratic-equation)
- [2.13 Imaginary and Complex Numbers](#213-imaginary-and-complex-numbers)
- [2.14 Roots of a Quadratic Equation](#214-roots-of-a-quadratic-equation)
- [2.15 Equations of Higher Degrees](#215-equations-of-higher-degrees)
- [2.16 Principles of Vector Calculus](#216-principles-of-vector-calculus)
- [2.17 Complex Numbers](#217-complex-numbers)
- [2.18 Mathematical Induction（数学归纳法）](#218-mathematical-induction数学归纳法)
- [2.19 Inequalities: Common Information](#219-inequalities-common-information)
- [2.20 Proving and Solving of Inequalities](#220-proving-and-solving-of-inequalities)
- [2.21 Arithmetic and Geometric Progressions](#221-arithmetic-and-geometric-progressions)
- [2.22 Logarithms](#222-logarithms)
- [2.23 Theory of Combinations](#223-theory-of-combinations)

Algebraic Transformations
================================================================================

2.1 Rational Numbers
--------------------------------------------------------------------------------

- rational numbers: positive and negative numbers

> A number is called rational, if it may be presented as a vulgar, not a cancelled fraction of the shape: m/n, where m is an integer and n is a natural number.

- absolute value (modulus（模）)

2.2 Monomials and Polynomials
--------------------------------------------------------------------------------

- monomial（单项式）
- coefficient （系数） of a monomial
- similar/like monomials: identical or differed only be coefficients
- polynomial（多项式）
- degree of polynomial: the most degree of monomials forming the polynomial

2.3 Formulas of Abridged Multiplication
--------------------------------------------------------------------------------

- $(a \pm b)^2 = a^2 \pm 2ab + b^2$
- $(a + b)(a - b) = a^2 - b^2$
- $(a \pm b)^3 = a^3 \pm 3a^2b + 3ab^2 \pm b^3$
- $(a + b)(a^2 - ab + b^2) = a^3 + b^3$
- $(a - b)(a^2 + ab + b^2) = a^3 - b^3$

2.4 Division of Polynomials
--------------------------------------------------------------------------------

- division of polynomials（多项式除法）
- long division（长除法）
- linear binomial（线性二项式）: a polynomial of the 1st degree: $ax + b$
- division of polynomial by linear binomial
- Bezout's theorem（裴蜀定理）:  
  a polynomial $a_0 x^m + a_1 x^{m-1} + ... + a_m$ is divided by $x – b$ with a remainder $N = a_0 b^m + a_1 b^{m-1} + ... + a_m$

2.5 Divisibility of Binomials
--------------------------------------------------------------------------------

As consequences from Bezout’s theorem:

1. a difference of identical powers of two numbers is divided without a remainder by a difference of these two numbers,  
   i.e. (x^m – a^m) is divided by (x – a)
2. a difference of identical even powers of two numbers is divided without a remainder both by a difference and by a sum of these two numbers,  
   i.e. if m is an even number, then the binomial x^m – a^m is divided both (x – a) and by (x + a)  
   a difference of identical odd powers of two numbers isn’t divided by a sum of these two numbers.
3. a sum of identical powers of two numbers is never divided by a difference of these two numbers
4. a sum of identical odd powers of two numbers is divided without a remainder by a sum of these two numbers
5. a sum of identical even powers of two numbers is never divided both by difference and by a sum of these two numbers

- factoring of polynomials（因式分解）

2.6 Proportions
--------------------------------------------------------------------------------

- crosswise lied terms can be changed by places
- ratios in any proportion can be changed by places
- derived proportions:  
  $$\frac{a}{b} = \frac{c}{d} \implies \frac{ma + nb}{ka + lb} = \frac{mc + nd}{kc + ld}$$
  where m, n, k, l - any numbers

Algebraic Equations
================================================================================

2.7 Equations: Common Information
--------------------------------------------------------------------------------

- equality: 2 expressions (numerical or literal ones) jointed by sign "="
- identity: a valid numerical equality or a literal equality valid at *any* numerical values of letters
- equation: a literal equality valid only at *some* values (roots of an equation) of letters (unknowns)
- solving: procedure of finding all roots
- equivalent equations: have the same roots

2.8 Main Ways Used at Solving of Equations
--------------------------------------------------------------------------------

- identical transformations: replace equation by equivalent one:
  1. replacement of identical expression
  2. transferring terms of equation from one side to another
  3. multiplication/division of both sides by non-zero expression (number)
  4. raising/extracting both sides to/of an *odd* power/degree root:
     1. *even* power result in extraneous roots
     2. a *wrong* extraction of *even* degree root result in loss of roots

2.9 Systems of 2 Simultaneous Linear Equations in 2 Unknowns
--------------------------------------------------------------------------------

- linear equation in one unknown（一元一次方程）
- systems of two simultaneous linear equations in two unknowns（二元一次方程组）
- 2 basic solution methods:
  1. substitution（代入？换元？）
  2. addition or subtraction of equations
- the second order determinants（二阶行列式）
- Cramer's rule: solution using determinants
- investigation of solutions:
  1. coefficients at unknowns are disproportionate: single solution
  2. all coefficients are proportional: has an *infinite set of solutions*
  3. coefficients at unknowns are proportional, but disproportionate to free terms: no solutions

2.10 Systems of 3 Simultaneous Linear Equationss in 3 Unknowns
--------------------------------------------------------------------------------

- systems of 3 simultaneous linear equations in 3 unknowns
- 2 basic solution methods:
  - substitution
  - addition or subtraction of equations
- the third order determinants
- Cramer's rule for solution

2.11 Irrational Numbers
--------------------------------------------------------------------------------

- arithmetical root
- algebraic root
- irrational numbers
- formula of complicated radical（？）:  
  $$\sqrt{a \pm \sqrt{b}} = \sqrt{\frac{a + \sqrt{a^2 - b}}{2}} \pm \sqrt{\frac{a - \sqrt{a^2 - b}}{2}}$$

2.12 Quadratic Equation
--------------------------------------------------------------------------------

- quadratic equation（二次方程）
- non-reduced quadratic equation: $ax^2 + bx + c = 0$
- reduced quadratic equation: $x^2 + px + q = 0$
- pure quadratic equation: b or c = 0

2.13 Imaginary and Complex Numbers
--------------------------------------------------------------------------------

- imaginary numbers（虚数）
- imaginary unit: $i = \sqrt{-1}$
- real number（实数）
- complex number（复数）

2.14 Roots of a Quadratic Equation
--------------------------------------------------------------------------------

$$ ax^2 + bx + c = 0 \implies x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a} $$
$$ x^2 + px + q = 0 \implies x = -p / 2 \pm \sqrt{(p/2)^2 - q} $$

- discriminant（判别式）
  1. $b^2 - 4ac > 0$: 2 roots are different real numbers
  2. $b^2 - 4ac = 0$: 2 roots are equal real numbers
  3. $b^2 - 4ac < 0$: 2 roots are imaginary numbers
- Viete's Theorem（韦达定理）:  
  $x_1 + x_2 = -p$  
  $x_1 * x_2 = q$
- factoring of a quadratic trinomial:  
  $$ ax^2 + bx + c = a(x - x_1)(x - x_2) $$

2.15 Equations of Higher Degrees
--------------------------------------------------------------------------------

- biquadratic equation（四次方程？）: $ax^4 + xb^2 + c = 0$  
  solution: exchange $z = x^2$
- cubic equation: $ax^3 + bx^2 + cx + d = 0$  
  the known Cardano’s formulas for solution are very difficult and almost aren’t used in practice  
  another way to solve:
  1. find 1 root by selecting (these equations have always at least one real root, and an integer root of a cubic equation with integer coefficients is one of factors of a free term d). Coefficients of these equations have been selected usually so that the root is among not great integers, such as: 0, ±1, ±2, ±3, assume this root is x1. 
  2. the 2nd stage of solution is dividing of $ax^3 + bx^2 + cx + d$ by $x – x_1$. According to Bezout’s theorem this division is possible without a remainder, and receiving a quadratic equation, solving which we’ll find (or not!) the rest of the two roots.

Vectors and Complex Numbers
================================================================================

2.16 Principles of Vector Calculus
--------------------------------------------------------------------------------

- vectors, opposite vectors, zero vector, length (modulus) of vector, collinear（共线） vectors, coplanar（共面） vectors
- equality of vectors
- addition of vectors
- scalar product（数量积）((a,b)) is a number: a product of lengths (modules) of these vectors by cosine of angle between them
- a scalar product of two vectors is:
  - positive, if an angle between the vectors is acute（锐角）
  - negative, if an angle between the vectors is obtuse（钝角）
  - A scalar product of two non-zero vectors is equal to zero, if and only if an angle between the vectors is right（直角）, i.e. these vectors are perpendicular（垂直） (orthogonal（正交）)
- unit orthogonal vectors, coordinates of vector
- a = (x,y,z), b = (u,v,w) ==> (a,b) = xu + yv + zw
- vector product of vectors ([a,b]) is a vector:
  $$ [a,b] = \begin{vmatrix} i & j & k \\ x & y & z \\ u & v & w \end{vmatrix} = i\begin{vmatrix} y & z \\ v & w \end{vmatrix} - j\begin{vmatrix} x & z \\ u & w \end{vmatrix} + k\begin{vmatrix} x & y \\ u & v \end{vmatrix} $$
- necessary and sufficient condition of collinearity of vectors:
  $$ \begin{vmatrix} x & y \\ u & v \end{vmatrix} = \begin{vmatrix} x & z \\ u & w \end{vmatrix} = \begin{vmatrix} y & z \\ v & w \end{vmatrix} = 0 $$
- necessary and sufficient condition of coplanarity of vectors
  $$ \begin{vmatrix} x & y & z \\ u & v & w \\ p & q & r \end{vmatrix} = 0 $$

2.17 Complex Numbers
--------------------------------------------------------------------------------

- complex numbers: `abscissa（横坐标）` + `ordinate（纵坐标）` i
- conjugate complex numbers（共轭）: a + bi & a - bi
- pure imaginary number
- Multiplication of complex numbers:  
  $(a + bi)(c + di) = (ac - bd) + (ad + bc)i$  
  $(a + bi)(a - bi) = a^2 + b^2$
- modulus (r) and argument (φ) of a complex number
- trigonometric form of a complex number: a+bi = r(cosφ + i sinφ)
- Moivre's formula: $z^n = [r(cosφ + isinφ) = r^n(cosnφ + isinnφ)$


Inequalities
================================================================================

2.18 Mathematical Induction（数学归纳法）
--------------------------------------------------------------------------------

Assume it's necessary to prove a statement (formula, property etc.), depending on a natural number n. If:

1. this statement is valid for some natural number n0,
2. from validity of this statement at n = k its validity follows at n = k + 1  for any k >= n0,

then this statement is valid for any natural number n >= n0.

2.19 Inequalities: Common Information
--------------------------------------------------------------------------------

- strict inequality: $\gt, \lt$
- non-strict inequality: $\geq, \leq$
- some important inequalities:
  1. $|a + b| \leq |a| + |b|$ (modulus of sum is not more than sum of the modules)
  2. $a + 1/a \geq 2$, a - positive
  3. $\sqrt{ab} \leq \frac{a + b}{2}$ a, b - positive (geometric average is not more than arithmetic average, also for n numbers)

2.20 Proving and Solving of Inequalities
--------------------------------------------------------------------------------

- basic methods of proving of inequalities:
  1. using of the known or before proved inequality
  2. estimating of the sign of difference between sides of inequality
  3. reductio ad absurdum proof(反证法)
  4. using of an indefinite inequality
- solving of inequalities, equivalent inequalities
- double inequality: a < x < b

Sequences and Progressions
================================================================================

2.21 Arithmetic and Geometric Progressions
--------------------------------------------------------------------------------

- numerical sequences（数列）, general term（一般项？通项？） of numerical sequence
- arithmetic progression（等差数列）: $a_n = a_1 + (n - 1)d$, $S_n = [2a_1 + (n - 1)d] * n / 2$
- geometric progression（等比数列）: $b_n = b_1 + q^{n - 1}$, $S_n = \frac{b_1(1 - q^n)}{1 - q}$
- infinitely decreasing geometric progression: |q| < 1


Logarithmic and Exponential Equations
================================================================================

2.22 Logarithms
--------------------------------------------------------------------------------

- main properties of logarithms
  1. $\log{ab} = \log{a} + \log{b}$
  2. $\log{b^k} = k\log{b}$
  3. $\log_{b^k}{N^m} = \frac{m}{k} \log_b{N}$
  4. $\log_b{N} = log_a{N} / \log_a{b}$ (the transition module formula)
- common logarithm（常用对数）: $\lg = \log_{10}$
- natural logarithm（自然对数）: $\ln = \log_e$

Theory of Combinations
================================================================================

2.23 Theory of Combinations
--------------------------------------------------------------------------------

- permutations（全排列）: total quantity of permutations of n elements  
  $$ P_n = 1 * 2 * ... * n = n! $$
- factorial（阶乘）
- arrangements（排列）: total quantity of arrangements of n elements taken m at a time  
  $$ A_n^m = n(n-1)...(n-m+1) = \frac{n!}{(n-m)!} $$
- combinations（组合）: total quantity of combination of n elements taken m at a time  
  $$ C_n^m = \frac{A_n^m}{m!} = \frac{n!}{m! * (n-m)!} $$
- Newton's binomial:  
  $$ (a + b)^n = a^n + C_n^1 a^{n-1}b + C_n^2 a^{n-2}b^2 + ... + C_n^{n-1} ab^{n-1} + b^n $$
- Pascal's triangle

--------------------------------------------------------------------------------

ref: bymath.com

EOF
