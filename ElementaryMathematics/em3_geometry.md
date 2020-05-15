em3_geometry.md

Elementary Methematics: 3 Geometry
================================================================================

A~-1h02

--------------------------------------------------------------------------------

- [3.1 Terminology](#31-terminology)
- [3.2 Angles](#32-angles)
- [3.3 Parallel Straight Lines](#33-parallel-straight-lines)
- [3.4 Polygon](#34-polygon)
- [3.5 Triangle](#35-triangle)
- [3.6 Parallelogram and Trapezoid](#36-parallelogram-and-trapezoid)
- [3.7 Similarity of Plane Figures, Similarity Criteria of Triangles](#37-similarity-of-plane-figures-similarity-criteria-of-triangles)
- [3.8 Geometric Locus, Circle and Circumference](#38-geometric-locus-circle-and-circumference)
- [3.9 Inscribed and Circumscribed Polygons, Regular Polygons](#39-inscribed-and-circumscribed-polygons-regular-polygons)
- [3.10 Areas of Plane Figures](#310-areas-of-plane-figures)
- [3.11 Common Notions](#311-common-notions)
- [3.12 Angles, Projections, Polyhedral Angles](#312-angles-projections-polyhedral-angles)
- [3.13 Polyhedrons, Prism, Parallelepiped, Pyramid](#313-polyhedrons-prism-parallelepiped-pyramid)
- [3.14 Cylinder](#314-cylinder)
- [#### 3.2.6 Cone](#h4-id326-cone-475326-coneh4)
- [#### 3.2.7 Ball (Sphere)](#h4-id327-ball-sphere-475327-ball-sphereh4)
- [#### 3.2.8 Tangent Plane of a Ball, a Cylinder and a Cone](#h4-id328-tangent-plane-of-a-ball-a-cylinder-and-a-cone-475328-tangent-plane-of-a-ball-a-cylinder-and-a-coneh4)
- [#### 3.2.9 Solid Angles](#h4-id329-solid-angles-475329-solid-anglesh4)
- [#### 3.2.10 Regular Polyhedrons](#h4-id3210-regular-polyhedrons-4753210-regular-polyhedronsh4)
- [#### 3.2.11 Symmetry, Symmetry of Plane Figures](#h4-id3211-symmetry-symmetry-of-plane-figures-4753211-symmetry-symmetry-of-plane-figuresh4)
- [#### 3.2.12 Similarity of Bodies](#h4-id3212-similarity-of-bodies-4753212-similarity-of-bodiesh4)
- [#### 3.2.13 Volumes and Areas of Bodies' Surfaces](#h4-id3213-volumes-and-areas-of-bodies-surfaces-4753213-volumes-and-areas-of-bodies-surfacesh4)

Plane Geometry
================================================================================

3.1 Terminology
--------------------------------------------------------------------------------

- proof: a reasoning, determing some property
- theorem (lemma, property, consequence, rule, criteria, proposition, statement): a statement, determing some property and requiring a proof
- axiom（公理）: a statement, determing some property and adopted without a proof
- initial notions: impossible to give sensible definition, like point and straight line
- straight line: infinite
- ray: limited from one side, infinite from the other side
- segment: limited from both sides

3.2 Angles
--------------------------------------------------------------------------------

- 1 degree = 60 minutes = 360 seconds
- radian measure of an angle
- right/direct angle, acute angle, obtuse angle
- mutually perpendicular（互相垂直） lines
- signs of angles: positive if a rotation is executed opposite a clockwise
- supplementary (adjacent) angles（补角）
- vertically opposite (vertical) angles（对顶角）
- bisector（平分线） property: any point of an angle bisector is placed by the same distance from the angle sides

3.3 Parallel Straight Lines
--------------------------------------------------------------------------------

- parallel straight lines
- corresponding angles（同位角）
- alternate interior angles（内错角）, alternate exterior angles（外错角）
- one-sided interior angles（同旁内角）one-sided exterior angles（同旁外角）
- Thales' theorem

3.4 Polygon
--------------------------------------------------------------------------------

- triangle, quadrangle, pentagon, hexagon
- vertices, angles, diagonals（对角线）, sides, perimeter（周长，边界）
- simple polygons (no self-intersections), convex polygon（凸多边形）
- sum of interior angles in a convex polygon = 180(n - 2)

3.5 Triangle
--------------------------------------------------------------------------------

- acute-angled triangle
- right-angled triangle, legs（直角边） and hypotenuse（斜边）
- obtuse-angled triangle
- isosceles triangle（等腰三角形）, lateral sides（腰） and base（底边）
- equilateral triangle（等边三角形）
- scalene triangle（不等边三角形）
- theorems about congruence of triangles（三角形全等）: 3 conditions
- remarkable lines and points of a triangle:
  - altitudes (heights), intersect in orthocenter（垂心）
  - medians（中线）, intersect in the center of gravity（重心）
  - bisectors（角平分线）, intersect in the center of an inscribed circle（内心，内切圆圆心）
  - midperpendiculars（中垂线，垂直平分线） intersect in the center of circumscribed circle (circumcircle)（外心，外接圆圆心）
- Pythagorean theorem（勾股定理，毕达哥拉斯定理）
- relation of sides' legnth for an arbitrary triangle:  
  $c^2 = a^2 + b^2 - 2ab\cos{C}$

3.6 Parallelogram and Trapezoid
--------------------------------------------------------------------------------

- parallelogram（平行四边形）
- rectangle
- rhombus（菱形）
- square
- trapezoid（梯形）
- isosceles trapezoid
- midline of a trapezoid and a triangle

3.7 Similarity of Plane Figures, Similarity Criteria of Triangles
--------------------------------------------------------------------------------

- similarity of plane figures: any corresponding angles equal
- ratio of similarity
- similarity criteria of triangles: 3 conditions

3.8 Geometric Locus, Circle and Circumference
--------------------------------------------------------------------------------

- geometrical locus (simply locus)（几何轨迹？点集？） is a totality of all points satisfying a certain given conditions
- circumference（圆周） is a locus, that is a totality of all points, equally removed from its center
  - radius
  - circle: a part of a plane inside of a circumference
  - arc
  - secant (traversal)（割线？）: a straight line going through two points of a circumference
  - chord（弦）
  - diameter
- tangent line（切线）, a point of tangency（切点）
- segment of a circle（圆缺？弓形？）, sector of a circle（扇形）
- angles in a circle:
  - central angle
  - inscribed angle
  - circumscribed angle
- radian measure of angles: a radian is a central angle, whose arc’s length is equal to its radius
- ratio of circumference length and diameter: π
- Huygens' formula：length of an arc $p \approxeq 2l + (2l - L) / 3$

3.9 Inscribed and Circumscribed Polygons, Regular Polygons
--------------------------------------------------------------------------------

- inscribed polygon (vertices are placed on a circumference), circumcircle around a polygon
- circumscribed polygon (sides are tangents to circumference), incircle into a polygon
- radius of an incircle into a triangle:  
  $$ r = \sqrt{(p-a)(p-b)(p-c) / p}, p = (a+b+c) / 2 $$
- radius of a circumcircle around a triangle:
  $$ R = \frac{abc}{4 \sqrt{p (p-a)(p-b)(p-c)}} $$
- regular polygon (with equal sides and angles): hexagon, octagon...
- apothem（边心距）

3.10 Areas of Plane Figures
--------------------------------------------------------------------------------

- areas of square, rectangle, rhombus, parallelogram, trapezoid, quadrangle
- right-angled triangle, isosceles triangle, equilateral triangle, arbitrary triangle
- regular polygon
- circle, sector, segment of a circle

Solid Geometry
================================================================================

3.11 Common Notions
--------------------------------------------------------------------------------

- stereometry（立体几何）
- main axiom of stereometry: through any 3 points, not placed on the same straight line, it is possible to draw 1 and only 1 plane
- through  3 points on same line, drawing innumerable set of planes, forming a pencil of planes, the line is axis of pencil
- crossing straight lines: able to draw a plane through the two lines
- parallel planes
- parallel straight line and plane.

3.12 Angles, Projections, Polyhedral Angles
--------------------------------------------------------------------------------

- angle between two crossing straight lines
- line perpendicular to a plane
- projection of a point and a segment to a plane
- dihedral angle（二面角）, linear angle of a dihedral angle
- polyhedral angle（多面角）
- parallelism and perpendicularity of straight lines and planes

3.13 Polyhedrons, Prism, Parallelepiped, Pyramid
--------------------------------------------------------------------------------

- polyhedron（多面体）
- prism（棱柱）: depending on a form of polygon in a base, prism can be: triangular, quadrangular, pentagonal, hexagonal...
- right prism（直棱柱）, oblique prism（斜棱柱）
- parallelepiped（平行六面体）
- right parallelepiped: 4 lateral faces are rectangles
- right-angled parallelepiped: all 6 faces are rectangles
- cube: all faces are squares
- pyramid（棱锥）: tetrahedron（四面体）, pentahedron（五面体）...
- truncated pyramid

3.14 Cylinder
--------------------------------------------------------------------------------

- cylindrical surface, directrix（准线） and generatrices（母线） of a cylindrical surface
- cylinder: a body limited by cylindrical surface (with a closed directrix) and 2 parallel planes
- right cylinder (generatrices are perpendicular to its base), oblique cylinder
- circular cylinder (base is circle), round cylinder (both right and circular)
- prism as a particular case of a cylinder. Cylindrical sections.

#### 3.2.6 Cone
--------------------------------------------------------------------------------

#### 3.2.7 Ball (Sphere)
--------------------------------------------------------------------------------

#### 3.2.8 Tangent Plane of a Ball, a Cylinder and a Cone
--------------------------------------------------------------------------------

#### 3.2.9 Solid Angles
--------------------------------------------------------------------------------

#### 3.2.10 Regular Polyhedrons
--------------------------------------------------------------------------------

#### 3.2.11 Symmetry, Symmetry of Plane Figures
--------------------------------------------------------------------------------

#### 3.2.12 Similarity of Bodies
--------------------------------------------------------------------------------

#### 3.2.13 Volumes and Areas of Bodies' Surfaces
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------

ref: bymath.com

EOF
