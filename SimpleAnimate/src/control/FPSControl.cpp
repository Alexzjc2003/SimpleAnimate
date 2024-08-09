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
	mouse.x = mouse.w / 2;
	mouse.y = mouse.h / 2;
}

void FPSControl::keyCallback(
	int key, int scancode, int action, int mods)
{
	auto _update = [&key, &action](bool& status, int _key)
	{
		if (key != _key)
			return;
		if (action == GLFW_PRESS)
			status = true;
		if (action == GLFW_RELEASE)
			status = false;
	};

	_update(move.left, GLFW_KEY_A);
	_update(move.right, GLFW_KEY_D);
	_update(move.forward, GLFW_KEY_W);
	_update(move.backward, GLFW_KEY_S);
	_update(move.up, GLFW_KEY_SPACE);
	_update(move.down, GLFW_KEY_LEFT_SHIFT);
}

void FPSControl::mouseMoveCallback(
	double x_pos, double y_pos)
{
	double dx = x_pos - mouse.x;
	double dy = -(y_pos - mouse.y);

	mouse.x = x_pos;
	mouse.y = y_pos;

	// right --> mouse.x+ --> yaw-
	// up    --> mouse.y+ --> pitch+
	glm::vec3 _euler = (*pObject).getEuler();
	_euler.y -= dx * mouse_sensitivity;
	_euler.x += dy * mouse_sensitivity;

	//logger.log(_euler, "FPSControl::mouseMoveCallback()::_euler");
	// set constraints for pitch
	constexpr double constraint = glm::pi<double>() / 2;
	//constexpr double constraint = 3.14159265358979365 / 4;
	//constexpr double constraint = 89.99;
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
	double _d = delta;
	double _s = _d * move_speed;

	// As controls are usually applied to cameras,
	// for intuitions, we have this mapping, that
	// forward --> Z-
	// right   --> X+
	// up      --> Y+
	// and vice versa.
	glm::vec3 _m(
		move.right - move.left,
		move.up - move.down,
		move.backward - move.forward);


	// _m = glm::normalize(_m);
	_m *= _s;
	logger.log(_m, "FPSControl::inputLoop()::_m");

	(*pObject).translateOnAxis(_m, 1);
}