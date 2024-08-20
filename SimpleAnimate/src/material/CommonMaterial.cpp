#include "pch.h"
#include "material/CommonMaterial.h"

using namespace SA;

StaticShader CommonMaterial::shader = StaticShader("./static/shader/static/common/.vert", "./static/shader/static/common/.frag");

CommonMaterial::CommonMaterial(
	const std::unordered_map<std::string, Texture*>& _maps,
	const Color& _color)
	: //  Material(_maps),
	color(_color)
{
	diffuseMap = getMap(_maps, "diffuse");
	pShader = &CommonMaterial::shader;
}

void CommonMaterial::updateUniforms()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(diffuseMap->target, diffuseMap->texID);

	pShader->use()
	    .set("uDiffuse", 0);
}
