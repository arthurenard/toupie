#ifndef GLSPHERE_H
#define GLSPHERE_H

#include <QGLBuffer>
#include <QOpenGLShaderProgram>

class GLSphere
{
public:
 GLSphere()
   : vbo(QGLBuffer::VertexBuffer), ibo(QGLBuffer::IndexBuffer)
 {}

  void initialize(GLuint slices = 25, GLuint stacks = 25);

  void draw(QOpenGLShaderProgram& program, int attributeLocation);

  void bind();
  void release();

private:
  QGLBuffer vbo, ibo;
  GLuint vbo_sz;
  GLuint ibo_sz[3];
};

#endif // GLSPHERE_H
