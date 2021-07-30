#include <iostream>
#include <GL/glew.h>
#include "display.h" 
#include "mesh.hpp"                 
#include "shader.hpp"        
#include "texture.hpp"
#include "transform.hpp"

using namespace std;

// Examples of OpenGL working with full 3D models
void bounceAroundTheScreenWithSin(float& counter, Mesh& mesh, Shader& shader, Transform& transform, Texture& texture);

int main(void)
{
    Display display(1600, 900, "Ichirodev OpenGL"); // Display Settings

    Shader shader("./res/basicShader"); // Add Shaders to the current program

    Vertex vertices[] = { Vertex(glm::vec3(-0.2, -0.2, 0), glm::vec2(0.0, 0.0)),
                          Vertex(glm::vec3(0, 0.4, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.2, -0.2, 0), glm::vec2(1.0, 0.0)), }; 

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    Texture texture("./res/defaultTexture.jpg");
    Transform transform;

    float counter = 0.0f;

    while(!display.isClosed()) {
        display.Clear(0.8f, 0.8f, 0.85f, 1.0f);
        
        bounceAroundTheScreenWithSin(counter, mesh, shader, transform, texture);

        display.Update();
    }
    return 0;
}

void bounceAroundTheScreenWithSin(float& counter, Mesh& mesh, Shader& shader, Transform& transform, Texture& texture) {
    transform.GetPos().y = sinf(counter);
    transform.GetPos().x = sinf(counter * 0.2f);
    transform.GetRot().z = counter * 1.2f;
    transform.SetScale(glm::vec3(cosf(counter), cosf(counter), cosf(counter)));
    shader.Bind();
    texture.Bind(0);
    shader.Update(transform);
    mesh.Draw();

    counter += 0.04f;
}