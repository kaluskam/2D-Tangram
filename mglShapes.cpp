#include "mglShapes.hpp"

namespace mgl {

    Vertex GlmVec4ToVertex(glm::vec4 v, glm::vec4 c) {
     return {
         {v.x, v.y, v.z, v.w}, {c.x, c.y, c.z, c.w} };
    }

    glm::vec4 RightTriangle::BASE_VERTICES[] = {
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
    };



    RightTriangle::RightTriangle(glm::vec3 p, GLfloat s, float degrees, glm::vec4 c) : Shape(new Vertex[3], 3, new GLubyte[3], 3) {
        color = c;

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), p);
        glm::mat4 rotationMatrix = glm::rotate(translationMatrix, glm::radians(degrees), glm::vec3(0, 0, 1)); // ASK         
        glm::mat4 transformationM = glm::scale(rotationMatrix, glm::vec3(s));
        
        for (int i = 0; i < 3; i++) {
            vArray[i] = GlmVec4ToVertex(transformationM * BASE_VERTICES[i], color);
            indices[i] = i;
        }
    }

    glm::vec4 Square::BASE_VERTICES[] = 
    {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
    };

    Square::Square(glm::vec3 p, GLfloat s, float degrees, glm::vec4 c) : Shape(new Vertex[4], 4, new GLubyte[6], 6) {
        color = c;

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), p);
        glm::mat4 rotationMatrix = glm::rotate(translationMatrix, glm::radians(degrees), glm::vec3(0, 0, 1));
        glm::mat4 transformationM = glm::scale(rotationMatrix, glm::vec3(s));

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;

        for (int i = 0; i < 4; i++) {
            vArray[i] = GlmVec4ToVertex(transformationM * BASE_VERTICES[i], color);
        }
    }

    glm::vec4 Parallelogram::BASE_VERTICES[] =
    {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f)
    };

    Parallelogram::Parallelogram(glm::vec3 p, GLfloat s, float degrees, glm::vec4 c) : Shape(new Vertex[4], 4, new GLubyte[6], 6) {
        color = c;

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), p);
        glm::mat4 rotationMatrix = glm::rotate(translationMatrix, glm::radians(degrees), glm::vec3(0, 0, 1));
        glm::mat4 transformationM = glm::scale(rotationMatrix, glm::vec3(s));

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;

        for (int i = 0; i < 4; i++) {
            vArray[i] = GlmVec4ToVertex(transformationM * BASE_VERTICES[i], color);
        }
    }
}