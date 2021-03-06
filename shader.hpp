// VISIT THE FOLLOWING SITES FOR MORE INFORMATION ON...
//          VAOs, VBOs, Vertex and Fragment Shaders: https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Important reminder: The shader pipeline behaves as follows: Vertex Shaders -> Geometry Shaders -> (Rasterizing Engine) -> Fragment Shaders. 

#pragma once

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "transform.hpp"
#include "camera.hpp"

static std::string LoadShader(const std::string& fileName) {
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open()) {
        while(file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}


void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }

    if(success == GL_FALSE) {
        if (isProgram) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        } else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

static GLuint CreateShader(const std::string& text, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0) {
        std::cerr << "Error: Shader could not be created" << std::endl;
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLenghts[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLenghts[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLenghts);
    
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

    return shader;
}

class Shader {
    public:
        Shader(const std::string& fileName) {
            m_program = glCreateProgram();
            m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
            m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

            // Add shaders to the program
            for(unsigned int i = 0; i < NUM_SHADERS; i++) {
                glAttachShader(m_program, m_shaders[i]);
            }

            glBindAttribLocation(m_program, 0, "position");
            glBindAttribLocation(m_program, 1, "textCoord");

            glLinkProgram(m_program);
            CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader program failed to link");

            glValidateProgram(m_program);
            CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid");
        
            m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
        }

        void Bind() {
           glUseProgram(m_program); 
        }

        void Update(const Transform& transform, const Camera& camera) {
            glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
            glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
        }

        virtual ~Shader() {
            for(unsigned int i = 0; i < NUM_SHADERS; i++) {
                glDetachShader(m_program, m_shaders[i]);
                glDeleteShader(m_shaders[i]);
            }

            glDeleteProgram(m_program);
        }

    private:
        static const unsigned int NUM_SHADERS = 2;

        Shader(const Shader& other) {}
        void operator=(const Shader& other) {}

        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];

        enum {
            TRANSFORM_U,
            NUM_UNIFORMS
        };
        GLuint m_uniforms[NUM_UNIFORMS];

};