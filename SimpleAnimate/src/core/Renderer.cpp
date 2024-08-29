#include "pch.h"
#include "core/Renderer.h"

#include <format>

#include "material/BlinnPhongMaterial.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"
#include "util/Logger.h"

using namespace SA;

Renderer::Renderer()
{
  glEnable(GL_DEPTH_TEST);
}

void Renderer::render(Scene& scene, Camera& camera)
{
  glClearColor(scene.color.r / 255.0, scene.color.g / 255.0, scene.color.b / 255.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // first loop
  render_list.clear();
  clearLights();

  //for (auto& child : scene.children)
    //for (auto& object : *(child.second))
    for (auto& object : scene)
    {
      // setup light
      if (auto ptr = dynamic_cast<Light*>(&object))
      {
        addLight(ptr);
        ptr->updateUniform();
      }
      // make list item
      if (object.pGeometry && object.pMaterial && object.pMaterial->pShader)
      {
        render_list[&object] = {
            &object,
            object.pGeometry,
            object.pMaterial,
            object.pMaterial->pShader,
            &camera };
      }
    }

  // second loop - Actually rendering
  shader_state.clear();
  for (auto& item : render_list)
  {
    // check if shader is different from last time
    Shader* pShader = item.second.shader;
    if (shader_state.find(pShader) == shader_state.end())
    {
      shader_state[pShader] = item.second;
      renderItem(item.second, true);
      continue;
    }

    renderItem(item.second, false);
  }
}

void Renderer::renderItem(RenderItem& item, bool first_time)
{
  item.shader->use().set("uModel", item.object->getModelWorld());

  if (first_time || item.camera != shader_state[item.shader].camera)
  {
    (*item.shader)
      .set("uView", item.camera->getViewMatrix())
      .set("uProj", item.camera->getProjMatrix())
      .set("uCamPos", item.camera->getPosWorld());
    shader_state[item.shader].camera = item.camera;
  }

  if (first_time && dynamic_cast<BlinnPhongMaterial*>(item.material))
  {
    BlinnPhongMaterial* pMaterial = dynamic_cast<BlinnPhongMaterial*>(item.material);
    pMaterial->updateUniforms();

    size_t i;
    GLuint j = 0;
    // Point light
    for (i = 0; i < lights[Point].size(); ++i, ++j)
    {
      item.shader->bindUBO(std::format("PointLight[{}]", i), lights[Point][i]->uniform.ubo, j);
    }
    item.shader->set("PointLightCount", (int)i);
    // Directional light
    for (i = 0; i < lights[Directional].size(); ++i, ++j)
    {
      item.shader->bindUBO(std::format("DirectionalLight[{}]", i), lights[Directional][i]->uniform.ubo, j);
    }
    item.shader->set("DirectionalLightCount", (int)i);
    // Spot light
    for (i = 0; i < lights[Spot].size(); ++i, ++j)
    {
      item.shader->bindUBO(std::format("SpotLight[{}]", i), lights[Spot][i]->uniform.ubo, j);
    }
    item.shader->set("SpotLightCount", (int)i);
  }

  item.geometry->draw();
}

void Renderer::addLight(Light* light)
{
  if (dynamic_cast<PointLight*>(light))
  {
    lights[Point].push_back(light);
  }
  else if (dynamic_cast<DirectionalLight*>(light))
  {
    lights[Directional].push_back(light);
  }
  else if (dynamic_cast<SpotLight*>(light))
  {
    lights[Spot].push_back(light);
  }
}

void Renderer::clearLights()
{
  for (auto& light : lights)
  {
    light.clear();
  }
}