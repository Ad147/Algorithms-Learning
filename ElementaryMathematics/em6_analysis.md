em6_analysis.md

Elementary Methematics: 6 Principles of Analysis
================================================================================

A~0e30

--------------------------------------------------------------------------------

- [6.1 Sequences, Limits of Numerical Sequences](#61-sequences-limits-of-numerical-sequences)
- [6.2 Limits of Functions](#62-limits-of-functions)
- [6.3 Derivative, Geometrical and Mechanical Meaning of Derivative](#63-derivative-geometrical-and-mechanical-meaning-of-derivative)
- [6.4 Differential and Its Relation with Derivative](#64-differential-and-its-relation-with-derivative)
- [6.5 Basic Properties of Derivatives and Differentials](#65-basic-properties-of-derivatives-and-differentials)
- [6.6 Derivatives of Elementary Functions](#66-derivatives-of-elementary-functions)
- [6.7 De L'Hospital’s Rule](#67-de-lhospitals-rule)
- [6.8 Application of Derivative in Investigation of Functions](#68-application-of-derivative-in-investigation-of-functions)
- [6.9 Convexity, Concavity and Inflexion Points of a Function](#69-convexity-concavity-and-inflexion-points-of-a-function)
- [6.10 Primitive, Indefinite Integral](#610-primitive-indefinite-integral)

Limits
================================================================================

6.1 Sequences, Limits of Numerical Sequences
--------------------------------------------------------------------------------

- numerical sequences（数列）, general term（通项）, general term formula（通项公式）
- limit of numerical sequence
  - a number a is called a limit of a numerical sequence {u_n}:
  - $$ \underset{n \rightarrow \infty}{\lim u_n}  = a $$
  - if and only if for any $\epsilon > 0$ one can find such a number $N = N(\epsilon)$, depending on $\epsilon$, that $|u_n - a| < \epsilon$ at $n > N$
- convergent（收敛） sequence, divergent（发散） sequence
- bounded sequence, monotone sequence
- Weierstrass's theorem: each monotone and bounded sequence has a limit
- basic properties of limits (6)
- some remarkable limits
  - $$ \underset{n \rightarrow \infty}{\lim} \left( 1 + \frac{1}{n} \right)^n = e $$
  - $$ \underset{n \rightarrow \infty}{\lim} \frac{a^n}{n!} = 0, a > 0 $$
  - $$ \underset{n \rightarrow \infty}{\lim} \sqrt[n]{a} = 1, a > 0 $$
  - $$ \underset{n \rightarrow \infty}{\lim} \sqrt[n]{n} = 1 $$
  - $$ \underset{n \rightarrow \infty}{\lim} \frac{\sin 1/n}{1/n} = 1, a > 0 $$
  - $$ \underset{n \rightarrow \infty}{\lim} \frac{\tan 1/n}{1/n} = 1, a > 0 $$

6.2 Limits of Functions
--------------------------------------------------------------------------------

- limit of a function
  - a number L is called a limit of a function y = f(x) as x tends a:
  - $$ \underset{x \rightarrow a}{\lim f(x)}  = L $$
  - if and only if for any $\epsilon > 0$ one can find such a positive number $\delta = \delta(\epsilon)$, depending on $\epsilon$, that $|x - a| < \delta$ implies that $|f(x) - L| < \epsilon$
- some remarkable limits
  - $$ \underset{x \rightarrow 0}{\lim} \frac{\sin x}{x} = 1 $$
  - $$ \underset{x \rightarrow 0}{lim} \frac{\tan x}{x} = 1 $$
  - $$ \underset{x \rightarrow 0}{lim} (1+x)^{1/x} = e $$
- infinitesimal（无穷小） and infinite（无穷大） values
- finite limit, infinite limit
- infinity ($\infty$) does not mean some number, but increase unboundly

Derivative
================================================================================

6.3 Derivative, Geometrical and Mechanical Meaning of Derivative
--------------------------------------------------------------------------------

- derivative（导数） of a function y = f(x) at a point x_0:
  - $$ \underset{\Delta x \rightarrow 0}{\lim} \frac{f(x_0 + \Delta x) - f(x_0)}{\Delta x} $$
  - (limit of function increment / argument increment)
  - if limit exists, f(x) is a differentiable function（可微函数） at a point x_0, marked as
  - $$ f'(x_0) = \frac{df}{dx} (x_0) = \frac{df(x)}{dx} |_x = x_0 $$
- geometrical meaning of derivative: a derivative of a function at a point is a slope（斜率） of a tangent of this function graph at this point
- tangent equation:
  - $$ y = f(x_0) + f'(x_0) \cdot (x - x_0) $$
- mechanical meaning of derivative:
  - a derivative of a coordinate with respect to time is a instantaneous velocity
  - an acceleration is a derivative of velocity with respective to time

6.4 Differential and Its Relation with Derivative
--------------------------------------------------------------------------------

- differential（微分） of a function: is a product of a derivative and an increment of argument:
  - $$ df = f'(x_0) \cdot \Delta x $$
- geometrical meaning of a differential

6.5 Basic Properties of Derivatives and Differentials
--------------------------------------------------------------------------------

- if $u(x) ≡ const$, then $u'(x) ≡ 0, du≡ 0$
- if $u(x), v(x)$ are differentiable functions at a point x_0, then:
  - $$ (c u)' = c u', d(c u) = c du $$
  - $$ (u ± v)' = u' ± v', d(u ± v) = du ± dv $$
  - $$ (u v)' = u' v + u v', d(u v) = v du + u dv $$
  - $$ (u/v)' = \frac{u' v - u v'}{v^2}, d(u/v) = \frac{u dv - v du}{v^2}, (v(x_0) != 0) $$
- derivative of a composite function (argument of which is also a function: $h(x) = g(f(x))$)
  - if a function f has a derivative at a point x_0, and a function g has a derivative at a point f(x_0), then a composite function h has also a derivative at a point x_0, calculated by the formula:
  - $$ h'(x_0) = g'(f(x_0)) · f'(x_0) $$

6.6 Derivatives of Elementary Functions
--------------------------------------------------------------------------------

$$ (x^n)' = n x^{n-1}, (n: a natural number) $$

$$ (\sin x)' = \cos x ; (\cos x)' = -\sin x $$

$$ (\tan x)' = 1 / \cos^2 x ; (\cot x)' = -1 / \sin^2 x $$

$$ (\arcsin x)' = 1 / \sqrt{1-x^2} ; (\arccos)' = -1 / \sqrt{1-x^2} $$

$$ (\arctan x)' = 1 / (1+x^2) ; (\arcctg)' = -1 / (1+x^2) $$

$$ (a^x)' = a^x · \ln a ; (\log_a x)' = 1 / (x·\ln a) $$

$$ (x^x)' = x^x · (\ln x + 1) $$

6.7 De L'Hospital’s Rule
--------------------------------------------------------------------------------

- L'Hospital's rule:
  - let at $x → a$ for functions f(x) and g(x), differentiable in some neighborhood of point a, the conditions are executed:
    1. either $f(x) → 0, g(x) → 0$, or $f(x) → ∞, g(x) → ∞$
    2. the limit $\underset{x→a}{\lim} \frac{f'(x)}{g'(x)}$ exists,
  - then
  - $$ \underset{x→a}{\lim} \frac{f(x)}{g(x)} = \underset{x→a}{\lim} \frac{f'(x)}{g'(x)} $$
- as mathematicians say, de L'Hospital's rule permits to get rid of indeterminacies of types 0/0 and ∞/∞
- indeterminacies of other types: $∞-∞, ∞•0, 0^0, ∞^0, 1^∞$, can be transformed to either 0/0 or ∞/∞:
  1. ∞-∞ reduced to 0/0:  
     $$ f(x) - g(x) = \frac{1/g(x) - 1/f(x)}{1/[f(x)•g(x)]} $$
  2. ∞•0 reduced to 0/0 or ∞/∞:  
     $$ f(x) • g(x) = \frac{f(x)}{1/g(x)} = \frac{g(x)}{1/f(x)} $$
  3. rest are reduced to the first ones by the logarithmic transformation:  
     $$ \log f(x)^{g(x)} = g(x) • \log f(x) $$
- if after using L'Hospital's rule, 0/0 or ∞/∞ remain, repeat

6.8 Application of Derivative in Investigation of Functions
--------------------------------------------------------------------------------

- if a function is differentiable at some point, then it is a continuous function at this point; contrary is invalid
- sufficient conditions of functions monotony:
  - if f'(x) > 0 at every point of an interval (a, b), then a function f(x) increases within this interval
  - < 0 => decreases
- Darboux's theorem:
  -  points, at which a derivative of a function is equal to 0 or does not exist, divide a function domain for such intervals that within each of them a derivative saves a constant sign
- critical points:
  - a domain interior points, in which a derivative of a function is equal to zero or does not exist
- extreme（极值） (minimum（极小值）, maximum（极大值）), points of extreme
- necessary condition of extreme:
  - f'(x_0) = 0 (if derivative exists)
- sufficient conditions of extreme:
  - a derivative changes its sign from plus to minus => point of maximum
  - from minus to plus => point of minimum
- plan of function investigation: to draw a graph of a function it is necessary:
    1. to find a domain and a codomain of a function
    2. to ascertain if the function is even or odd
    3. to determine if the function is periodic or not
    4. to find zeros of the function and its values at x = 0
    5. to find intervals of a sign constancy,
    6. to find intervals of monotony
    7. to find points of extreme and values of a function in these points
    8. to analyze the behavior of a function near “special” points and at a great odulus of x

6.9 Convexity, Concavity and Inflexion Points of a Function
--------------------------------------------------------------------------------

- the second derivative f"(x)
- convex and concave function:
  - convex: in an interval (a, b), function graph is placed lower than a tangent line, going through any point (x_0, f(x_0))
  - concave: higher than tangent
- sufficient condition of concavity/convexity of a function:
  - let a function be twice defferentiable (i.e. it has the second derivative) in an interval (a, b), then:
  - if f"(x) > 0 for x ∈（a, b) => concave
  - < 0 => convex
- inflexion point:
  - at which a function changes a convexity to a concavity or vice versa
  - f"(x_0) = 0

Integral
================================================================================

6.10 Primitive, Indefinite Integral
--------------------------------------------------------------------------------