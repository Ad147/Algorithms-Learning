em4_trigonometry.md

Elementary Methematics: 4 Trigonometry
================================================================================

A~0e19

--------------------------------------------------------------------------------

- [4.1 Radian and Degree Measures of Angles](#41-radian-and-degree-measures-of-angles)
- [4.2 Trigonometric Functions of an Acute Angle](#42-trigonometric-functions-of-an-acute-angle)
- [4.3 Relations between Trigonometric Functions of the Same Angle](#43-relations-between-trigonometric-functions-of-the-same-angle)
- [4.4 Trigonomatric Functions of Any Angle](#44-trigonomatric-functions-of-any-angle)
- [4.5 Reduction Formulas](#45-reduction-formulas)
- [4.6 Addition and Subtraction Formulas](#46-addition-and-subtraction-formulas)
- [4.7 Double-, Triple-, and Half-Angle Formulas](#47-double--triple--and-half-angle-formulas)
- [4.8 Transforming of Trigonomatric Expressions to Product](#48-transforming-of-trigonomatric-expressions-to-product)
- [4.9 Some Important Correlations](#49-some-important-correlations)
- [4.10 Basic Relations between Elements of Triangle](#410-basic-relations-between-elements-of-triangle)
- [4.11 Solving of Oblique Triangles](#411-solving-of-oblique-triangles)

Trigonometric Transformations
================================================================================

4.1 Radian and Degree Measures of Angles
--------------------------------------------------------------------------------

- degree measure of angles: 1 °/deg = 1/360 complete revolution = 60 '/min = 3600 "/sec
- radian measure of angles: a ratio of a length of an arc drawn by an arbitrary radius and concluded between sides of this angle to the arc radius
- 1 rad = 360deg / 2pi ~= 57.2958deg ~= 57deg17'45"  
  1 deg = 2pi / 360deg ~= 0.017453rad
- table of degree and radian measures for some most used angles:

| angles in deg | 360 | 180 | 90   | 60   | 45   | 30   |
| ------------- | --- | --- | ---- | ---- | ---- | ---- |
| angles in rad | 2pi | pi  | pi/2 | pi/3 | pi/4 | pi/6 |

4.2 Trigonometric Functions of an Acute Angle
--------------------------------------------------------------------------------

- sine: opposite leg / hypotenuse
- cosine: adjacent leg / hypotenuse
- tangent: opposite leg / adjacent leg
- cotangent: adj / opp
- secant: hyp / adj
- cosecant: hpy / opp
- exact values of trigonometric functions for some most used acute angles:

| A/deg | sinA | cosA | tanA | cotA | secA | cosecA |
| ----- | ---- | ---- | ---- | ---- | ---- | ------ |
| 0     | 0    | 1    | 0    | inf  | 1    | inf    |
| 30    | 1/2  | √3/2 | 1/√3 | √3   | 2/√3 | 2      |
| 45    | √2/2 | √2/2 | 1    | 1    | √2   | √2     |
| 60    | √3/2 | 1/2  | √3   | 1/√3 | 2    | 2/√3   |
| 90    | 1    | 0    | inf  | 0    | inf  | 1      |

4.3 Relations between Trigonometric Functions of the Same Angle
--------------------------------------------------------------------------------

$$ \sin^2\alpha + \cos^2\alpha = 1 ; \tan\alpha \cdot \cot\alpha = 1 $$
$$ \tan\alpha = \frac{\sin\alpha}{\cos\alpha} ; \cot\alpha = \frac{\cos\alpha}{\sin\alpha} $$
$$ \sin\alpha \cdot \cosec\alpha = 1 ; \cos\alpha \cdot \sec\alpha = 1 $$
$$ \sec^2\alpha = 1 + \tan^2\alpha ; \cosec^2\alpha = 1 + \cot^2\alpha $$
$$ cos^2\alpha = \frac{1}{1 + \tan^2\alpha} = \frac{\cot^2\alpha}{1 + \cot^2\alpha} $$
$$ \sin^2\alpha = \frac{1}{1 + \cot^2\alpha} = \frac{\tan^2\alpha}{1 + \tan^2\alpha} $$

4.4 Trigonomatric Functions of Any Angle
--------------------------------------------------------------------------------

- unit circle（单位圆）
- negative angle (clockwise), positive angle
- quarters of a unit circle
- sine line is a vertical diameter, cosine line is a horizontal diameter
- signs of sine in quarters: ++--; signs of cosine in quarters: +--+
- tangent and cotangent lines: tangents of unit circle
- signs of tangent and cotangent in quarters: +-+-
- secant and cosecant are determined as reciprocal（倒数） values of cosine and sine correspondingly

4.5 Reduction Formulas
--------------------------------------------------------------------------------

|        | sin   | cos   | tan   | cot   |
| -----: | ----- | ----- | ----- | ----- |
|     -A | -sinA | +cosA | -tanA | -cotA |
|   90-A | +cosA | +sinA | +cotA | +tanA |
|   90+A | +cosA | -sinA | -cotA | -tanA |
|  180-A | +sinA | -cosA | -tanA | -cotA |
|  180+A | -sinA | -cosA | +tanA | +cotA |
|  270-A | -cosA | -sinA | +cotA | +tanA |
|  270+A | -cosA | +sinA | -cotA | -tanA |
| 360k-A | -sinA | +cosA | -tanA | -cotA |
| 360k+A | +sinA | +cosA | +tanA | +cotA |

4.6 Addition and Subtraction Formulas
--------------------------------------------------------------------------------

$$ \sin(\alpha + \beta) = \sin\alpha\cos\beta + \cos\alpha\sin\beta $$
$$ \sin(\alpha - \beta) = \sin\alpha\cos\beta - \cos\alpha\sin\beta $$
$$ \cos(\alpha + \beta) = \cos\alpha\cos\beta - \sin\alpha\sin\beta $$
$$ \cos(\alpha - \beta) = \cos\alpha\cos\beta + \sin\alpha\sin\beta $$
$$ \tan(\alpha + \beta) = \frac{\tan\alpha + \tan\beta}{1 - \tan\alpha\tan\beta} $$
$$ \tan(\alpha - \beta) = \frac{\tan\alpha - \tan\beta}{1 - \tan\alpha\tan\beta} $$
$$ \cot(\alpha + \beta) = \frac{1 - \cot\alpha\cot\beta}{\cot\alpha + \cot\beta} $$
$$ \cot(\alpha - \beta) = \frac{1 + \cot\alpha\cot\beta}{\cot\alpha - \cot\beta} $$

4.7 Double-, Triple-, and Half-Angle Formulas
--------------------------------------------------------------------------------

$$ \sin2\alpha = 2\sin\alpha\cdot\cos\alpha $$
$$ \cos2\alpha = \cos^2\alpha - \sin^2\alpha = 1 - 2\sin^2\alpha = 2\cos^2\alpha - 1 $$
$$ \tan2\alpha = \frac{2\tan\alpha}{1 - \tan^2\alpha} ; \cot2\alpha = \frac{\cot^2\alpha - 1}{2\cot\alpha}$$
$$ \sin3\alpha = 3\sin\alpha - 4\sin^3\alpha = 3\cos^2\alpha\cdot\sin\alpha - \sin^3\alpha $$
$$ \cos3\alpha = 4\cos^3\alpha - 3\cos\alpha = \cos^3\alpha - 3\cos\alpha\cdot\sin^2\alpha $$
$$ \tan3\alpha = \frac{3\tan\alpha - \tan^3\alpha}{1 - 3\tan^2\alpha} ; \cot3\alpha = \frac{\cot^3\alpha - 3\cot\alpha}{3\cot^2\alpha - 1} $$
$$ \sin\frac{\alpha}{2} = \pm\sqrt{\frac{1 - \cos\alpha}{2}} ; \cos\frac{\alpha}{2} = \pm\sqrt{\frac{1 + \cos\alpha}{2}} $$
$$ \tan\frac{\alpha}{2} = \pm\sqrt{\frac{1 - \cos\alpha}{1 + \cos\alpha}} = \frac{\sin\alpha}{1 + \cos\alpha} = \frac{1 - \cos\alpha}{\sin\alpha} $$
$$ \cot\frac{\alpha}{2} = \pm\sqrt{\frac{1 + \cos\alpha}{1 - \cos\alpha}} = \frac{\sin\alpha}{1 - \cos\alpha} = \frac{1 + \cos\alpha}{\sin\alpha} $$

Signs before roots depend on the quarter.

4.8 Transforming of Trigonomatric Expressions to Product
--------------------------------------------------------------------------------

$$ \sin\alpha + \sin\beta = 2\sin\frac{\alpha + \beta}{2} \cdot \cos\frac{\alpha - \beta}{2} $$
$$ \sin\alpha - \sin\beta = 2\cos\frac{\alpha + \beta}{2} \cdot \sin\frac{\alpha - \beta}{2} $$
$$ \cos\alpha + \cos\beta = 2\cos\frac{\alpha + \beta}{2} \cdot \cos\frac{\alpha - \beta}{2} $$
$$ \cos\alpha - \cos\beta = 2\sin\frac{\alpha + \beta}{2} \cdot \sin\frac{\alpha - \beta}{2} $$
$$ \tan\alpha \pm \tan\beta = \frac{\sin(\alpha \pm \beta)}{\cos\alpha \cdot \cos\beta} $$
$$ \cot\alpha \pm \cot\beta = \frac{\sin(\alpha \pm \beta)}{\sin\alpha \cdot \sin\beta} $$
$$ \cos\alpha + \sin\alpha = \sqrt2 \cdot \cos(45\degree - \alpha) $$
$$ \cos\alpha - \sin\alpha = \sqrt2 \cdot \sin(45\degree - \alpha) $$
$$ \tan\alpha + \cot\beta = \frac{\cos(\alpha - \beta)}{\cos\alpha \cdot \sin\beta} $$
$$ \tan\alpha - \cot\beta = -\frac{\cos(\alpha + \beta)}{\cos\alpha \cdot \sin\beta} $$
$$ 1 + \cos\alpha = 2\cos^2\alpha/2 ; 1 - \cos\alpha = 2\sin^2\alpha/2 $$
$$ 1 + \sin\alpha = 2\cos^2(45\degree - \alpha/2) ; 1 - \sin\alpha = 2\sin^2(45\degree - \alpha/2) $$
$$ 1 + \tan\alpha\tan\beta = \frac{\cos(\alpha - \beta)}{\cos\alpha \cdot \cos\beta} $$
$$ 1 - \tan\alpha\tan\beta = \frac{\cos(\alpha + \beta)}{\cos\alpha \cdot \cos\beta} $$
$$ \cot\alpha\cot\beta + 1 = \frac{\cos(\alpha - \beta)}{\sin\alpha \cdot \sin\beta} $$
$$ \cot\alpha\cot\beta - 1 = \frac{\cos(\alpha + \beta)}{\sin\alpha \cdot \sin\beta} $$

4.9 Some Important Correlations
--------------------------------------------------------------------------------

- transforming product to sum

$$ \sin\alpha \cdot \sin\beta = \frac{1}{2} [\cos(\alpha - \beta) - \cos(\alpha + \beta)]$$
$$ \cos\alpha \cdot \cos\beta = \frac{1}{2} [\cos(\alpha - \beta) + \cos(\alpha + \beta)]$$
$$ \sin\alpha \cdot \cos\beta = \frac{1}{2} [\sin(\alpha - \beta) + \sin(\alpha + \beta)]$$

- universal substitution

$$ \sin\alpha = \frac{2\tan\alpha/2}{1 + \tan^2\alpha/2} $$
$$ \cos\alpha = \frac{1 - \tan^2\alpha/2}{1 + \tan^2\alpha/2} $$
$$ \sin\alpha = \frac{2\tan\alpha/2}{1 - \tan^2\alpha/2} $$

- quadruple-angle formulas（四倍角公式）

$$ \cos4\alpha = \cos^4\alpha - 6\cos^2\alpha \cdot \sin^2\alpha + \sin^4\alpha $$
$$ \sin4\alpha = 4\cos^3\alpha \cdot \sin\alpha - 4\cos\alpha \cdot \sin^3\alpha $$

4.10 Basic Relations between Elements of Triangle
--------------------------------------------------------------------------------

- law of cosines

$$ a^2 = b^2 + c^2 - 2bc \cdot \cos A ; \cos A = \frac{b^2 + c^2 - a^2}{2bc} $$

- law of sines

$$ \frac{a}{\sin A} = \frac{b}{\sin B} = \frac{c}{\sin C} = 2R $$

- law of tangents

$$ \frac{a + b}{a - b} = \frac{\tan\frac{A + B}{2}}{\tan\frac{A - B}{2}} = \frac{\cot\frac{C}{2}}{\tan\frac{A - B}{2}} $$

- area formulas

$$ S = \frac{bc \cdot \sin A}{2} = \frac{b^2 \cdot \sin A \cdot \sin C}{2\sin B} = \frac{h^2 \cdot \sin B}{2\sin A \cdot \sin C} $$
$$ S = \sqrt{p(p-a)(p-b)(p-c)} (Heron's  formula) $$
$$ S = r^2 \cdot \cot\frac{A}{2} \cdot \cot\frac{B}{2} \cdot \cot\frac{C}{2} = p^2 \cdot \tan\frac{A}{2} \cdot \tan\frac{B}{2} \cdot \tan\frac{C}{2} $$
$$ S = p(p-a) \cdot \tan\frac{A}{2} $$

- radii of circumscribed and inscribed circles

$$ R = \frac{a}{2\sin A} = \frac{abc}{4S} = \frac{p}{4\cos\frac{A}{2} \cdot \cos\frac{B}{2} \cdot \cos\frac{C}{2}} $$
$$ r = \frac{S}{p} = (p-a) \cdot \tan\frac{A}{2} = \frac{a \cdot \sin B/2 \cdot \sin C/2}{\cos A/2} = 4R\sin\frac{A}{2} \cdot \sin\frac{B}{2} \cdot \sin\frac{C}{2} \cdot $$

Designations: a, b, c – sides; A, B, C – angles of triangle; p = (a + b + c) / 2  - a half-perimeter; h – a height; S – an area; R, r – radii of circumscribed and inscribed circles correspondingly.

4.11 Solving of Oblique Triangles
--------------------------------------------------------------------------------



Trigonometric Equations
================================================================================

Trigonometric Inequalities
================================================================================