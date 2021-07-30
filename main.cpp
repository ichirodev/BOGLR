#include <iostream>
#include <GL/glew.h>
#include "display.h" 
#include "mesh.hpp"                 
#include "shader.hpp"        
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"

#define WIDTH 1440
#define HEIGHT 720

using namespace std;

// Examples of OpenGL working with full 3D models
void TriangleBounceAroundTheScreen(float& counter, Mesh& mesh, Shader& shader, Transform& transform, Texture& texture, Camera& camera);

int main(void)
{
    Display display(WIDTH, HEIGHT, "Ichiro\'s OpenGL Renderer"); // Display Settings

    Shader shader("./res/basicShader"); // Add Shaders to the current program

    Vertex vertices[] = { Vertex(glm::vec3(-0.2, -0.2, 0), glm::vec2(0.0, 0.0)),
                          Vertex(glm::vec3(0, 0.2, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.2, -0.2, 0), glm::vec2(1.0, 0.0)), }; 

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    Texture texture("./res/defaultTexture.jpg");
    Transform transform;
    float aspectRadio = (float)display.GetWidth() / (float)display.GetHeight();
    Camera camera(glm::vec3(0,0,-2), 70.0f, aspectRadio, 0.01f, 1000.0f);

    float counter = 0.0f;

    while(!display.isClosed()) {
        display.Clear(0.8f, 0.8f, 0.85f, 1.0f);
        
        TriangleBounceAroundTheScreen(counter, mesh, shader, transform, texture, camera);

        display.Update();
    }
    return 0;
}

void TriangleBounceAroundTheScreen(float& counter, Mesh& mesh, Shader& shader, Transform& transform, Texture& texture, Camera& camera) {
    transform.GetPos().x = sinf(counter * 0.3f);
    transform.GetRot().x = counter * 0.16f; 
    transform.GetRot().y = counter * 0.4f; 
    transform.GetRot().z = counter * 0.16f; 
    shader.Bind();
    texture.Bind(0);
    shader.Update(transform, camera);
    mesh.Draw();

    counter += 0.04f;
}