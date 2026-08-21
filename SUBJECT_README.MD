*This project has been created as part of the 42 curriculum by kmonjard and sstark.*

## Description

"miniRT" is simple implementation of a raytracer, taking a .rt scene file as its input.
It supports:
- spheres, planes, cylinders and cones
- one spotlight
- ambient lighting
- phong reflection model
- moving camera

The rendered image updates with incremental resolution increases, allowing for realtime movement in the scene.

## Instructions

### Compilation

Run `make` at the project root to compile the executable `miniRT`.

### Execution

Run the executable `miniRT` to start the program.
It takes exactly one argument, which should be the location of a .rt file describing the scene to be rendered.

### File Format

The .rt file will be parsed line by line, ignoring empty lines and lines starting with '#'.
Each line describes an element, with parameters seperated by one or more spaces.
The first parameter is the elements identifier, followed by the relevant information as specified below:

**A**: Ambient Lighting
- ambient brightness in the range 0.0 to 1.0
- color in RGB format, each component in the range 0 to 255
Has to be declared exactly once in a scene file!

**C**: Camera
- x, y, z coordinates of the viewpoint
- orientation vector
- horizontal fov in degrees in the range 0.0 to 180.0
Has to be declared exactly once in a scene file!

**L**: Light
- x, y, z coordinates
- brightness in the range 0.0 to 1.0
- color in RGB format, each component in the range 0 to 255
Has to be declared exactly once in a scene file!

**sp**: Sphere
- x, y, z coordinates
- diameter
- color in RGB format, each component in the range 0 to 255

**pl**: Plane
- x, y, z coordinates
- orientation vector
- color in RGB format, each component in the range 0 to 255

**cy**: Cylinder
- x, y, z coordinates
- orientation vector
- diameter
- height
- color in RGB format, each component in the range 0 to 255

**co**: Cone
- x, y, z coordinates
- orientation vector
- diameter
- height
- color in RGB format, each component in the range 0 to 255

### Usage

Upon execution a window is created, which can be closed normally or by pressing ESC.
The camera can be moved with the following keys:
- **W**: move forward
- **A**: move left
- **S**: move back
- **D**: move right
- **Space**: move up
- **Shift**: move down
- **Arrow Up**: rotate up
- **Arrow Left**: rotate left
- **Arrow Down**: rotate down
- **Arrow Right**: rotate right

## Resources

Raytracing Guide: The Ray Tracer Challenge by Jamis Buck
Unoffical MLX Docs: https://harm-smits.github.io/42docs/libs/minilibx

### AI USAGE

TODO
