#include "pch.h"
#include "Object3D.h"

#include <glm/gtx/euler_angles.hpp>

using namespace SA;

int Object3D::nextId = 1;

Object3D::Object3D() : pGeometry(nullptr),
                       children({}),
                       parent(nullptr),
                       scale(1.0f),
                       position(0.0f),
                       euler(0.0f),
                       quaternion(1.0f, glm::vec3(0.0f)),
                       _model(1.0f),
                       _model_needs_update(false),
                       id(nextId++)

{
  ;
}

Object3D::Object3D(Geometry *geometry, Material *material) : Object3D()
{
  pGeometry = geometry;
  pMaterial = material;
}

void Object3D::setPosition(const glm::vec3 &_pos)
{
  position = _pos;
  _model_needs_update = true;
}

void Object3D::setScale(const glm::vec3 &_scale)
{
  scale = _scale;
  _model_needs_update = true;
}

void Object3D::setEuler(const glm::vec3 &_euler)
{
  euler = _euler;
  quaternion = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
  _model_needs_update = true;
}

void Object3D::setQuaternion(const glm::quat &_quat)
{
  quaternion = _quat;
  euler = glm::eulerAngles(quaternion);
  _model_needs_update = true;
}

glm::vec3 Object3D::getPosition() const
{
  return position;
}

glm::vec3 Object3D::getEuler() const
{
  return euler;
}

glm::quat Object3D::getQuaternion() const
{
  return quaternion;
}

glm::vec3 Object3D::getDirection() const
{
  return static_cast<glm::mat3>(getQuaternion()) * glm::vec3(0, 0, 1);
}

glm::mat4 Object3D::getModelLocal()
{
  if (_model_needs_update)
  {
    _model = glm::mat4(1.0f);
    _model = glm::scale(_model, scale);
    _model = glm::mat4_cast(quaternion) * _model;
    _model = glm::translate(_model, position);
  }

  return _model;
}

glm::mat4 Object3D::getModelWorld()
{
  auto _m = getModelLocal();
  return parent ? parent->getModelWorld() * _m : _m;
}

void Object3D::add(Object3D *object)
{
  children[object->id] = object;
  object->parent = this;
}

void Object3D::remove(Object3D *object)
{
  if (children[object->id])
  {
    object->parent = nullptr;
    children.erase(object->id);
  }
}

void Object3D::removeFromParent()
{
  if (parent)
  {
    parent->remove(this);
  }
}
