// VISIT THE FOLLOWING SITES FOR MORE INFORMATION ON...
//          Vertex: https://www.khronos.org/opengl/wiki/Vertex_Specification
//          glVertexAttribPointer: https://docs.gl/gl4/glVertexAttribPointer
// ------------------------------------------------------------------------------------------------------------------------------------------------------
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
            
            /// Prepare Vertex Array for use
            glGenVertexArrays(1, &m_vertexArrayObject);
            glBindVertexArray(m_vertexArrayObject);
            
            //// Pass data to the GPU
            // Generate the buffers to store data
            glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
            // Bind (prepare) array of buffers
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
            // Buffers given data
            glBufferData(GL_ARRAY_BUFFER,
                        numVertices * sizeof(vertices[0]),
                        vertices, GL_STATIC_DRAW /* Use STATIC_DRAW when the data store contents will be modified once and used many times. */);
            
            glEnableVertexAttribArray(0);

            // Define an array of generic vertex attribute data
            // void glVertexAttribPointer( 	GLuint index,
            //        GLint size,
            //        GLenum type,
            //        GLboolean normalized,
            //        GLsizei stride,
            //        const GLvoid * pointer);
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

        GLuint m_vertexArrayObject;  // Object which contains one or more Vertex Buffers, stores information of the complete rendered object              
        GLuint m_vertexArrayBuffers[NUM_BUFFERS]; // Memory buffer that holds information about vertices,
                                                  // these can contain any kind of information such coordinates, colors, etc

        unsigned int m_drawCount;
};