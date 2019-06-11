# BallProject

This is an experiment project for study and test OpenGL. The hierarchy of the classes are not yet in their final state.
Probably every object would move to a different dll, which could give its own Model matrixes for the Model-View-Projection matrixes,
and the View would get only their interfaces.

For cmake, please extract OGLPack.zip to the root of T:\ drive. otherwise modify the Find*.cmake files.
   
Controlls:
 - W      - forward
 - A      - strafe left
 - D      - strafe right
 - S      - backward
 - Ctrl   - move down
 - Space  - move up
 - Mouse  - rotating the camera
 - Esc	- exiting the program
 
The game sets the logFile path automatically to C:/BallProject/GameLog.txt
If you dont have C:/BallProject folder, please create it, or modify the setFileName in main.cpp of Balls project.
I will modify this soon by setting the target filename in a settings.txt file, which the program should read from.
