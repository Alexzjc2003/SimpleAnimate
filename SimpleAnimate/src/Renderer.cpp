#include "pch.h"
#include "Renderer.h"
#include "util/Logger.h"

using namespace SA;

Renderer::Renderer() {
	glEnable(GL_DEPTH_TEST);
}

void Renderer::render(Scene& scene, Camera& camera)
{
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (auto& object : scene)
	{
		renderObject(object, camera);
	}
}

void Renderer::renderObject(Object3D& object, Camera& camera) const
{
	// 1. get shader from material
	if (!object.pMaterial)
		return;
	auto& shader = *(object.pMaterial->pShader);
	shader.use();

	// 2. set drawing uniforms
	shader
		.set("uModel", object.getModelWorld())
		.set("uView", camera.getViewMatrix())
		.set("uProj", camera.getProjMatrix());

	logger.log(camera.getProjMatrix() * camera.getViewMatrix() * object.getModelWorld(), "MVP");

	// 3. set material uniforms
	object.pMaterial->updateUniforms();

	// 4. draw
	if (!object.pGeometry)
		return;
	object.pGeometry->draw();
}
