em9_analyticgeometry.md

Elementary Methematics: 9 Analytic Geometry
================================================================================

A~0f14

Analytic Geometry in a Plane
================================================================================

9.11 Transformations of Coordinates
--------------------------------------------------------------------------------

- translation of axes
  - axes move parallelly, O(0, 0) -> O'(a, b)
  - P(x, y) -> P(x', y'):
    - $$ x' = x - a $$
    - $$ y' = y - b $$
- turning around origin of coordinates
  - turn coor system XOY by ϕ
  - P(x, y) -> P(x', y'):
    - $$ x' = x ⋅ \cos ϕ + y ⋅ \sin ϕ $$
    - $$ y' = -x ⋅ \sin ϕ + y ⋅ \cos ϕ $$
- central symmetry (ϕ = π):
    - $$ x' = -x, y' = -y $$
- homothetic transformation（位似变换） with a center O(a, b) and a coefficient k != 0:
  - $$ x' - a = k (x-a) $$
  - $$ y' - b = k (y-b) $$
- affine transformation（仿射变换）:
  - $$ x' = ax + by + c $$
  - $$ y' = dx + ey + f $$
  - where $\begin{vmatrix} a & b \\ d & e \end{vmatrix} \neq 0$
- an affine transformation transfers  
  straight lines to straight lines,  
  intersecting lines to intersecting lines,  
  parallel straight lines to parallel straight lines;  
  all above mentioned transformations of coordinates are affine transformations

9.12 Straight Line
--------------------------------------------------------------------------------

- general equation of straight line:
  - $$ Ax + By + C = 0 $$
  - where A, B are aoordinates of normal vector of the straight line
- at B != 0, receive an equation of straight line with slope:
  - $$ y = -A/B x - C/B = mx + k $$
  - line through (x_0, y_0) and not parallel to OY:
  - $$ y - y_0 = m(x - x_0) $$
  - where m is a slope
- at A, B, C !=0, receive an equation of straight line in segments on axes:
  - $$ x/a + y/b = 1 $$
  - where a=-C/A, b=-C/B
  - this line through (a, 0) and (0, b)
- equation of straight line going through two different points:
  - $$ \frac{y-y_1}{y_2-y_1} = \frac{x-x_1}{x_2-x_1} $$
  - at x_1 != x_2, y_1 != y_2
- parametric（参数） equation of straight line:
  - going through (x_0, y_0) and parallel to vector (a, b)
  - $$ x = x_0 + at $$
  - $$ y = y_0 + bt $$
- parallelism condition of straight lines:
  - for Ax+By+c=0 and Dx+Ey+F=0: $AE-BD=0$
  - for y=mx+k and y=px+q: $m=p$

Perpendicularity condition of straight lines.

Distance between two points.

Distance from point to straight line.

Distance between parallel straight lines.

Angle between straight lines.

9.13 Circle

9.14 Ellipse

9.15 Hyperbola

9.16 Parabola

Analytic Geometry in a Space
================================================================================

9.21 Transformations of Coordinates

9.22 Plane

9.23 Straight Line

9.24 Sphere
