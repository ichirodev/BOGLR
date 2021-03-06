# Basic OpenGL Renderer
---
An OpenGL renderer written in C++, it contains basic things such Shaders support, camera, transforms, mesh and textures.
Nothing fancy.

![](triangle.gif)

#### Set-up
##### Required libraries
* [GLEW](http://glew.sourceforge.net/)
* [OpenGL](https://www.opengl.org/sdk/)
* [SDL2](https://www.libsdl.org/)
* [GLM](https://www.opengl.org/sdk/libs/GLM/)

Linux users may look for said libraries on their respective package manager.

For Debian / Ubuntu:
```bash
sudo apt-get install libsdl2-dev libglew-dev libglm-dev 
```

For Arch / Manjaro:
```bash
sudo pacman -S libsdl2-dev libglew-dev libglm-dev 
```

#### Build and run
For testing purposes and rapid review and debug the project can be compiled and run with:
```bash
g++ main.cpp -o opengl.o -std=c++11 -lGL -lGLEW -lSDL2
```
Then just run the output file named "opengl.o".

---
**Ichirodev 2021**