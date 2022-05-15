# 3GC3_Assignment3
 
 To be able to compile and run the assignment, setup OpenGL and freeglut. To run the assignment, simply use the command "make" while in the main directory. Make sure you download main.cpp, makefile, particle.h and particle.cpp.

## Personal Infos
- Name: Zicheng Guo
- student Num: 400250658
- Name: Jianlan Ding
- student Num: 400235703


## Development
- OS used: Windows 10
- platform: Visual Studio 2019, vs code
- MinGW 64-bits

## Assignment2 Functionality Description
To generate a 3D particle fountain using OpenGL/Glut. Particles are randomly initialized with following properties: rotation angle, speed, direction, shape, color, size and material(there are different types of particles). Particles should be continuously added to the system, and should shoot upward from the "particle origin", then fall back to the plane. Despite of the mandatory features, Pressing N or n should place the camera position inside the next particle enters the system; Pressing 'w' 'a' 's' d' should change the angle of cannon and initial particle trajectory. Besides, we implemented three types of particles: rubber ball, anti-gravity ball and superglue ball. 

 
## Usage (Interaction with User)
| Key  | Description  |
|---|---|
| f, F  | To activate or deactivate friction mode |
| UpArrow  | To rotate the scene up about x-axis with limitation|
| DownArrow  | To rotate the scene down about x-axis with limitation|
| RightArrow  | To rotate the scene right about y-axis without limitation|
| LeftArrow  | To rotate the scene left about y-axis without limitation|
| "_"  | To pause or resume the simulation  |
| r,R  | To reset the particle system to original state |
| l, L  | To toggle the light or remove the light |
| n, N | To place camera position inside the next particles enters the system |
| w, W  | To rotate the cannon to back and effects initial particle trajectory with limitation|
| s, S  | To rotate the cannon to front and effects initial particle trajectory with limitation|
| d, D  | To rotate the cannon to right and effects initial particle trajectory with limitation|
| a, A  | To rotate the cannon to left and effects initial particle trajectory with limitation|
| o, O  | Move first light source on it's Y axis to Positive direction |
| i, I  | Move first light source on it's Y axis to negative direction |
| u, U  | Move second light source on it's X axis to Positive direction |
| y, Y  | Move second light source on it's X axis to negative direction |
## Extra Features
Particle Cannon: Particles are shoted by the cylinder cannon. Pressing keys (“W”, “A”, “S”, “D”) should 
change the angle of the cannon, which should also affect the initial particle trajectory. 

Particle Properties: Generate particles with different properties. When mat = 0, We have rubber particles, 
it will bounce after hitting the plane; when mat=1, we have anti-gravity particle(will not influence by gravity); 
when mat = 2 we have superglue ball, it will stop after hitting the floor. All three types of particles have different material when turn on lighting mode.

Particle Cam: Pressing 'N' or 'n' would puts the camera position inside the next particle that enters the system. 

## Class: Particle
constructor: Particle (double* pos, double* dir, int spd, double* ang, int size, double* rgb, int material, int age, int shape)
method: move(), move_with_fract(double fraction), apply_grav(float grav), check_delet();
fields: 
- double pos[3]{}
- double dir[3]{}
-  int spd
-  double ang[3]{}
-  int size
-  double rgb[3]{}
-  int age
-  int shape

## Functions
drawParticle(double red, double green, double blue, double pos0, double pos1,
    double pos2, double ang0, double ang1, double ang2, int size, int shape, int mat)
 - To create a particle in our 3D system.
 - Pass color, position, rotate angle, size, shape adn material in as parameters.

erase_all()
- Function that removes all particles by clearing the particle vector. 

randomFloat(float upperBound)
- Function that generate a random floating point number given its upperbound.

randomInt(Int upperBound)
- Function that generate a random integer given its upperbound.

drawGround()
- Function that draw the 3D plane and the cylinder canno and offer them material.

drawScene(void)
- Function that iterate the vector and call drawParticle.

add_particals(int amount)
- Function that call constructor of Particle class by passing parameters and adding the created particle objects to the vector. 

move_all()
- Function that move the particles around, apply gravity. Also check to delete if a particle reaches it predetermined limit.

display()
 - Check for if the extra feature Particle Cam executed, adjust the view accordingly.
 - Check for is toggle light is activated.
 - Call drawGround() and drawScene().

 handleReshape(int w, int h)
- To handle the resizing of the screen.

mouse()
- If the user press down the left-button, set buttonPress to 1.
- If the user press down the right-button, set buttonPress to 2.
- Call the function attackOrRepulse().
 

init()
- Function to initiate the basic settings.

special(int key, int x, int y)
- Special function to handle the glut special input like uparrow key and downarrow key.

resize(int w, int h)
- Called when openGL window is resized. The position of the mouse cursor should stay at the same place.

animation(int value)
- The animation function
- Call add_particle() if animate is true
- rendering 35 miliseconds
- makes particles to move and rotate.


kbd(unsigned char key, int x, int y)
- Shows how user can interact with program  by pressing specific key.
- Switch cases of user input and showing all kinds of effects: pause/resume, reset to initial state, firing particle at specific direction, change camera position, toggling lighting and exit. 

spcialkbd(int key, int x, int y)
- Handle special keyboard event such as uparrow key, downarrow key and etc.

showMenu()
- Print to console all keyboard events and their usage.

## References

https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluCylinder.xml
 
https://www2.cs.arizona.edu/classes/cs433/spring02/opengl/dblbuffer.html
 
https://learnopengl.com/Advanced-OpenGL/Face-culling
 
https://en.cppreference.com/w/cpp/container/vector
 
http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
 

lecture files
 
 

 
