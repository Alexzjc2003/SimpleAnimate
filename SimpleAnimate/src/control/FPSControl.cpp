#include "pch.h"
#include "core/Window.h"
#include "core/Object3D.h"
#include "control/FPSControl.h"
#include "util/Logger.h"
using namespace SA;

FPSControl::FPSControl() {}

void FPSControl::onBindWindow()
{
	auto [_w, _h] = pWindow->size.get();
	mouse.w = _w;
	mouse.h = _h;
	auto [_x, _y] = pWindow->cursorPos.get();
	mouse.x = _x;
	mouse.y = _y;

	pWindow->cursorShow = false;
}

void FPSControl::keyCallback(
		int key, int scancode, int action, int mods)
{

	auto _is = [&](int _key, int _action)
	{
		return _key == key && _action == action;
	};
	// move status updates
	auto _update = [&](bool &status, int _key)
	{
		if (_is(_key, GLFW_PRESS))
			status = true;
		if (_is(_key, GLFW_RELEASE))
			status = false;
	};

	_update(move.left, GLFW_KEY_A);
	_update(move.right, GLFW_KEY_D);
	_update(move.forward, GLFW_KEY_W);
	_update(move.backward, GLFW_KEY_S);
	_update(move.up, GLFW_KEY_SPACE);
	_update(move.down, GLFW_KEY_LEFT_SHIFT);

	// show cursor
	if (_is(GLFW_KEY_LEFT_ALT, GLFW_RELEASE) && pWindow->cursorShow.get())
	{
		pWindow->cursorShow = false;
	}
	if (_is(GLFW_KEY_LEFT_ALT, GLFW_PRESS) && !pWindow->cursorShow.get())
	{
		logger.log(111);

		pWindow->cursorShow = true;
	}
}

void FPSControl::mouseMoveCallback(
		double x_pos, double y_pos)
{
	double dx = x_pos - mouse.x;
	double dy = -(y_pos - mouse.y);
	mouse.x = x_pos;
	mouse.y = y_pos;

	// if the mouse is not hidden, we should not
	// process the mouse movement
	if (pWindow->cursorShow.get())
	{
		return;
	}

	// right --> mouse.x+ --> yaw-
	// up    --> mouse.y+ --> pitch+
	glm::vec3 _euler = (*pObject).getEuler();
	_euler.y -= dx * mouse_sensitivity;
	_euler.x += dy * mouse_sensitivity;

	// set constraints for pitch
	constexpr double constraint = glm::pi<double>() / 2;
	_euler.x = _euler.x > constraint
								 ? constraint
						 : _euler.x < -constraint
								 ? -constraint
								 : _euler.x;

	(*pObject).setEuler(_euler);
}

void FPSControl::scrollCallback(
		double x_offset, double y_offset)
{
}

void FPSControl::inputLoop(double delta)
{
	logger.log(delta, "FPSControl::inputLoop()::delta");

	// As controls are usually applied to cameras,
	// for intuitions, we have this mapping, that
	// forward --> Z-
	// right   --> X+
	// up      --> Y+
	// and vice versa.

	auto _e = pObject->getEuler();
	// horizontal (xz plane, yaw)
	auto _h =
			glm::vec3(
					move.right - move.left,
					0,
					move.backward - move.forward) *
			glm::vec3(move_speed);

	// vertical (y axis)
	auto _v =
			glm::vec3(
					0,
					move.up - move.down,
					0) *
			glm::vec3(fly_speed);

	auto _d = (glm::mat3)glm::eulerAngleY(_e.y) * _h + _v;

	pObject->setPosition(pObject->getPosition() + _d * glm::vec3(delta));
}