# SimpleAnimate Document

## Core

These are cores of SimpleAnimate. You can see (almost) all the core classes and functions with their usage below.

*Following classes are arranged in alphabet order.*

### class Object3D (*in Object3D.h*)

This class is the base for almost every 3D objects in SimpleAnimate. (including Camera, Scene...)

To describe an Object3D, these variables are needed:

#### Position

```cpp
private:
	glm::vec3 position;
public:
	glm::vec3 getPosition() const;
	Object3D& setPosition(const glm::vec3& _pos)
```

#### Direction

```cpp
private:
	glm::vec3 euler;
	glm::quat quaternion;
public:
	glm::vec3 getEuler() const;
	glm::quat getQuaternion() const;
	Object3D& setEuler(const glm::vec3& _euler);
	Object3D& setQuaternion(const glm::quat& _quat);

	glm::vec3 getDirection() const;
	static const glm::vec3 default_direction // (0, 0, -1)
```

Calling *setEuler* or *setQuaternion* will update both **euler** and **quaternion**, so you can get the newest **euler** or **quaternion** by calling *getXxx*, no matter which set you called before.

Calling *getDirection* will return you a glm::vec3 in local space representing the facing direction of an Object3D. The facing direction of an Object3D will initially be **(0, 0, -1)** or **default_direction** (negativeZ) in its local space if you don't set its **euler** or **quaternion**.
