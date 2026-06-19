# miniRT - TODO

These are the available functions.
> • open, close, read, write,
printf, malloc, free, perror,
strerror, exit.

> • All functions of the math
library. (Man page: man
math.h or man 3 math. Don’t
forget to compile with the
-lm flag).

> • All functions of the MinilibX
library.

> • gettimeofday()

## Repository Setup & Architecture
- [x] **Makefile Creation**
  - [x] 1.1.1: Define compiler (`cc`) and mandatory flags (`-Wall -Wextra -Werror`).
  - [x] 1.1.2: Add library flags for Math (`-lm`) and MLX (e.g., `-lmlx -lXext -lX11` for Linux or framework flags for macOS).
  - [ ] 1.1.3: Implement `all`, `clean`, `fclean`, `re`, and `bonus` optionally.
- [x] **Core Data Structures (Headers)**
  - [x] 1.2.1: Define 3D vector struct (x, y, z floats/doubles).
	- t_tuple is defined.

  - [ ] 1.2.2: Define Ray struct (origin, direction).
  - [x] 1.2.3: Define Color struct (r, g, b integers or floats).
  - [ ] 1.2.4: Define Camera struct (origin, orientation, FOV).
  - [x] 1.2.5: Define Light & Ambient structs.
  - [x] 1.2.6: Define Object struct (enum for type: SPHERE/PLANE/CYLINDER, and union/fields for specific properties).
  - [x] 1.2.7: Define Scene struct (holds camera, lights, and a linked list of Object).

## Parser (`.rt` files)
- [ ] **File I/O & Validation**
  - [ ] 2.1.1: Validate `argc == 2` and `argv[1]` ends with `.rt`.
  - [ ] 2.1.2: Open file and handle invalid FD (`perror`/`strerror`).
  - [ ] 2.1.3: Read file line by line using `get_next_line`.
- [ ] **Line Tokenization**
  - [ ] 2.2.1: Split each line by whitespace to extract parameters.
  - [ ] 2.2.2: Implement a router function to call specific parsers based on the first token (identifier).
- [ ] **Element Parsing & Strict Validation**
  - [ ] 2.3.1: Parse Ambient (`A`) -> Check uniqueness, limits [0.0, 1.0], RGB [0, 255].
  - [ ] 2.3.2: Parse Camera (`C`) -> Check uniqueness, orientation vector range [-1.0, 1.0], FOV [0, 180]. Normalize the orientation vector.
  - [ ] 2.3.3: Parse Light (`L`) -> Check uniqueness, brightness [0.0, 1.0], RGB [0, 255].
  - [ ] 2.3.4: Parse Sphere (`sp`) -> Extract coordinates, convert diameter to radius, check RGB.
  - [ ] 2.3.5: Parse Plane (`pl`) -> Extract coordinates, check orientation vector [-1.0, 1.0], normalize it, check RGB.
  - [ ] 2.3.6: Parse Cylinder (`cy`) -> Extract coordinates, check orientation vector [-1.0, 1.0] and normalize, convert diameter to radius, extract height, check RGB.
- [ ] **Error Management**
  - [ ] 2.4.1: Create a unified exit function that frees all allocated memory (GNL buffers, linked lists, MLX pointers).
  - [ ] 2.4.2: On any parsing failure, print `Error\n` followed by a specific message (e.g., "Error\nInvalid RGB range for Sphere").

## Mathematics Library
- [ ] **Basic Tuple Operations**
  - [x] 3.1.1: Doubles comparison function
  - [x] 3.1.2: Tuples comparison function
  - [x] 3.1.3: Tuple addition
  - [x] 3.1.4: Tuple subtraction
  - [x] 3.1.5: Tuple scalar multiplication
  - [x] 3.1.6: Tuple scalar division
  - [x] 3.1.7: Tuple negation
  - [x] 3.1.8: Calculate magnitude
  - [x] 3.1.9: Calculate normalized vector
  - [x] 3.1.10: Calculate dot product
  - [x] 3.1.11: Calculate cross product
- [ ] **Color Operations**
  - [ ] 3.2.1: hadamard_product (shur product)
- [ ] **Matrix Operations**
  - [ ] 3.3.1: Matrix creation and inspection (4x4, 3x3, 2x2)
  - [ ] 3.3.2: Matrix equality comparison
  - [ ] 3.3.3: Multiply two 4x4 matrices
  - [ ] 3.3.4: Multiply a matrix by a tuple
  - [ ] 3.3.5: Implement identity matrix (multiplication and transposition)
  - [ ] 3.3.6: Transpose a matrix
  - [ ] 3.3.7: Calculate the determinant of a 2x2 matrix
  - [ ] 3.3.8: Extract submatrices (from 3x3 and 4x4)
  - [ ] 3.3.9: Calculate minors
  - [ ] 3.3.10: Calculate cofactors
  - [ ] 3.3.11: Calculate determinants of 3x3 and 4x4 matrices
  - [ ] 3.3.12: Test matrix invertibility
  - [ ] 3.3.13: Matrix inversion (using cofactor expansion)

## Core Raytracing Engine
- [ ] **Viewport Setup**
  - [ ] 4.1.1: Calculate viewport width and height based on Camera FOV and window aspect ratio.
  - [ ] 4.1.2: Calculate camera coordinate system (Forward, Right, and Up vectors) using cross products. (Handle edge case where Forward is exactly parallel to the global Up vector).
- [ ] **Ray Generation**
  - [ ] 4.2.1: Map 2D screen coordinates (x, y pixels) to 3D viewport coordinates.
  - [ ] 4.2.2: Generate a Ray starting at the camera origin and pointing to the mapped 3D viewport pixel.
- [ ] **Render Loop**
  - [ ] 4.3.1: Create nested loops to iterate over window height (`y`) and window width (`x`).
  - [ ] 4.3.2: Shoot ray per pixel.
  - [ ] 4.3.3: Call intersection logic for the current ray.

## Object Intersections
- [ ] **Sphere Intersection**
  - [ ] 5.1.1: Implement quadratic equation coefficients (a, b, c) for a sphere.
  - [ ] 5.1.2: Calculate discriminant ($b^2 - 4ac$).
  - [ ] 5.1.3: If hit, find the nearest positive root ($t$).
- [ ] **Plane Intersection**
  - [ ] 5.2.1: Check denominator (dot product of ray direction and plane normal). If near 0, ray is parallel to plane (no hit).
  - [ ] 5.2.2: Calculate intersection distance ($t$).
- [ ] **Cylinder Intersection**
  - [ ] 5.3.1: Implement quadratic equation for the infinite cylindrical surface.
  - [ ] 5.3.2: Once $t$ is found, project the hit point onto the cylinder axis to check if it falls within the cylinder's height limits.
  - [ ] 5.3.3: Implement intersections for the top and bottom flat disk caps (treat as planes, then check if distance from center is <= radius).

## Lighting & Shading
- [ ] **Surface Normals**
  - [ ] 6.1.1: Calculate normal at hit point for Sphere (`normalize(hit_point - center)`).
  - [ ] 6.1.2: Calculate normal at hit point for Plane (it's just the plane's orientation vector, but inverted if ray hits the back face).
  - [ ] 6.1.3: Calculate normal at hit point for Cylinder (depends on if hit was on the curved body or the caps).
- [ ] **Color Computation**
  - [ ] 6.2.1: Apply Ambient light to base object color.
  - [ ] 6.2.2: Calculate Light Vector (normalized vector from hit point to light source).
  - [ ] 6.2.3: Compute Diffuse factor (dot product of Surface Normal and Light Vector). Make sure to clamp at 0.
  - [ ] 6.2.4: Add Diffuse light contribution to final pixel color.
- [ ] **Shadows**
  - [ ] 6.3.1: Create a "Shadow Ray" starting from the hit point (add a small epsilon to origin to avoid self-intersection/shadow acne) pointing towards the light source.
  - [ ] 6.3.2: Check if this shadow ray intersects any other object in the scene.
  - [ ] 6.3.3: If it hits something AND the intersection distance is less than the distance to the light source, the point is in shadow (apply ONLY ambient light, drop diffuse).

## Window & MLX Integration
- [ ] **Window Initialization**
  - [ ] 7.1.1: Call `mlx_init()` to establish connection to display.
  - [ ] 7.1.2: Call `mlx_new_window()` with chosen resolution.
- [ ] **Image Buffer (Fast Rendering)**
  - [ ] 7.2.1: Call `mlx_new_image()` to create an off-screen buffer.
  - [ ] 7.2.2: Call `mlx_get_data_addr()` to get the memory address of the image.
  - [ ] 7.2.3: Implement `my_mlx_pixel_put(image, x, y, color)` to write pixels directly to the buffer array.
  - [ ] 7.2.4: Call `mlx_put_image_to_window()` once the whole frame is rendered.
- [ ] **Event Hooks**
  - [ ] 7.3.1: Hook `KeyPress` event. If key == ESC, trigger clean exit.
  - [ ] 7.3.2: Hook `DestroyNotify` (Event 17, clicking the window X button) to trigger clean exit.
  - [ ] 7.3.3: Call `mlx_loop()`.

## Finalization & README
- [ ] **Rigorous Testing**
  - [ ] 8.1.1: Test parser against deliberately malformed `.rt` files to check for leaks.
  - [ ] 8.1.2: Test edge cases (camera inside a sphere, camera looking exactly down the Y-axis [gimbal lock scenario]).
  - [ ] 8.1.3: Build "functional scenes" specifically designed for defense grading (e.g., a file showing shadow casting on a cylinder).
- [ ] **README Generation**
  - [ ] 8.2.1: Add the mandatory italicized 42 preamble at the very top.
  - [ ] 8.2.2: Write Description, Instructions, and Resources sections.
  - [ ] 8.2.3: Add the mandatory explicit description of how/where AI was used in the project.
