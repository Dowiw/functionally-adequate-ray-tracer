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

---

# Transforming Coordinates and Normals

## 1. Object Space vs. World Space

* **Object (Local) Space**: The canonical space where a 3D shape is defined at its simplest form. E.g., a sphere is centered at local $(0,0,0)$ with a radius of $1.0$.
* **World Space**: The global scene space where the camera, lights, and final geometry reside.

To bridge the two spaces, each object stores a **Transformation Matrix** ($M$):
$$P_{\text{world}} = M \cdot P_{\text{local}}$$

## 2. Ray-Object Intersection (World to Object Space)

Rather than transforming simple shape geometries (like spheres) into complex world-space shapes (like skewed ellipsoids) to calculate intersections, we transform the ray into the object's local space:
$$P_{\text{object}} = M^{-1} \cdot P_{\text{world}}$$

This allows the intersection code in `intersect` to always run against a simple unit sphere centered at $(0, 0, 0)$.

## 3. Surface Normals (Object to World Space)

When calculating shading, we need the surface normal in **World Space**. However, we calculate it in **Object Space** first.

We cannot use the standard transformation matrix $M$ to move the normal to world space because scaling and shearing distort the perpendicular angle of normal vectors. Instead, we use the **transpose of the inverse** of the object's transformation matrix:

$$N_{\text{world}} = (M^{-1})^T \cdot N_{\text{object}}$$

### The 5-Step Normal Calculation Recipe in `normal_at`:
1. **Inverse-Transform the Point**: Multiply the world point $P_{\text{world}}$ by $M^{-1}$ to get $P_{\text{object}}$.
2. **Compute Local Normal**: Subtract the local sphere center $(0,0,0)$ from $P_{\text{object}}$.
3. **Transpose-Inverse-Transform the Normal**: Multiply $N_{\text{object}}$ by $(M^{-1})^T$ to get $N_{\text{world}}$.
4. **Fix Vector Representation**: Force the $w$ component of the resulting tuple to `VECTOR` ($0.0$) to discard translation.
5. **Normalize**: Normalize the final vector to unit length.