////////////////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Clip Space.
// A "Hello 2D World" of Modern OpenGL.
//
// Copyright (c) 2013-23 by Carlos Martinho
//
// INTRODUCES:
// GL PIPELINE, mglShader.hpp, mglConventions.hpp
//
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

#include "./mgl/mgl.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
 public:
  void initCallback(GLFWwindow *win) override;
  void displayCallback(GLFWwindow *win, double elapsed) override;
  void windowCloseCallback(GLFWwindow *win) override;
  void windowSizeCallback(GLFWwindow *win, int width, int height) override;

 private:
  const GLuint POSITION = 0, COLOR = 1;
  GLuint VaoId, VboId[2];
  mgl::ShaderProgram *Shaders;
  GLint MatrixId;

  void createShaderProgram();
  void createBufferObjects();
  void destroyBufferObjects();
  void drawScene();
};

//////////////////////////////////////////////////////////////////////// SHADERs

void MyApp::createShaderProgram() {
  Shaders = new mgl::ShaderProgram();
  Shaders->addShader(GL_VERTEX_SHADER, "clip-vs.glsl");
  Shaders->addShader(GL_FRAGMENT_SHADER, "clip-fs.glsl");

  Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, POSITION);
  Shaders->addAttribute(mgl::COLOR_ATTRIBUTE, COLOR);
  Shaders->addUniform("Matrix");

  Shaders->create();

  MatrixId = Shaders->Uniforms["Matrix"].index;
}

//////////////////////////////////////////////////////////////////// Define shapes

float minSqrtOneEight = -glm::sqrt(0.125);
mgl::RightTriangle triangle = mgl::RightTriangle(glm::vec3(-0.5, 0.0, 0), 0.5f, 0.0f, glm::vec4(0.9, 0.2, 0.4, 1));
mgl::RightTriangle triangle2 = mgl::RightTriangle(glm::vec3(0.0, minSqrtOneEight, 0), 0.25 / glm::sqrt(0.5), 90.0f, glm::vec4(0.7, 0.1, 0.7, 1));
mgl::RightTriangle triangle3 = mgl::RightTriangle(glm::vec3(minSqrtOneEight, minSqrtOneEight, 0), 0.5f, 45.0f, glm::vec4(0.4, 0.4, 1, 1));
mgl::RightTriangle triangle4 = mgl::RightTriangle(glm::vec3(0.0, minSqrtOneEight + 0.25, 0), 0.25f, 270.0f, glm::vec4(0.1, 0.7, 0.7, 1));
mgl::RightTriangle triangle5 = mgl::RightTriangle(glm::vec3(-0.25 + glm::sqrt(1 / 32.0), minSqrtOneEight + 0.75 + glm::sqrt(1 / 32.0), 0), 0.25f, 225.0f, glm::vec4(1, 0.3, 0.2, 1));
mgl::Square square = mgl::Square(glm::vec3(0, minSqrtOneEight + 0.25, 0), 0.25f, 0.0f, glm::vec4(0.1, 0.6, 0, 1));
mgl::Parallelogram parallelogram = mgl::Parallelogram(glm::vec3(0, minSqrtOneEight + 0.5, 0), 0.25f, 0.0f, glm::vec4(0.9, 0.7, 0.1, 1));

std::vector<mgl::Shape> shapes = { triangle, triangle2, triangle3, triangle4, triangle5, square, parallelogram };

//////////////////////////////////////////////////////////////////// VAOs & VBOs

void MyApp::createBufferObjects() {
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);

  {
    glGenBuffers(2, VboId);
 
    int numberOfIndices = 0;
    int numberOfVertices = 0;

    for (auto shape : shapes) {
        numberOfIndices += shape.indicesArrSize;
        numberOfVertices += shape.verticesArrSize;
    }

    GLubyte* allIndices = new GLubyte[numberOfIndices];
    mgl::Vertex* allVertices = new mgl::Vertex[numberOfVertices];

    int totalSize = numberOfVertices * sizeof(mgl::Vertex);
    int totalIndicesArrSize = numberOfIndices * sizeof(GLubyte);

    int c1 = 0;
    int c2 = 0;
    int addToIndex = 0;

    for (auto shape : shapes) {

        for (int i = 0; i < shape.indicesArrSize; i++) {
            allIndices[c1++] = shape.indices[i] + addToIndex;
        }
        
        for (int i = 0; i < shape.verticesArrSize; i++) {
            allVertices[c2++] = shape.vArray[i];
        }
        addToIndex += shape.verticesArrSize;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    {
        glBufferData(GL_ARRAY_BUFFER, totalSize, allVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(POSITION);
        glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(mgl::Vertex),
            reinterpret_cast<GLvoid*>(0));
        glEnableVertexAttribArray(COLOR);
        glVertexAttribPointer(
            COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(mgl::Vertex),
            reinterpret_cast<GLvoid*>(sizeof(allVertices[0].XYZW)));    
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    {
        
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndicesArrSize, allIndices,
                GL_STATIC_DRAW);
        
    }
  }
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(2, VboId);
}

void MyApp::destroyBufferObjects() {
  glBindVertexArray(VaoId);
  glDisableVertexAttribArray(POSITION);
  glDisableVertexAttribArray(COLOR);
  glDeleteVertexArrays(1, &VaoId);
  glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////// SCENE

const glm::mat4 I(1.0f);
const glm::mat4 M = glm::translate(glm::vec3(-1.0f, -1.0f, 0.0f));

void MyApp::drawScene() {
  // Drawing directly in clip space

  glBindVertexArray(VaoId);
  Shaders->bind();

  
    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(I));
    glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));
 




 /* glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(M));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
                 reinterpret_cast<GLvoid *>(0));*/

  //glUniformMatrix4fv();
  //glDrawElements()

  Shaders->unbind();
  glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
  createBufferObjects();
  createShaderProgram();
}

void MyApp::windowCloseCallback(GLFWwindow *win) { destroyBufferObjects(); }

void MyApp::windowSizeCallback(GLFWwindow *win, int winx, int winy) {
  glViewport(0, 0, winx, winy);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) { drawScene(); }

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[]) {
  mgl::Engine &engine = mgl::Engine::getInstance();
  engine.setApp(new MyApp());
  engine.setOpenGL(4, 6);
  engine.setWindow(1000, 1000, "Hello Modern 2D World", 0, 1);
  engine.init();
  engine.run();
  exit(EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////////////////////// END
