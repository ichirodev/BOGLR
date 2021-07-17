// Run from console with g++ main.cpp -o main.o -std=c++11 -lGL -lGLEW -lSDL2; ./main.o
#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "mesh.hpp"

using namespace std;

int main(void)
{
    Display display(1600, 900, "Hello");
    Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
                          Vertex(glm::vec3(0, 0.5, 0)),
                          Vertex(glm::vec3(0.5, -0.5, 0)) }; 

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

    while(!display.isClosed()) {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        mesh.Draw();

        display.Update();
    }
    return 0;
}
