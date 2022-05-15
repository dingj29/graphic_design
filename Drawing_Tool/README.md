# Drawing_Tool
 
 To be able to compile and run the assignment, setup OpenGL and freeglut. To run the assignment, simply use the command "make" while in the main directory. 

## Personal Infos
- Name: Jianlan Ding


## Development
- OS used: Windows 10
- platform: Visual Studio 2019

## Project Functionality Description
To create a basic drawing tool using OpenGL and freeglut. The user should be able to interact with the canvas and doing all sorts of fun stuff. (Ex. making a point, draw lines, even painting a picture!)

 
## Usage (Interaction with User)
| Command  | Description  |
|---|---|
| q  | quit  |
| Q  | quit  |
| r  | To clean the canvas  |
| R  | To clean the canvas  |
| +  | To increase the brush size |
| -  | To decrease the brush size  |
| left-click  | To draw a single dot on the canvas  |   
| 1  | To change the brush colour to red  |
| 2  | To change the brush colour to ultramarine blue  |
| 3  | To change the brush colour to green|
| 4  | To change the colour to yellow |
| 5  | To change the colour to light blue |
| 6  | To change the colour to purple (just for fun) |
| e  | To change to eraser mode (extra feature)|
| E  | To change to eraser mode (extra feature)|
## Class: Point2D
constructor: Point2D (GLfloat x,  GLfloat y, float size, float redf, float greenf, float bluef)
method: paintPoint()
fields: 
- GLfloat xVal 
- GLfloat yVal
- float mySize
- float myRed
- float myGreen
- float myBlue

     
## Functions: 

paintPoint()
 - To draw a single point on the canvas
 - colour is defined by: glColor3f(myRed, myGreen, myBlue), where myRed, myGreen and myBlue are fields of Point2D objects.
 - size is defined by: glPointSize(mySize), where mySize is field of Point2D objects.

myInti()
- Setup the 2D viewing of the canvas(colour mode, model-view, projection etc.)

display()
 - To set up a clean canvas.
 - Use glFlush() to show the effects.
 

mouse()
- if the user press down the left-button, append the coordinate to the vector 
- Called by glutMouseFunc()
- Has structure: mouse(int btn, int state, int x,int y) 
- glutPostRedisplay is called to make repeated calls to display function
 

mouseMotion()
- Save the motion of user's mouse cursor as coordinates and append to the vector.
- Called when mouse moves while a left-button is pressed 
- Called by glutMotionFunc()
- has structure: mouseMotion(int x,int y) 
- glutPostRedisplay is called to make repeated calls to display function
 

paintScene()
- To iterate through the vector and call paintPoint() function to paint the points.
- Use glFlush() to take effects

keyListener()
- Called by glutKeyboardFunc()
- Has structure: keyListener(unsigned char key, int x, int y)
- Switch cases of user input and taking all kinds of effects: change properties of points, clean the canvas and exit. 


## References

 https://docs.microsoft.com/en-us/windows/win32/opengl/gl-functions
 
 https://stackoverflow.com/questions/4206472/understanding-the-relationship-between-glutdisplayfunc-and-glutpostredisplay
 
 https://www.opengl.org/resources/libraries/glut/spec3/node51.html
 
 https://community.khronos.org/t/how-to-clear-screen-after-drawing/18623
 
 https://en.cppreference.com/w/cpp/container/vector
 
 https://community.khronos.org/t/using-glutkeyboardfunc/59946

file named Square1.cc and slides from lecture and the lecture of course
 
 
