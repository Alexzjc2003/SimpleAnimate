#pragma once

#include <map>

#include <def.h>
#include <geometry/Geometry.h>
#include <material/Material.h>
#include <core/State.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace SA
{
  class SA_API Object3D
  {
  public:
    Object3D(Geometry* geometry, Material* material);
    virtual ~Object3D() = default;

    static const glm::vec3 default_front;
    static const glm::vec3 default_up;

    // setters
    // all setters return the reference to the instance
    // for chain calling
    Object3D& setPos(const glm::vec3& _pos);
    Object3D& setDir(const glm::vec3& _front, const glm::vec3& _up = default_up);
    Object3D& setScale(const glm::vec3& _scale);
    Object3D& setEuler(const glm::vec3& _euler);
    Object3D& setQuaternion(const glm::quat& _quat);

    Object3D& translateOnAxis(const glm::vec3& _axis, const float _dist);
    Object3D& rotateOnAxis(const glm::vec3& _axis, const float _radians);
    Object3D& rotateOnWorldAxis(const glm::vec3& _axis, const float _radians);

    // getters
    glm::vec3 getPosLocal();
    glm::vec3 getPosWorld();
    glm::vec3 getDirLocal();
    glm::vec3 getDirWorld();
    glm::vec3 getScale() const;
    glm::vec3 getEuler() const;
    glm::quat getQuaternion() const;

    glm::mat4 getModelLocal();
    glm::mat4 getModelWorld();

    // object management
    Object3D& add(Object3D* object);
    Object3D& remove(Object3D* object);
    void removeFromParent();

    // iterators
    class SA_API iterator
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = Object3D;
      using pointer_type = Object3D*;
      using reference_type = Object3D&;

      reference_type operator*() const;
      pointer_type operator->();

      iterator& operator++();
      iterator operator++(int);

      bool operator==(const iterator& other) const;
      bool operator!=(const iterator& other) const;

      iterator(const pointer_type _p);

    protected:
    private:
      pointer_type pRoot;
      pointer_type pObj;
    };

    iterator begin();
    iterator end();

    Geometry* pGeometry;
    Material* pMaterial;

    State state;

    std::map<int, Object3D*> children;
    Object3D* parent;
    const int id;

  protected:
    Object3D();
    glm::vec3 position;
    glm::quat quaternion;
    glm::vec3 scale;
    glm::vec3 euler;

    glm::mat4 _model;
    bool _model_needs_update;

  private:
    Object3D& operator=(const Object3D&) { return *this; }
    Object3D(const Object3D&) = delete;
    static int nextId;

  };
} // namespace SA