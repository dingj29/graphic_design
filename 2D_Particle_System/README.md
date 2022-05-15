# 2D_Particle_System
 
 To be able to compile and run the assignment, setup OpenGL and freeglut. To run the assignment, simply use the command "make" while in the main directory. Make sure you download my modified version mathLib2D.h and mathLib2D.cpp.

## Personal Infos
- Name: Jianlan Ding


## Development
- OS used: Windows 10
- platform: Visual Studio 2019
- MinGW 64-bits

## Project Functionality Description
To generate a 2D particle system using OpenGL/Glut. Particles are randomly initialized with following properties: location, speed, vector(direction), size, color. Particles would bounce off the screen edge. Particles are initialized with a random and relatively small size, then they can grow to have a bigger size after activated the grow_and_split feature. After a particle reaching the certain size, it splits into two smaller particles and the newborn particles may grow and split. The user should be able to interact with the viewing box and adding particles, remove particles and pause etc. Furthermore, after activating mouse_change_color feature, the particle may change color when mouse cursor approach.

 
## Usage (Interaction with User)
| Command  | Description  |
|---|---|
| g  | To activate or deactivate grow_and_split extra feature |
| G  | To activate or deactivate grow_and_split extra feature |
| c  | To activate or deactivate mouse_change_color feature |
| C  | To activate or deactivate mouse_change_color feature |
| q  | quit  |
| Q  | quit  |
| r  | To reset the showing box to initial state  |
| R  | To reset the showing box to initial state  |
| +  | To increase the range of attraction or repulsion |
| -  | To decrease the range of attraction or repulsion |
| left-click  | To attract the points in a certain range |   
| right-click | To repluse the points in a certain range |
| p  | To pause/resume the animation |
| P  | To pause/resume the animation |
| UpArrow  | To globally increase the speed of particles |
| DownArrow  | To globally decrease the speed of particles |
| d  | To remove a particle which is closest to the mouse cursor |
| D  | To remove a particle which is closest to the mouse cursor |

## Extra Features
Bounce_off_edge: Bouncing off edge of screen with corrected direction.

Mouse_change_color: A passive mouse mode which will interact whenever the mouse hits a particle. When mouse passed by a particle, it's color would change.

Grow_and_split: To let particle to grow continuously(increasing its size by using timer function). Then after reaching the certain size, it split into two smaller particles and the newborn particles begin to grow and split.
## Class: Point2D
constructor: Point2D (float inX, float inY, float size)
method: drawPoint(), distanceTo(), fastDistanceTo();
fields: 
- float mX
- float mY
- float size

## Class: Vec2D
constructor: Vec2D (float inX, float inY)
method: length(), normalize(), multiply(), addVector(), movePoint(), createVector()
fields: 
- float mX
- float mY
 

## Class: Color
constructor: Point2D (float red, float green, float blue)
fields: 
- float myRed
- float myGreen
- float myBlue
## Functions: 

drawPoint(float x, float y, float size, float red, float green, float blue)
 - To draw a single point on the showing box.
 - Red, green and blue are parameters passed from attricutes of Color object, in colorVector.
 - Size is defined by: glPointSize(size), where size is a field of Point2D object.
 - Position is determined by mX and mY of Point2D object.

generateAll()
- Function which initialize a set of vectors for a particle.
- call generateSpeed(), generateVector(), generatePoint2D() and generateColor().

generateSpeed()
- Function which generates a vector of speeds in float.

generatePoint2D()
- Function which generates a vector of Point2D objects.

generateVector()
- Function which generate a vector of Vec2D objects.

generateColor()
- Function which generate a vector of Color objects.

erase_index(int index)
- Function that removes a particle by removing a certain member in each vector at a given index.

erase_all()
- Function that removes all particles by clearing all vectors. 

insert_point()
- Function that insert a particle by appending new member to each vector.

move_all()
- Fuction which move a particle in one place to another by its vector and speed.

attractOrRepulse()
- Function which reset the particle direction vector to direction towards the mouse cursor or away from mouse cursor.

motion(int mX, int mY)
- It calls the function attrackOrRepulse()
- Mouse motion function allows particles to follow when we holding the LMB and moving the mouse cursor. 
- Mouse motion function allows particles to move away from cursor we hold the RMB and moving around.

passive(int mX, int mY)
- Passive function updates the mouse cursor location synchronously.

bounce_off_edge()
- Function which let particle to bounce off the edge of sreen.

clash_color_change()
- Function change the color of particle when mouse cursor approach.

drawScene()
- Function which call drawPoint to draw the particles to the screen.

display()
 - To set up a clean showing box.
 - Shows two features by calling functions bounce_off_edge() and clash_color_change().
 - Call glutSwapBuffers() to perform the front and back buffer swap. 
 

mouse()
- If the user press down the left-button, set buttonPress to 1.
- If the user press down the right-button, set buttonPress to 2.
- Call the function attackOrRepulse().
 

special(int key, int x, int y)
- Special function to handle the glut special input like uparrow key and downarrow key.

resize(int w, int h)
- Called when openGL window is resized. The position of the mouse cursor should stay at the same place.

FPS(int val)
- The animation function
- Call moveall() if animate is true
- rendering every 17 miliseconds
- makes particles to move

Growth(int val)
- The timer function
- Make each particle to grow to certain size and then split to 2 smaller particles.
- rendering every 5 seconds

kbd(unsigned char key, int x, int y)
- Shows how user can interact with program  by pressing speci
- Switch cases of user input and showing all kinds of effects: pause/resume, reset to initial state, add and remove a single particle, increase the speed globally and exit. 


## References

 https://docs.microsoft.com/en-us/windows/win32/opengl/gl-functions
 
https://www2.cs.arizona.edu/classes/cs433/spring02/opengl/dblbuffer.html
 
 https://www.opengl.org/resources/libraries/glut/spec3/node51.html
 
 https://www.opengl.org/resources/libraries/glut/spec3/node64.html
 
 https://en.cppreference.com/w/cpp/container/vector
 
 https://community.khronos.org/t/using-glutkeyboardfunc/59946
 
 https://stackoverflow.com/questions/3267243/in-opengl-how-can-i-adjust-for-the-window-being-resized

tutorial2 file(first lab)
 
 
