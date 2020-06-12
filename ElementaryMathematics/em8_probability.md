em8_probability.md

Elementary Methematics: 8 Probability
================================================================================

A~0f11

8.1 Events
--------------------------------------------------------------------------------

- event, elementary event
- space of elementary events: a set of all elementary events
- certain event: is all space of elementary events
- impossible event (∅): an empty subset of a space of elementary events
- identical events (A=B)
- A involves B (A⊂B): B occured follows A occured
- sum (A∪B)
- product (A∩B)
- difference (A-B)
- complementary events
- mutually exclusive（互斥） events (A∩B = ∅)
- equally likely events

8.2 Definition and Basic Properties of Probability
--------------------------------------------------------------------------------

- axiomatic and classical definitions of probability
- basic properties of probability:
  1. P(∅) = 0
  2. A⊂B⊂E => P(A) <= P(B)
  3. P(A) <= 1
  4. P(A') = 1 - P(A)
  5. P(A∪B) = P(A) + P(B) - P(A∩B)

8.3 Conditional Probability, Independence of Events
--------------------------------------------------------------------------------

- conditional probability
  - $$ P(A|B) = \frac{P(A∩B)}{P(B)} $$
- independent events
  - $$ P(A∩B) = P(A) ⋅ P(B) $$

8.4 Random Variables
--------------------------------------------------------------------------------

- random variable
- discrete and continuous random variables
- independent random variables
- density function of continuous random variable
- distribution function $F(x) = P(X≤x)$
- general properties of distribution function
  1. F(x) is a non-decreasing function
  2. $0 ≤ F(x) ≤ 1$
  3. $\underset{x→-∞}{\lim} F(x) = 0$
  4. $\underset{x→+∞}{\lim} F(x) = 1$

8.5 Characteristics of Random Variables
--------------------------------------------------------------------------------

- mathematical expectation of a discrete random variable
  - $$ M(X) = x_1⋅p_1 + x_2⋅p_2 + x_3⋅p_3 + ... + x_n⋅p_n $$
- properties of mathematical expectation
  1. $M(c⋅X) = c⋅M(X)$
  2. $M(X+Y) = M(X) + M(Y)$
  3. $M(X⋅Y) = M(X) ⋅ M(Y)$ for independent random variables X, Y
- variance（方差）
  - $$ D(X) = M{[X-M(X)]^2} = M(X^2) - [M(X)]^2 $$
- properties of variance
  1. $D(c⋅X) = c^2 ⋅ D(X)$
  2. $D(X+Y) = D(X) + D(Y)$
- root-mean-square deviation（标准差/均方差）
  - $$ σ = √D(X) $$

8.6 Normal (Gaussian) Distribution
--------------------------------------------------------------------------------