#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>

GLenum _glCheckError(const char *file, int line);
#define glCheckError() _glCheckError(__FILE__, __LINE__)

void APIENTRY glDebugOutput(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const char *message, const void *userParam);
void glEnableDebug();

GLenum _glCheckError(const char *file, int line)
{
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string error;
    switch (errorCode)
    {
    case GL_INVALID_ENUM:
      error = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      error = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      error = "INVALID_OPERATION";
      break;
    // case GL_STACK_OVERFLOW: error = "STACK_OVERFLOW"; break;
    // case GL_STACK_UNDERFLOW: error = "STACK_UNDERFLOW"; break;
    case GL_OUT_OF_MEMORY:
      error = "OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      error = "INVALID_FRAMEBUFFER_OPERATION";
      break;
    }
    std::cout << error << "|" << file << "(" << line << ")" << std::endl;
  }
  return errorCode;
}

void APIENTRY glDebugOutput(
    GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const char *message, const void *userParam)
{
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    return;
  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "):\n\t" << message << std::endl;
  switch (source)
  {
  case GL_DEBUG_SOURCE_API_ARB:
    std::cout << "    Source: API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
    std::cout << "    Source: WindowSystem";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
    std::cout << "    Source: ShaderCompiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
    std::cout << "    Source: ThirdParty";
    break;
  case GL_DEBUG_SOURCE_APPLICATION_ARB:
    std::cout << "    Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER_ARB:
    std::cout << "    Source: Other";
    break;
  }
  std::cout << std::endl;

  switch (type)
  {
  case GL_DEBUG_TYPE_ERROR_ARB:
    std::cout << "      Type: Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
    std::cout << "      Type: DeprecatedBehaviour";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
    std::cout << "      Type: UndefinedBehaviour";
    break;
  case GL_DEBUG_TYPE_PORTABILITY_ARB:
    std::cout << "      Type: Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE_ARB:
    std::cout << "      Type: Performance";
    break;
    //	case GL_DEBUG_TYPE_MARKER_ARB:
    //		std::cout << "Type:Marker"; break;
    //	case GL_DEBUG_TYPE_PUSH_GROUP_ARB:
    //		std::cout << "Type:PushGroup"; break;
    //	case GL_DEBUG_TYPE_POP_GROUP_ARB:
    //		std::cout << "Type:PopGroup"; break;
  case GL_DEBUG_TYPE_OTHER_ARB:
    std::cout << "      Type: Other";
    break;
  }
  std::cout << std::endl;

  switch (severity)
  {
  case GL_DEBUG_SEVERITY_HIGH_ARB:
    std::cout << "  Severity: high";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM_ARB:
    std::cout << "  Severity: medium";
    break;
  case GL_DEBUG_SEVERITY_LOW_ARB:
    std::cout << "  Severity: low";
    break;
    //	case GL_DEBUG_SEVERITY_NOTIFICATION_ARB:
    //		std::cout << "Severity:notification"; break;
  }

  std::cout << std::endl;
  std::cout << std::endl;
}

void glEnableDebug()
{
  GLint flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  // GL_CONTEXT_FLAG_DEBUG_BIT Macro should be 0x0002,
  // yet I can't find it
  if (flags & 0x0002)
  {
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    glDebugMessageCallbackARB(glDebugOutput, nullptr);
    glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
                             0, nullptr, GL_TRUE);
  }
}