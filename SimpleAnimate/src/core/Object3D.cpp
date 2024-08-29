#include "pch.h"
#include "core/Object3D.h"

#include <glm/gtx/euler_angles.hpp>

#include "util/Math.h"


using namespace SA;

const glm::vec3 Object3D::default_front = glm::vec3(0, 0, -1);
const glm::vec3 Object3D::default_up = glm::vec3(0, 1, 0);
int Object3D::nextId = 1;

Object3D::Object3D() : pGeometry(nullptr),
pMaterial(nullptr),
children({}),
parent(nullptr),
scale(1.0f),
position(0.0f),
euler(0.0f),
quaternion(1.0f, glm::vec3(0.0f)),
_model(1.0f),
_model_needs_update(false),
state(),
id(nextId++)

{
  ;
}

Object3D::Object3D(Geometry* geometry, Material* material) : Object3D()
{
  pGeometry = geometry;
  pMaterial = material;
}

Object3D& Object3D::setPos(const glm::vec3& _pos)
{
  position = _pos;
  _model_needs_update = true;

  return *this;
}

Object3D& Object3D::setDir(const glm::vec3& _front, const glm::vec3& _up)
{
  // glm::quatLookAtRH returns a quaternion which transforms
  // (0, 0, -1) to the desired direction(_front)
  return setQuaternion(glm::quatLookAtRH(_front, _up));
}

Object3D& Object3D::setScale(const glm::vec3& _scale)
{
  scale = _scale;
  _model_needs_update = true;

  return *this;
}

Object3D& Object3D::setEuler(const glm::vec3& _euler)
{
  euler = _euler;
  quaternion = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
  _model_needs_update = true;

  return *this;
}

Object3D& Object3D::setQuaternion(const glm::quat& _quat)
{
  quaternion = _quat;
  euler = glm::eulerAngles(quaternion);
  _model_needs_update = true;

  return *this;
}

/*
 * Translate on axis
 * Axis will be in local space, and normalization is on user's duty.
 */
Object3D& Object3D::translateOnAxis(const glm::vec3& _axis, const float _dist)
{
  glm::vec3 _x = quaternion * _axis * _dist;
  return setPos(getPosLocal() + _x);
}

Object3D& Object3D::rotateOnAxis(const glm::vec3& _axis, const float _radians)
{
  return setQuaternion(getQuaternion() * glm::angleAxis(_radians, _axis));
}

Object3D& Object3D::rotateOnWorldAxis(const glm::vec3& _axis, const float _radians)
{
  return setQuaternion(glm::angleAxis(_radians, glm::normalize(_axis)) * getQuaternion());
}

glm::vec3 Object3D::getPosLocal()
{
  return position;
}

glm::vec3 Object3D::getPosWorld()
{
  glm::mat4 _m = getModelWorld();

  return _m[3];
}

glm::vec3 Object3D::getScale() const
{
  return scale;
}

glm::vec3 Object3D::getEuler() const
{
  return euler;
}

glm::quat Object3D::getQuaternion() const
{
  return quaternion;
}

glm::vec3 Object3D::getDirLocal()
{
  //return glm::normalize(-_model[2]);
  return getQuaternion() * default_front;
}

glm::vec3 Object3D::getDirWorld()
{
  glm::mat4 _m = getModelWorld();

  return glm::normalize(-_m[2]);
}

glm::mat4 Object3D::getModelLocal()
{
  if (_model_needs_update)
  {
    _model = compose(position, quaternion, scale);
    _model_needs_update = false;
  }

  return _model;
}

glm::mat4 Object3D::getModelWorld()
{
  auto _m = getModelLocal();
  return parent ? parent->getModelWorld() * _m : _m;
}

Object3D& Object3D::add(Object3D* object)
{
  children[object->id] = object;
  if (object->parent)
    object->parent->remove(object);
  object->parent = this;

  return *this;
}

Object3D& Object3D::remove(Object3D* object)
{
  if (children[object->id])
  {
    object->parent = nullptr;
    children.erase(object->id);
  }

  return *this;
}

void Object3D::removeFromParent()
{
  if (parent)
  {
    parent->remove(this);
  }
}

// iterators
using iterator = Object3D::iterator;
iterator::iterator(const iterator::pointer_type _p)
  : pObj(_p), pRoot(_p)
{
  if (!_p)
    return;
}

iterator::reference_type iterator::operator*() const
{
  return *pObj;
}

iterator::pointer_type iterator::operator->()
{
  return pObj;
}

iterator& iterator::operator++()
{
  // check if end()
  if (!pObj)
    return *this;

  // check if any children
  if (!pObj->children.empty())
  {
    pObj = pObj->children.begin()->second;
    return *this;
  }

  // no children, recursively find next "sibling"
  while (pObj != pRoot)
  {
    auto p = pObj->parent;
    // FIXME: may be problematic, as complier hints that
    // it can't deduce the type (auto it)
    auto it = ++(p->children.find(pObj->id));
    if (it == p->children.end())
    {
      pObj = p;
      continue;
    }
    pObj = it->second;
    return *this;
  }

  // next is end()
  pObj = nullptr;
  return *this;
}

iterator iterator::operator++(int)
{
  iterator temp = *this;
  ++(*this);
  return temp;
}

bool iterator::operator==(const iterator& other) const
{
  return pObj == other.pObj;
}

bool iterator::operator!=(const iterator& other) const
{
  return pObj != other.pObj;
}

iterator Object3D::begin()
{
  return iterator(this);
}

Object3D::iterator Object3D::end()
{
  return iterator(nullptr);
}