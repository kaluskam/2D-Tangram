#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

namespace mgl {
    class Shape {
    public:
        GLubyte a;
        std::vector<GLubyte> indices;
        Shape() {};
    };

    class RightTriangle : public Shape {
    public:
        static glm::vec4 BASE_VERTICES[];
        glm::vec4 vertices[3];
        glm::vec4 color;

        RightTriangle(glm::vec3 p, GLfloat scale, float degrees, glm::vec4 c);
        ~RightTriangle() {};
    };

    class Square : public Shape {
    public:
        static glm::vec4 BASE_VERTICES[];
        glm::vec4 vertices[4];
        glm::vec4 color;

        Square(glm::vec3 p, GLfloat scale, float degrees, glm::vec4 c);
        ~Square() {};
    };
}

