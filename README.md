# SimpleAnimate

This is a C++ library for rendering with OpenGL.

## Dependences

Before everything starts, I should inform that this project relies on following libraries.

Pre-compiled dlls and other dependency files can be found in [externals](https://github.com/Alexzjc2003/SimpleAnimate/tree/master/externals).

### glad

This program uses [glad1][glad] for OpenGL API implementations.

#### Specifications & Extensions:

Following [LearnOpenGL][learnopengl], this program specifies opengl as **330 core**.

Following glad extensions are required if you're generating code on https://glad.dav1d.de/

- GL_ARB_debug_output
- GL_ARB_shading_language_include

### glfw3

This program uses [glfw3][glfw] for window, event managing and so on.

The glfw3 is imported in dll version, with [glfw-3.3.8][glfw-3.3.8] version embedded.

### glm

This program uses [glm][glm](0.9.4) to handle math (matrices, vectors, quaternions and so on).

### stb_image

This program uses [stb_image][stb] to load image files.

[glfw-3.3.8]: (https://github.com/glfw/glfw/releases/tag/3.3.8)
[learnopengl]: (https://github.com/JoeyDeVries/LearnOpenGL)
[glad]: (https://github.com/Dav1dde/glad)
[glfw]: (https://github.com/glfw/glfw)
[glm]: (https://github.com/g-truc/glm)
[stb]: (https://github.com/nothings/stb/blob/master/stb_image.h)
