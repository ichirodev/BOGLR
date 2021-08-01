// VISIT THE FOLLOWING SITES FOR MORE INFORMATION ON...
//          Vertex: https://www.khronos.org/opengl/wiki/Vertex_Specification
//          glVertexAttribPointer: https://docs.gl/gl4/glVertexAttribPointer
// ------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>

class Vertex {
    public:
        Vertex(const glm::vec3& pos, const glm::vec2& textCoord) {
            this->pos = pos;
            this->textCoord = textCoord;
        }

        inline glm::vec3* GetPos() { return &pos; }
        inline glm::vec2* GetTextCoord() { return &textCoord; }

    private:
        glm::vec3 pos;
        glm::vec2 textCoord;
};

class Mesh {
    public:
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices) {
            m_drawCount = numIndices;
            //m_drawCount = numVertices;
            
            /// Prepare Vertex Array for use
            glGenVertexArrays(1, &m_vertexArrayObject);
            glBindVertexArray(m_vertexArrayObject);
            
            std::vector<glm::vec3> positions;
            std::vector<glm::vec2> textCoords;

            positions.reserve(numVertices);
            textCoords.reserve(numVertices);

            for (unsigned int i = 0; i < numVertices; i++) {
                positions.push_back(*vertices[i].GetPos());
                textCoords.push_back(*vertices[i].GetTextCoord());
            }

            //// Pass vertex data to the GPU
            // Generate the buffers to store data
            glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
            // Bind (prepare) array of buffers
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
            // Buffers given data
            glBufferData(GL_ARRAY_BUFFER,
                        numVertices * sizeof(positions[0]),
                        &positions[0], GL_STATIC_DRAW /* Use STATIC_DRAW when the data store contents will be modified once and used many times. */);
            
            glEnableVertexAttribArray(0);

            // Define an array of generic vertex attribute data
            // void glVertexAttribPointer( 	GLuint index,
            //        GLint size,
            //        GLenum type,
            //        GLboolean normalized,
            //        GLsizei stride,
            //        const GLvoid * pointer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            /// Pass texture data to the GPU
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXTCOORD_VB]);
            glBufferData(GL_ARRAY_BUFFER,
                        numVertices * sizeof(textCoords[0]),
                        &textCoords[0], GL_STATIC_DRAW);
            
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        numIndices * sizeof(indices[0]),
                        &indices[0], GL_STATIC_DRAW);

            glBindVertexArray(0);
        }

        void Draw() {
            glBindVertexArray(m_vertexArrayObject);

            //glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
            glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
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
            TEXTCOORD_VB,
            INDEX_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayObject;  // Object which contains one or more Vertex Buffers, stores information of the complete rendered object              
        GLuint m_vertexArrayBuffers[NUM_BUFFERS]; // Memory buffer that holds information about vertices,
                                                  // these can contain any kind of information such coordinates, colors, etc

        unsigned int m_drawCount;
};