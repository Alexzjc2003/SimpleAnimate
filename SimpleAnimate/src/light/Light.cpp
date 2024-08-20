#include "pch.h"
#include "light/Light.h"

using namespace SA;

Light::Light(const Color &_color, const glm::vec3 &_atten)
    : ads(glm::mat3(glm::vec3(0.0),
                    glm::vec3(_color.r / 255.0, _color.g / 255.0, _color.b / 255.0),
                    glm::vec3(0.0))),
      atten(_atten),
      Object3D()
{
    uniform
        .set("ads", ads)
        .set("atten", atten);
}

Light::Light(const glm::mat3 &_ads, const glm::vec3 &_atten)
    : ads(_ads), atten(_atten), Object3D()
{
    uniform
        .set("ads", ads)
        .set("atten", atten);
}