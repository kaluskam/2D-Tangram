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

//////////////////////////////////////////////////////////////////// VAOs & VBOs

typedef struct {
  GLfloat XYZW[4];
  GLfloat RGBA[4];
} Vertex;

Vertex GlmVec4ToVertex(glm::vec4 v, glm::vec4 c) {
    return {
        {v.x, v.y, v.z, v.w}, {c.x, c.y, c.z, c.w} };
}


mgl::RightTriangle triangle = mgl::RightTriangle(glm::vec3(1, 0, 0),  0.5f, 0.0f, glm::vec4(1, 0, 0, 1));
const Vertex Vertices[] = {
    GlmVec4ToVertex(triangle.vertices[0], triangle.color), 
    GlmVec4ToVertex(triangle.vertices[1], triangle.color),
    GlmVec4ToVertex(triangle.vertices[2], triangle.color)
};

mgl::Square square = mgl::Square(glm::vec3(0, 0, 0), 0.5f, 0.0f, glm::vec4(0, 1, 0, 1));
const Vertex squareVertices[] = {
    GlmVec4ToVertex(square.vertices[0], square.color),
    GlmVec4ToVertex(square.vertices[1], square.color),
    GlmVec4ToVertex(square.vertices[2], square.color),
        GlmVec4ToVertex(square.vertices[3], square.color)
};

std::vector<mgl::Shape> shapes = {triangle, square};

//glm::vec4 VertexToGlmVec4(Vertex v) {
//    return glm::vec4(
//        v.XYZW[0], v.XYZW[1], v.XYZW[2], v.XYZW[3]
//    );
//}



//const Vertex Vertices[] = {
//    {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
//    {{1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
//    {{0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}};

const GLubyte Indices[] = {0, 1, 2};
const GLubyte squareIndices[] = { 0, 1, 2, 2, 3, 0 };

void MyApp::createBufferObjects() {
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);

  {
    glGenBuffers(2, VboId);

    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(POSITION);
      glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            reinterpret_cast<GLvoid *>(0));
      glEnableVertexAttribArray(COLOR);
      glVertexAttribPointer(
          COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
          reinterpret_cast<GLvoid *>(sizeof(squareVertices[0].XYZW)));
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    {
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices,
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

  int counter = 0;
  for (auto shape : shapes) {
      glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(I));
      glDrawElements(GL_TRIANGLES, shape.indices.size(), GL_UNSIGNED_BYTE,
          reinterpret_cast<GLvoid*>(counter));
      counter += shape.indices.size();
  }



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
  engine.setWindow(600, 600, "Hello Modern 2D World", 0, 1);
  engine.init();
  engine.run();
  exit(EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////////////////////// END
