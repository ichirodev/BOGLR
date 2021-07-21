#pragma once

#include <string>
#include "stb_image.h"
#include <GL/glew.h>

class Texture {
    public:
        Texture(const std::string& fileName) {
            unsigned int width, height, numComponents;
            unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

            glGenTextures(1, &m_texture);
            glBindTexture(GL_TEXTURE_2D, m_texture);

            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            
            stbi_image_free(data);
        }

        void Bind(unsigned int unit) {
            glActiveTexture(GL_TEXTURED + unit);
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }
        
        virtual ~Texture() {
            glDeleteTextures(1, &m_texture);
        }

    private:
        GLuint m_texture;
};