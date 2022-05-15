# Object Modeler
Team members: 
- Zicheng Guo
- Jianlan Ding

## How to run
Before starting, make sure GLM lib is installed properly.
Instruction on install it in windows with mingw:
- Open your mingw terminal.
- Paste `pacman -S mingw-w64-x86_64-glm` into it.
- Type `Y` into terminal to confirm install.
- Wait to be complete

More information about GLM can be found here:https://glm.g-truc.net/0.9.9/index.html
(Notice: We did not use the raypicking func from glm, as you can see in our source code. We wrote all essential algotherisms ourselves. The reason why we use library is just to make things more readable and powerful.)

Download everything from my repo. Make sure you are in the same directory as makefile. Then just type 'make'.

## Description
In this project, we develop a simple modeler system using Opengl and C++. The user is able to rendering a specific object by pressing a specific key. When user click on an object, he is able to select an object. We are asked to use mouse ray picking to achieve the selection. After an object is selected, we can translate, rotate, apply material and doing all kinds of things with it.

## Additional Features
- Custom shape: use obj file and a parser to load obj model(a cat) into game. Can be applied with material and textures.
- Save&Load Scene Plus: instead of just display the data as the normal require, we read the data and put the object into its saved position with all same attributes. You can save as many files as you needed. 

## Interface
| Command  | Description  |
|---|---|
| Mouse Left Button | select an object (in green box)  |
| Mouse Right Button | delete the selected object |
| q, Q  | quit  |
| r, R  | clear the object list (reset the scene)  |
| Alt + S| Save current scene into a file, make sure you enter the file name |
| Shift + S | Loaded saved file, make sure you enter the file to load |
| Shift + ArrowUp  | translate object up |
| Shift + ArrowDown  | translate object down  |
| Shift + ArrowLeft  | translate object left(along x-axis)  |   
| Shift + ArrowRight  | translate object right(along x-axis)  |   
| Ctrl + ArrowLeft  | translate object out of the screen(along z-axis)  |   
| Ctrl + ArrowRight  | translate object in to the screen(along z-axis)  |  
| Alt + y  | rotate the object along y axis  |
| Alt + x  | rotate the object along x axis  |
| Alt + z  | rotate the object along z axis  |
| Alt + ArrowUp  | apply symmetric scaling to object (getting bigger)  |
| Alt + ArrowDown  | apply symmetric scaling to object (getting smaller)  |
| ArrowUp  | rotate the scene up  |
| ArrowDown | rotate the scene down |
| ArrowLeft  | rotate the scene left  |
| ArrowRight | rotate the scene right |
| 1 | apply material 1 to the selected object |
| 2 | apply material 2 to the selected object |
| 3 | apply material 3 to the selected object |
| 4 | apply material 4 to the selected object |
| 5 | apply material 5 to the selected object |
| 6 | apply material 6 to the selected object |
| 8 | apply carpet texture to objects |
| 9 | apply rock texture to objects |
| 0 | apply marble texture to objects (default is marble)|
| left button | select an object |
| right button | delete the selected object |
| m, M | apply material to the selected object |
| Alt + 1 | generate a cube at world origin |
| Alt + 2 | generate a sphere at world origin|
| Alt + 3 | generate a cone at world origin|
| Alt + 4 | generate a torus at world origin|
| Alt + 5 | generate a teapot at world origin|
| Alt + 6 | generate a tetra at world origin|
| Alt + 7 | generate a cat at world origin|
| c, C | to activate or deactivate the camera control mode |
| w,s,a,d | if camera control mode is activate, then shift view near, far, left, right respectively |
| n,b | if camera control mode is activate, then shift view up, down |


## Project References: 
https://antongerdelan.net/opengl/raycasting.html
lab 6(the last lab)
https://coderedirect.com/questions/196820/how-to-apply-texture-to-glutsolidcube
https://learnopengl.com/Getting-started/Camera

 
 

 


 
