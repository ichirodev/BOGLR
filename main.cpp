#include <iostream>
#include <GL/glew.h>
#include "display.h" 
#include "mesh.hpp"                 
#include "shader.hpp"        
#include "texture.hpp"

using namespace std;

int main(void)
{
    Display display(1600, 900, "Hello"); // Display Settings

    Shader shader("./res/basicShader"); // Add Shaders to the current program

    Vertex vertices[] = { Vertex(glm::vec3(-0.3, -0.5, 0), glm::vec2(0.0, 0.0)),
                          Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.3, -0.5, 0), glm::vec2(1.0, 0.0)), }; 

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    Texture texture("./res/defaultTexture.jpg");

    while(!display.isClosed()) {
        display.Clear(0.1f, 0.1f, 0.2f, 1.0f);

        shader.Bind();
        texture.Bind(0);
        mesh.Draw();

        display.Update();
    }
    return 0;
}
