/*
 * glbridge.cpp
 * Copyright (C) 2013  Michał Garapich <michal@garapich.pl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <algorithm>
#include <cstring>
#include <vector>

#include "glbridge.h"

namespace Dee {

/**
 * Tests current render context whether it supports all required extensions.
 * If not - cannot continue.
 */
static bool supportsRequiredExtensions();

GlBridge::glVersion GlBridge::__glVersion = { -1, -1 };

bool GlBridge::extensionSupported(const std::string& extension) {
  static std::vector<std::string> extensions = __findExtensions();
  
  bool found = std::binary_search(extensions.begin(), extensions.end(), extension);
  
  Logger::debug("Extension %s found? %s", extension, found ? "yes" : "no");
  
  return found;
}

std::string&& GlBridge::errorString(GLenum errorCode) {
  switch (errorCode) {
    case GL_INVALID_ENUM:
      return std::move(std::string("GL_INVALID_ENUM"));
    case GL_INVALID_VALUE:
      return std::move(std::string("GL_INVALID_VALUE"));
    case GL_INVALID_OPERATION:
      return std::move(std::string("GL_INVALID_OPERATION"));
    case GL_OUT_OF_MEMORY:
      return std::move(std::string("GL_OUT_OF_MEMORY"));
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return std::move(std::string("GL_INVALID_FRAMEBUFFER_OPERATION​"));
    default:
      return std::move(std::string("unknown error code"));
  }
}

void
GlBridge::initVersion() {
  glGetIntegerv(GL_MAJOR_VERSION, &__glVersion.major);
  glGetIntegerv(GL_MINOR_VERSION, &__glVersion.minor);
  
  if (__glVersion.major < 0 || __glVersion.minor < 0) {
    const unsigned char* versionString =
      static_cast<const unsigned char *>(glGetString(GL_VERSION));
    
    __glVersion.major = static_cast<int>(versionString[0]) - 48;
    __glVersion.minor = static_cast<int>(versionString[2]) - 48;
  }
  
  Logger::info("OpenGL version %i.%i.", __glVersion.major, __glVersion.minor);
}

void
GlBridge::initExtensions() {
  glExtensions::init();
}

std::vector<std::string>
GlBridge::__findExtensions() {
  std::vector<std::string> extensions;
  
  if (__glVersion.major > 2) { /* modern way */
    const GLubyte * (*glGetStringi)(GLenum, GLuint) =
      getProcAddr<decltype(glGetStringi)>("glGetStringi");
    
    DeeAssert(glGetStringi);
    
    int n;
    glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    
    for (int i = 0; i < n; i++) {
      const char* ext = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
      Logger::debug("Found extension: %s", ext);
      extensions.push_back(std::string(ext));
    }
  } else { /* old way */
    const char * pExtensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
    std::string temp;
    for (size_t i = 0; i < strlen(pExtensions); ++i) {
      if (pExtensions[i] == ' ') {
        extensions.push_back(temp);
        temp.clear();
      } else {
        temp += pExtensions[i];
      }
    }
    
    if (temp.length() > 0) {
      extensions.push_back(temp);
    }
  }
  
  std::sort(extensions.begin(), extensions.end());
  
  return extensions;
}

namespace glExtensions {
  
  void   (*glActiveShaderProgram)(GLuint pipeline, GLuint program)   = nullptr;
  void   (*glAttachShader)(GLuint program, GLuint shader)            = nullptr;
  
  void   (*glCompileShader)(GLuint shader)                           = nullptr;
  GLuint (*glCreateShader)(GLenum shaderType)                        = nullptr;
  GLuint (*glCreateProgram)(void)                                    = nullptr;
  
  void   (*glDeleteProgram)(GLuint program)                          = nullptr;
  void   (*glDeleteShader)(GLuint shader)                            = nullptr;
  void   (*glDetachShader)(GLuint program, GLuint shader)            = nullptr;
  
  void   (*glGetProgramInfoLog)(GLuint program, GLsizei maxLength,
                                GLsizei* length, GLchar* infoLog)    = nullptr;
  void   (*glGetProgramiv)(GLuint program, GLenum pname, GLint* params)
                                                                     = nullptr;
  void   (*glGetShaderInfoLog)(GLuint shader, GLsizei maxLength,
                               GLsizei* length, GLchar* infoLog)     = nullptr;
  void   (*glGetShaderiv)(GLuint shader, GLenum pname, GLint* params)
                                                                     = nullptr;
  
  void   (*glLinkProgram)(GLuint program)                            = nullptr;
  
  void   (*glShaderSource)(GLuint shader, GLsizei count,
                           const GLchar** string, const GLint* length)
                                                                     = nullptr;

void
init() {
#define init_ext(name)                                                        \
  do {                                                                        \
    name = GlBridge::getProcAddr<decltype(name)>(#name);                      \
    DeeAssert(name);                                                          \
  } while (0)
  
  if (!supportsRequiredExtensions()) {
    Logger::fatal("The graphic system's requirements were not met.\n \
      Upgrade your computer or update the GPU driver.");
    
    return;
  }
  
  /* Must-have extensions */
  init_ext(glAttachShader);
  init_ext(glCompileShader);
  init_ext(glCreateShader);
  init_ext(glCreateProgram);
  init_ext(glDeleteProgram);
  init_ext(glDeleteShader);
  init_ext(glDetachShader);
  init_ext(glGetProgramInfoLog);
  init_ext(glGetProgramiv);
  init_ext(glGetShaderInfoLog);
  init_ext(glGetShaderiv);
  init_ext(glLinkProgram);
  init_ext(glShaderSource);
  
  if (GlBridge::extensionSupported("GL_ARB_separate_shader_objects")) {
    init_ext(glActiveShaderProgram);
  }

#undef init_ext
}

} /* namespace glExtensions */

bool
supportsRequiredExtensions() {
  return GlBridge::extensionSupported("GL_ARB_vertex_shader")
      && GlBridge::extensionSupported("GL_ARB_fragment_shader");
}

} /* namespace Dee */
