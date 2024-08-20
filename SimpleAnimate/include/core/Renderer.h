#pragma once

#include <control/Control.h>
#include <core/Scene.h>
#include <glfw/glfw3.h>
#include <camera/Camera.h>
#include <core/Object3D.h>
#include <light/Light.h>

namespace SA
{

  struct SA_API RenderItem
  {
    Object3D *object;
    Geometry *geometry;
    Material *material;
    Shader *shader;
    Camera *camera;
  };

  class SA_API Renderer
  {
  public:
    Renderer();
    void render(Scene &scene, Camera &camera);

  private:
    std::unordered_map<Object3D *, RenderItem> render_list;
    std::unordered_map<Shader *, RenderItem> shader_state;

    enum LightType : size_t
    {
      Point,
      Directional,
      Spot
    };
    std::array<std::vector<Light *>, 3> lights;

    void renderItem(RenderItem &item, bool first_time);
    void addLight(Light *light);
    void clearLights();
  };
} // namespace SA
