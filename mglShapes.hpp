#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

namespace mgl {

    typedef struct {
        GLfloat XYZW[4];
        GLfloat RGBA[4];
    } Vertex;

    class Shape {
    public:
        std::vector<glm::vec4> vertices;
        glm::vec4 color;

        Vertex* vArray;
        GLubyte* indices;
        int arraySize;
        int indicesArrSize;

        Shape() {};
        Shape(Vertex* arr, int arraySize, GLubyte* indices, int indicesArrSize) : vArray(arr), arraySize(arraySize), indices(indices), indicesArrSize(indicesArrSize) {};
    };

    class RightTriangle : public Shape {
    public:
        static glm::vec4 BASE_VERTICES[];

        RightTriangle(glm::vec3 p, GLfloat scale, float degrees, glm::vec4 c);
        ~RightTriangle() {};
    };

    class Square : public Shape {
    public:
        static glm::vec4 BASE_VERTICES[];

        Square(glm::vec3 p, GLfloat scale, float degrees, glm::vec4 c);
        ~Square() {};
    };

    class Parallelogram : public Shape {
    public:
        static glm::vec4 BASE_VERTICES[];

        Parallelogram(glm::vec3 p, GLfloat scale, float degrees, glm::vec4 c);
        ~Parallelogram() {};
    };
}

