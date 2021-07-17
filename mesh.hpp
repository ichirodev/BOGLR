#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
    public:
        Vertex(const glm::vec3& pos) {
            this->pos = pos;
        }

    private:
        glm::vec3 pos;
};

class Mesh {
    public: 
        Mesh(Vertex* vertices, unsigned int numVertices) {
            m_drawCount = numVertices;
            
            glGenVertexArrays(1, &m_vertexArrayObject);
            glBindVertexArray(m_vertexArrayObject);
            
            //// Pass data to the GPU

            // Generate the buffers to store data
            glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
            // Bind (prepare) buffers in order to store data
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
            // Buffers given data
            glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);
        }

        void Draw() {
            glBindVertexArray(m_vertexArrayObject);

            glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

            glBindVertexArray(0);
        }

        virtual ~Mesh() {
            glDeleteVertexArrays(1, &m_vertexArrayObject);            
        }
    
    private:
        Mesh(const Mesh& other);
        void operator=(const Mesh& other);

        enum {
            POSITION_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];

        unsigned int m_drawCount;
};