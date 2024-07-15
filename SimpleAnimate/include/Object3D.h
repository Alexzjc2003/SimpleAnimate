#pragma once

#include <map>

#include <geometry/Geometry.h>
#include <material/Material.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace SA
{
  class Object3D
  {
  public:
    Object3D(Geometry *geometry, Material *material);

    void setPosition(const glm::vec3 &_pos);
    void setScale(const glm::vec3 &_scale);
    void setEuler(const glm::vec3 &_euler);
    void setQuaternion(const glm::quat &_quat);

    glm::vec3 getPosition() const;
    glm::vec3 getScale() const;
    glm::vec3 getEuler() const;
    glm::quat getQuaternion() const;
    glm::vec3 getDirection() const;

    glm::mat4 getModelLocal();
    glm::mat4 getModelWorld();

    void add(Object3D *object);
    void remove(Object3D *object);
    void removeFromParent();

  protected:
    Object3D();

    Geometry *pGeometry;
    Material *pMaterial;

    std::map<int, Object3D *> children;
    Object3D *parent;

    int id;

  private:
    Object3D &operator=(const Object3D &) {}
    Object3D(const Object3D &) {}
    static int nextId;

    glm::vec3 position;
    glm::quat quaternion;
    glm::vec3 scale;
    glm::vec3 euler;

    glm::mat4 _model;
    bool _model_needs_update;
  };

} // namespace SA