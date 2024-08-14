#include "pch.h"
#include "core/Object3D.h"

#include <glm/gtx/euler_angles.hpp>

using namespace SA;

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
id(nextId++)

{
	;
}

Object3D::Object3D(Geometry* geometry, Material* material) : Object3D()
{
	pGeometry = geometry;
	pMaterial = material;
}

Object3D& Object3D::setPosition(const glm::vec3& _pos)
{
	position = _pos;
	_model_needs_update = true;

	return *this;
}

Object3D& Object3D::setDirection(const glm::vec3& _front, const glm::vec3& _up)
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
	return setPosition(getPosition() + _x);
}

Object3D& Object3D::rotateOnAxis(const glm::vec3& _axis, const float _radians)
{
	return setQuaternion(getQuaternion() * glm::angleAxis(_radians, glm::normalize(_axis)));
}

glm::vec3 Object3D::getPosition() const
{
	return position;
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

glm::vec3 Object3D::getDirection() const
{
	return static_cast<glm::mat3>(getQuaternion()) * default_front;
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

Object3D& Object3D::add(Object3D* object)
{
	children[object->id] = object;
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