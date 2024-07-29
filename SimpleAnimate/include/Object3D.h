#pragma once

#include <map>
#include <stack>

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

    // setters
    // all setters return the reference to the instance
    // for chain calling
    Object3D &setPosition(const glm::vec3 &_pos);
    Object3D &setScale(const glm::vec3 &_scale);
    Object3D &setEuler(const glm::vec3 &_euler);
    Object3D &setQuaternion(const glm::quat &_quat);

    Object3D &translateOnAxis(const glm::vec3 &_axis, const float _dist);
    Object3D &rotateOnAxis(const glm::vec3 &_axis, const float _radians);

    // getters
    glm::vec3 getPosition() const;
    glm::vec3 getScale() const;
    glm::vec3 getEuler() const;
    glm::quat getQuaternion() const;
    glm::vec3 getDirection() const;

    glm::mat4 getModelLocal();
    glm::mat4 getModelWorld();

    // object management
    Object3D &add(Object3D *object);
    Object3D &remove(Object3D *object);
    void removeFromParent();

    // iterators
    class iterator
    {
    public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = Object3D;
      using pointer_type = Object3D *;
      using reference_type = Object3D &;

      reference_type operator*() const;
      pointer_type operator->();

      iterator &operator++();
      iterator operator++(int);

      bool operator==(const iterator &other) const;
      bool operator!=(const iterator &other) const;

      iterator(const pointer_type _p);

    protected:
    private:
      // std::list<pointer_type> _lst;
      pointer_type pRoot;
      pointer_type pObj;
    };

    iterator begin();
    iterator end();

    Geometry *pGeometry;
    Material *pMaterial;

  protected:
    Object3D();

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