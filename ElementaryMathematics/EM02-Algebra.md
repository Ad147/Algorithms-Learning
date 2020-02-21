EM02-Algebra.md

Elementary Methematics
================================================================================

Ad

Init: 19Aug01

2 Algebra
--------------------------------------------------------------------------------

### 2.1 Algebraic Transformations

#### 2.1.1 Rational Numbers

- **Positive** & **negative** numbers
- **Rational numbers**
- **Absolute value (modulus)**

#### 2.1.2 Monomials and Polynomials

- **Monomial**
- **Coefficient** of a monomial
- **Similar/like monomials**: identical or differed only be coefficients
- Reducing of like terms
- **Polynomial**
- **Degree of polynomial**: the most degree of monomials forming the polynomial

#### 2.1.3 Formulas of Abridged Multiplication

- $(a \pm b)^2 = a^2 \pm 2ab + b^2$
- $(a + b)(a - b) = a^2 - b^2$
- $(a \pm b)^3 = a^3 \pm 3a^2b + 3ab^2 \pm b^3$
- $(a + b)(a^2 - ab + b^2) = a^3 + b^3$
- $(a - b)(a^2 + ab + b^2) = a^3 - b^3$

#### 2.1.4 Division of Polynomials

- **Division of polynomials**
- **Long division**
- **Linear binomial**: a polynomial of the 1st degree: $ax + b$
- *Bezout's theorem*:  
  a polynomial $a_0 x^m + a_1 x^{m-1} + ... + a_m$ is divided by $x – b$ with a remainder $N = a_0 b^m + a_1 b^{m-1} + ... + a_m$

#### 2.1.7 Divisibility of Binomials

As consequences from *Bezout’s theorem*:

1. A difference of identical powers of two numbers is divided without a remainder by a difference of these two numbers, i.e. (x^m – a^m) is divided by (x – a)
2. A difference of identical even powers of two numbers is divided without a remainder both by a difference and by a sum of these two numbers, i.e. if m is an even number, then the binomial x^m – a^m is divided both (x – a) and by (x + a)  
   A difference of identical odd powers of two numbers isn’t divided by a sum of these two numbers.
3. A sum of identical powers of two numbers is never divided by a difference of these two numbers
4. A sum of identical odd powers of two numbers is divided without a remainder by a sum of these two numbers
5. A sum of identical even powers of two numbers is never divided both by difference and by a sum of these two numbers

#### 2.1.8 Factoring of Polynomials

#### 2.1.9 Proportions

- **Crosswise lied terms** can be changed by places
- **Derived proportions**:  
  $$\frac{a}{b} = \frac{c}{d} \implies \frac{ma + nb}{ka + lb} = \frac{mc + nd}{kc + ld}$$
  where m, n, k, l - any numbers

--------------------------------------------------------------------------------

### 2.2 Algebraic Equations

#### 2.2.1 Equations: Common Information

- **Equality**: 2 expressions (numerical or literal ones) jointed by sign "="
- **Identity**: a valid equality, valid at *any* numerical values of letters
- **Equation**: a literal equality valid only at *some* values (**roots of an equation**) of letters (**unknowns**)
- **Solving**: procedure of finding all roots
- **Equivalent equations**: have the same roots

#### 2.2.2 Main Ways Used at Solving of Equations

- **Identical transformations**: replace equation by equivalent one
  1. Replacement of identical expression
  2. Transferring terms of equation from one side to another
  3. Multiplication/division of both sides by non-zero expression (number)
  4. Raising/extracting both sides to/of an *odd* power/degree root
     1. *even* power result in extraneous roots
     2. a *wrong* extraction of *even* degree root result in loss of roots

#### 2.2.3 Linear Equations in One Unknown

#### 2.2.4 Systems of 2 simultaneous linear equations in 2 unknowns

- **Systems of two simultaneous linear equations in two unknowns**
- 2 basic methods of solution:
  1. **Substitution**
  2. Addition or subtraction of equations
- **The second order determinants**
- *Cramer's rule*
- Investigation of solutions:
  1. coefficients at unknowns are disproportionate: single solution
  2. all coefficients are proportional: has an *infinite set of solutions*
  3. coefficients at unknowns are proportional, but disproportionate to free terms: no solutions

#### 2.2.5 Systems of 3 simultaneous linear equationss in 3 unknowns

- Systems of three simultaneous linear equations in three unknowns
- Basic methods of solution:
  - Substitution
  - Addition or subtraction of equations
- **The third order determinants**
- *Cramer's rule*

#### 2.2.6 Arithmetical root

- **Arithmetical root**
- **Algebraic root**

#### 2.2.7 Irrational Numbers

- **Irrational numbers**
- **Formula of complicated radical**:  
  $$\sqrt{a \pm \sqrt{b}} = \sqrt{\frac{a + \sqrt{a^2 - b}}{2}} \pm \sqrt{\frac{a - \sqrt{a^2 - b}}{2}}$$

#### 2.2.8 Quadratic Equation

- A **quadratic equation** is an algebraic equation of the second degree
- **Non-reduced** quadratic equation: $ax^2 + bx + c = 0$
- **Reduced** quadratic equation: $x^2 + px + q = 0$
- **Pure** quadratic equation: b or c = 0

#### 2.2.9 Imaginary and Complex Numbers

- **Imaginary Numbers**: 2nd power is negative
- Imaginary unit: $i = \sqrt{-1}$
- **Real number**
- **Complex number**: sum of real and imaginary numbers

#### 2.2.10 Roots of a Quadratic Equation

$$ ax^2 + bx + c = 0 \implies x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a} $$
$$ x^2 + px + q = 0 \implies x = -p / 2 \pm \sqrt{(p/2)^2 - q} $$

1. $b^2 - 4ac > 0$: 2 roots are different real numbers
2. $b^2 - 4ac = 0$: 2 roots are equal real numbers
3. $b^2 - 4ac < 0$: 2 roots are imaginary numbers

- *Viete's Theorem*:  
  $x_1 + x_2 = -p$  
  $x_1 * x_2 = q$

#### 2.2.11 Factoring of a Quadratic Trinomial

$$ ax^2 + bx + c = a(x - x_1)(x - x_2) $$

#### Equations of Higher Degrees

- **Biquadratic equation**: $ax^4 + xb^2 + c = 0$
  - Solution: $z = x^2$
- **Cubic equation**: $ax^3 + bx^2 + cx + d = 0$  
  The known Cardano’s formulas for solution are very difficult and almost aren’t used in practice.  
  Another way to solve:
  1. At first we find one root of the equation by selecting, because these equations have always at least one real root, and an integer root of a cubic equation with integer coefficients is one of factors of a free term d. Coefficients of these equations have been selected usually so that the root, which must be found, is among not great integers, such as: 0, ± 1, ± 2, ± 3. Therefore, we’ll find the root among these numbers and check it by substituting into the equation. A probability of successful result is very high. Assume this root is x1. 
  2. The second stage of solution is dividing of the third degree polynomial ax3 + bx2 + cx + d   by the binomial  ( x – x1 ) . According to Bezout’s theorem this division is possible without a remainder, and we’ll receive as a result the second degree polynomial, which would be annihilated, will give us a quadratic equation, solving which we’ll find (or not !) the rest of the two  roots.

--------------------------------------------------------------------------------

### 2.3 Vectors and Complex Numbers

#### 2.3.1 Principles of Vector Calculus

- **Vectors**, **opposite vectors**, **zero vector**
- **Length (modulus) of vector**
- **Collinear vectors**, **Coplanar  vectors**
- **Equality  of  vectors**, **Addition  of  vectors**
- Laws of addition of vectors, Laws of multiplication of vector by a number
- **Scalar  product  of vectors**: a product of lengths (modules) of these vectors by cosine of angle between them
- **Angle between non-zero vectors**, **Scalar square**
- A scalar product of two vectors is:
  - positive, if an angle between the vectors is *acute*
  - negative, if an angle between the vectors is *obtuse*
  - A scalar product of two non-zero vectors is equal to zero, if and only if an angle between the vectors is *right*, i.e. these vectors are perpendicular (orthogonal)
- Properties of a scalar product
- **Unit orthogonal vectors**: In any rectangular system of coordinates it is possible to introduce unit two-and-two orthogonal vectors i, j and k, connected with coordinate axes: i for x-axis,  j for y-axis and k for z-axis. Any vector a can be expressed through these vectors by  the only way: a = xi + yj + zk. Another form of  the record is: a = (x, y, z). Here x, y, z – *coordinates of the vector* a in this system of coordinates.
- **Vector product of vectors**, Properties of a vector product
- **Necessary and sufficient condition** of collinearity of vectors
  $$ \begin{vmatrix} x & y \\ u & v \end{vmatrix} = \begin{vmatrix} x & z \\ u & w \end{vmatrix} = \begin{vmatrix} y & z \\ v & w \end{vmatrix} = 0 $$
- Necessary and sufficient condition of coplanarity of vectors
  $$ \begin{vmatrix} x & y & z \\ u & v & w \\ p & q & r \end{vmatrix} = 0 $$

#### 2.3.2 Complex Numbers

- **Complex numbers**: `abscissa` + `ordinate` i
- **Conjugate complex numbers**: a + bi & a - bi
- **Pure imaginary number**
- Multiplication of complex numbers:  
  $(a + bi)(c + di) = (ac - bd) + (ad + bc)i$  
  $(a + bi)(a - bi) = a^2 + b^2$
- Geometric representation of complex numbers, Complex plane, Modulus and argument of a complex number
- Trigonometric form of a complex number
- Operations with complex numbers in the trigonometric form
- Moivre's formula

--------------------------------------------------------------------------------

### 2.4 Inequalities

#### 2.4.1 Mathematical Induction

Assume it's necessary to prove a statement (formula, property etc.), depending on a natural number n. If:

1. this statement is valid for some natural number n0,
2. from validity of this statement at n = k its validity follows at n = k + 1  for any k >= n0,

then this statement is valid for any natural number n >= n0.

#### 2.4.2 Inequalities: Common Information

- **Inequality**: more, less
- **Strict inequality**: $\gt, \lt$
- **Non-strict inequality**: $\geq, \leq$
- Some important inequalities:
  1. $|a + b| \leq |a| + |b|$ (modulus of sum is not more than sum of the modules)
  2. $a + 1/a \geq 2$, a - positive
  3. $\sqrt{ab} \leq \frac{a + b}{2}$ a, b - positive (geometric average is not more than arithmetic average, also for n numbers)

#### 2.4.3 Proving and Solving of Inequalities

- Basic methods of proving of inequalities:
  1. Using of the known or before proved inequality
  2. Estimating of the sign of difference between sides of inequality
  3. Reductio ad absurdum proof
  4. Using of an indefinite inequality
- Solving of inequalities, Equivalent inequalities, Method of intervals
- Double inequality: a < x < b

--------------------------------------------------------------------------------

### 2.5 Sequences and Progressions

#### 2.5.1 Arithmetic and Geometric Progressions

- Numerical sequences, General term of numerical sequence
- **Arithmetic progression**: $a_n = a_1 + (n - 1)d$, $S_n = [2a_1 + (n - 1)d] * n / 2$
- **Geometric progression**: $b_n = b_1 + q^{n - 1}$, $S_n = \frac{b_1(1 - q^n)}{1 - q}$
- Infinitely decreasing geometric progression: |q| < 1

--------------------------------------------------------------------------------

### 2.6 Logarithmic and Exponential Equations

#### 2.6.1 Logarithms

- **Logarithm**
- Properties:
  1. $\log{ab} = \log{a} + \log{b}$
  2. $\log_{b^k}{N^m} = \frac{m}{k} \log_b{N}$
  3. $\log_b{N} = log_a{N} / \log_a{b}$ (the transition module formula)
- Common logarithm: $\lg = \log_{10}$
- Natural logarithm: $\ln = \log_e$

--------------------------------------------------------------------------------

### 2.7 Theory of Combinations

#### 2.7.1 Theory of Combinations

- **Permutations**: permutations of n elements $P_n = 1 * 2 * ... * n = n!$ (factorial)
- **Arrangements**: arrangements of n elements taken m at a time  
  $$ A_n^m = n(n-1)...(n-m+1) = \frac{n!}{(n-m)!} $$
- **Combinations**: combination of n elements taken m at a time  
  $$ C_n^m = \frac{A_n^m}{m!} = \frac{n!}{m! * (n-m)!} $$
- Newton's binomial:  
  $(a + b)^n = a^n + C_n^1 a^{n-1}b + C_n^2 a^{n-2}b^2 + ... + C_n^{n-1} ab^{n-1} + b^n$
- *Pascal's triangle*
- . Properties of binomial coefficients.

--------------------------------------------------------------------------------

Reference: bymath.com

EOF
