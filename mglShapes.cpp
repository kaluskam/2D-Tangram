#include "mglShapes.hpp"

namespace mgl {


    glm::vec4 RightTriangle::BASE_VERTICES[] = {
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
    };


    RightTriangle::RightTriangle(glm::vec3 p, GLfloat s, float degrees, glm::vec4 c) {
        color = c;

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), p);
        glm::mat4 rotationMatrix = glm::rotate(translationMatrix, glm::radians(degrees), glm::vec3(0, 0, 1)); // ASK 
        glm::mat4 transformationM = glm::scale(rotationMatrix, glm::vec3(s));
        indices = {0, 1, 2};

        for (int i = 0; i < 3; i++) {
            vertices[i] = transformationM * BASE_VERTICES[i];
        }
    }

    glm::vec4 Square::BASE_VERTICES[] = 
    {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
    };

    Square::Square(glm::vec3 p, GLfloat s, float degrees, glm::vec4 c) {
        color = c;

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), p);
        glm::mat4 rotationMatrix = glm::rotate(translationMatrix, glm::radians(degrees), glm::vec3(0, 0, 1)); // ASK 
        glm::mat4 transformationM = glm::scale(rotationMatrix, glm::vec3(s));
        indices = { 0, 1, 2, 2, 3, 0 };
        for (int i = 0; i < 4; i++) {
            vertices[i] = transformationM * BASE_VERTICES[i];
        }
    }
}