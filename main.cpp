#include <iostream>
#include <GL/glew.h>
#include "display.h" 
#include "mesh.hpp"                 
#include "shader.hpp"        

using namespace std;

int main(void)
{
    Display display(1600, 900, "Hello"); // Display Settings

    Shader shader("./res/basicShader"); // Add Shaders to the current program

    Vertex vertices[] = { Vertex(glm::vec3(-0.3, -0.5, 0)),
                          Vertex(glm::vec3(0, 0.5, 0)),
                          Vertex(glm::vec3(0.3, -0.5, 0)) }; 

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

    while(!display.isClosed()) {
        display.Clear(0.1f, 0.1f, 0.2f, 1.0f);

        shader.Bind();
        mesh.Draw();

        display.Update();
    }
    return 0;
}
