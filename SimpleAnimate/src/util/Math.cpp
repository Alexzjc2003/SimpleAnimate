#include "pch.h"
#include "util/Math.h"

#include <glm/gtx/quaternion.hpp>

using namespace SA;

glm::mat4 SA_API SA::compose(const glm::vec3 &translate, const glm::quat &quaternion, const glm::vec3 &scale)
{
  glm::mat4 result;

  const auto &x = quaternion.x;
  const auto &y = quaternion.y;
  const auto &z = quaternion.z;
  const auto &w = quaternion.w;

  const auto x2 = x + x, y2 = y + y, z2 = z + z;
  const auto xx = x * x2, xy = x * y2, xz = x * z2;
  const auto yy = y * y2, yz = y * z2, zz = z * z2;
  const auto wx = w * x2, wy = w * y2, wz = w * z2;

  const auto sx = scale.x, sy = scale.y, sz = scale.z;

  result[0][0] = (1.0f - (yy + zz)) * sx;
  result[0][1] = (xy + wz) * sx;
  result[0][2] = (xz - wy) * sx;
  result[0][3] = 0;

  result[1][0] = (xy - wz) * sy;
  result[1][1] = (1.0f - (xx + zz)) * sy;
  result[1][2] = (yz + wx) * sy;
  result[1][3] = 0;

  result[2][0] = (xz + wy) * sz;
  result[2][1] = (yz - wx) * sz;
  result[2][2] = (1.0f - (xx + yy)) * sz;
  result[2][3] = 0;

  result[3][0] = translate.x;
  result[3][1] = translate.y;
  result[3][2] = translate.z;
  result[3][3] = 1.0f;

  return result;
}
