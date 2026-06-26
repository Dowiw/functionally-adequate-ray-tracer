# The Dot Product: $\mathbf{A} \cdot \mathbf{B}$

## 1. Definition
For two 3D vectors $\mathbf{A} = (A_x, A_y, A_z)$ and $\mathbf{B} = (B_x, B_y, B_z)$:

* **Algebraic Definition**:
  $$\mathbf{A} \cdot \mathbf{B} = A_x B_x + A_y B_y + A_z B_z$$
  *(Multiply matching components and sum the results to get a single scalar).*

* **Geometric Definition**:
  $$\mathbf{A} \cdot \mathbf{B} = \|\mathbf{A}\| \|\mathbf{B}\| \cos(\theta)$$

  where 
  $\|\mathbf{A}\|$ and $\|\mathbf{B}\|$ 
  are the lengths of the vectors, and $\theta$ is the angle between them.
  *(If both vectors are normalized, i.e., 
  $\|\mathbf{A}\| = \|\mathbf{B}\| = 1$,
  then $\mathbf{A} \cdot \mathbf{B} = \cos(\theta)$).*

## 2. Key Uses in Ray Tracing

1. **Direction / Angle Comparison**:
   * **$\mathbf{A} \cdot \mathbf{B} > 0$**: 
   The vectors point in the same general direction ($\theta < 90^\circ$).

   * **$\mathbf{A} \cdot \mathbf{B} = 0$**: The vectors are perpendicular/orthogonal ($\theta = 90^\circ$).

   * **$\mathbf{A} \cdot \mathbf{B} < 0$**: The vectors point in opposite general directions ($\theta > 90^\circ$).

2. **Vector Length Squared**:
   * $$\mathbf{A} \cdot \mathbf{A} = \|\mathbf{A}\|^2$$
   * Used to compute distance relations without performing a square root operation, which is computationally expensive.

3. **Vector Projection**:
   * If $\mathbf{D}$ is a normalized direction vector, then $\mathbf{V} \cdot \mathbf{D}$ gives the length of the projection of vector $\mathbf{V}$ onto the direction of $\mathbf{D}$.

---

# Ray-Sphere Intersection

## 1. The Equations

* **Ray Equation**: Any point $\mathbf{P}(t)$ along a ray at a parameter $t \ge 0$ is defined by:
  $$\mathbf{P}(t) = \mathbf{O} + t\mathbf{D}$$
  where:
  * $\mathbf{O}$ is the origin of the ray (a 3D point).
  * $\mathbf{D}$ is the direction vector of the ray.
  * $t$ is the distance along the ray.

  What it means: As time passes for a ray, the resulting position is the origin coordinates summed with time multiplied by the direction of the ray. Makes sense.


* **Sphere Equation**: A sphere centered at point $\mathbf{C}$ with radius $r$ is defined as the set of points $\mathbf{P}$ satisfying:
  $$(\mathbf{P} - \mathbf{C}) \cdot (\mathbf{P} - \mathbf{C}) = r^2$$
  *(The dot product of a vector with itself gives its squared length).*

  What it means: The 3D distance formula (Pythagorean theorem) squared. It states that any point $\mathbf{P}$ on the surface of the sphere is at distance $r$ from the center $\mathbf{C}$. Squaring both sides of the distance equation $\|\mathbf{P} - \mathbf{C}\| = r$ allows us to use the dot product of $(\mathbf{P} - \mathbf{C})$ with itself, avoiding a computationally expensive square root.

  How is it derived:
  1. Geometrically, a point $\mathbf{P} = (x, y, z)$ lies on a sphere with center $\mathbf{C} = (x_c, y_c, z_c)$ and radius $r$ if the Euclidean distance between them is exactly $r$:
     $$\sqrt{(x - x_c)^2 + (y - y_c)^2 + (z - z_c)^2} = r$$
  2. Square both sides to eliminate the square root:
     $$(x - x_c)^2 + (y - y_c)^2 + (z - z_c)^2 = r^2$$
  3. Notice that the vector pointing from the center $\mathbf{C}$ to the point $\mathbf{P}$ is:
     $$\mathbf{P} - \mathbf{C} = (x - x_c, \ y - y_c, \ z - z_c)$$
  4. The dot product of this vector with itself is:
     $$(\mathbf{P} - \mathbf{C}) \cdot (\mathbf{P} - \mathbf{C}) = (x - x_c)^2 + (y - y_c)^2 + (z - z_c)^2$$
  5. Substituting this back yields the vector form of the sphere equation:
     $$(\mathbf{P} - \mathbf{C}) \cdot (\mathbf{P} - \mathbf{C}) = r^2$$


---

## 2. Combining Into a Quadratic Equation

To find the intersection, substitute the ray equation into the sphere equation:
$$((\mathbf{O} + t\mathbf{D}) - \mathbf{C}) \cdot ((\mathbf{O} + t\mathbf{D}) - \mathbf{C}) = r^2$$

Let $\mathbf{V} = \mathbf{O} - \mathbf{C}$ be the vector from the sphere's center to the ray's origin. Substituting this in:
$$(t\mathbf{D} + \mathbf{V}) \cdot (t\mathbf{D} + \mathbf{V}) = r^2$$

Expanding the dot product using algebraic distribution:
$$t^2(\mathbf{D} \cdot \mathbf{D}) + 2t(\mathbf{D} \cdot \mathbf{V}) + (\mathbf{V} \cdot \mathbf{V}) - r^2 = 0$$

This is a standard quadratic equation in terms of $t$:
$$a t^2 + b t + c = 0$$

where:
* $a = \mathbf{D} \cdot \mathbf{D}$ *(if $\mathbf{D}$ is normalized, $a = 1$)*
* $b = 2(\mathbf{D} \cdot \mathbf{V})$
* $c = \mathbf{V} \cdot \mathbf{V} - r^2$

---

## 3. The Role of the Discriminant: $\Delta = b^2 - 4ac$

The discriminant determines the number of intersection points:

1. **$\Delta < 0$ (Negative)**:
   The ray misses the sphere entirely (no real solutions).
2. **$\Delta = 0$ (Zero)**:
   The ray is tangent to the sphere, touching it at exactly one point:
   $$t = -\frac{b}{2a}$$
3. **$\Delta > 0$ (Positive)**:
   The ray intersects the sphere at two distinct points:
   $$t_1 = \frac{-b - \sqrt{\Delta}}{2a}, \quad t_2 = \frac{-b + \sqrt{\Delta}}{2a}$$