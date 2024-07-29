#include "pch.h"
#include "Renderer.h"

using namespace SA;

Renderer::Renderer()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  pWindow = glfwCreateWindow(RENDERER::WINDOW_WIDTH, RENDERER::WINDOW_HEIGHT, "SimpleAnimate", NULL, NULL);
  glfwSetWindowPos(pWindow, 400, 200);
  glfwMakeContextCurrent(pWindow);
}

void Renderer::useControl(Control &control)
{
  control.bindWindow(pWindow);
}

void Renderer::render(Scene &scene, Camera &camera)
{
  for (auto &object : scene)
  {
    renderObject(object, camera);
  }
}

void Renderer::renderObject(Object3D &object, Camera &camera) const
{
  // 1. get shader from material
  if (!object.pMaterial)
    return;
  auto &shader = *(object.pMaterial->pShader);
  shader.use();

  // 2. set drawing uniforms
  shader
      .set("uModel", object.getModelWorld())
      .set("uView", camera.getViewMatrix())
      .set("uProj", camera.getProjMatrix());

  // 3. set material uniforms
  object.pMaterial->updateUniforms();

  // 4. draw
  if (!object.pGeometry)
    return;
  object.pGeometry->draw();
}
