# BallProject

This is an experiment project for study and test OpenGL. The hierarchy of the classes are not yet in their final state.
Probably every object would move to a different dll, which could give its own Model matrixes for the Model-View-Projection matrixes,
and the View would get only their interfaces.

For compiling the program, you must have a t: drive with an OGLPack.
You must have T:\OGLPack\lib\x64 libraries and T:\OGLPack\include headers available

The pojects uses additional dependencies for:
    opengl32.lib
    SDL2.lib
    SDL2main.lib
    SDL2_image.lib
    glew32.lib
   
Controlls:
 W      - forward
 A      - strafe left
 D      - strafe right
 S      - backward
 Ctrl   - move down
 Space  - move up
 Mouse  - rotating the camera
