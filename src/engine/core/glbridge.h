/*
 * glbridge.h
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

#ifndef GLBRIDGE_H
#define GLBRIDGE_H

#include <type_traits>
#include <string>
#include <GL/glx.h>

#include "core/deeglobal.h"
#include "utils/logger.h"

namespace Dee {

class __DeeExport__ GlBridge {
  
public:
  
  /**
   * This function obtains OpenGL extension pointers in a safe way.
   * Sample usage:
   *   
   * ~~~~{.cpp}
   * GLuint (* glCreateShader)(GLenum);
   * glCreateShader = gl::getProcAddr<decltype(glCreateShader)>("glCreateShader");
   * ~~~~
   * 
   * This is only example, one can use `glExtensions` namespace instead.
   * 
   * \param Function Function pointer type.
   * \param name Name of the function.
   * \return Function pointer or nullptr if the pointer could not be obtained.
   * \sa extensionSupported().
   */
  template <typename Function> static
    Function getProcAddr(const char *name) {
      
      static_assert(std::is_pointer<Function>::value,
        "This function returns only function pointer!");
      
      Function temp = reinterpret_cast<Function>(
          glXGetProcAddress(reinterpret_cast<const GLubyte*>(name))
        );
      
      if (!temp)
        Logger::warning("Function pointer not available: %s", name);
      
      return temp;
    }
  
  /**
   * Checks if the given extension is supported by the GPU driver.
   * 
   * \param extension Extension name.
   * \return True if the GPU driver supports the extension, otherwise false.
   * \sa getProcAddr().
   */
  static bool extensionSupported(const std::string& extension);
  
  /**
   * Converts error code to readable string.
   * 
   * \param errorCode The error code, possibly got by glGetError() function.
   * \return The error string.
   */
  static std::string&& errorString(GLenum errorCode);
  
  /**
   * Gets OpenGL major verion number.
   * 
   * If this function returns -1, it means that the version was not yet
   * obtained. An OpenGL context has to be created first.
   * 
   * \return OpenGL major version number.
   */
  inline static int getGlMajor() {
    return __glVersion.major;
  }
  
  /**
   * Gets OpenGL minor version number.
   * 
   * If this function returns -1, it means that the version was not yet
   * obtained. An OpenGL context has to be created first.
   * 
   * \return OpenGL minor version number.
   */
  inline static int getGlMinor() {
    return __glVersion.minor;
  }
  
  /**
   * \cond HIDDEN_DOC
   */
  GlBridge() = delete;
  /**
   * \endcond
   */
  
private:
  
  static void initVersion();
  static void initExtensions();
  
  static std::vector<std::string> __findExtensions();
  
  static struct glVersion {
    int major;
    int minor;
  } __glVersion;

};

/**
 * \internal
 */
namespace glExtensions {
  
  extern void   (*glActiveShaderProgram)(GLuint pipeline, GLuint program);
  extern void   (*glAttachShader)(GLuint program, GLuint shader);
    
  extern void   (*glCompileShader)(GLuint shader);
  extern GLuint (*glCreateShader)(GLenum shaderType);
  extern GLuint (*glCreateProgram)(void);
  
  extern void   (*glDeleteProgram)(GLuint program);
  extern void   (*glDeleteShader)(GLuint shader);
  extern void   (*glDetachShader)(GLuint program, GLuint shader);
  
  extern void   (*glGetProgramInfoLog)(GLuint program, GLsizei maxLength,
                                       GLsizei* length, GLchar* infoLog);
  extern void   (*glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
  extern void   (*glGetShaderInfoLog)(GLuint shader, GLsizei maxLength,
                                     GLsizei* length, GLchar* infoLog);
  extern void   (*glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
  extern void   (*glLinkProgram)(GLuint program);
    
  extern void   (*glShaderSource)(GLuint shader, GLsizei count,
                                 const GLchar** string, const GLint* length);
  
  void init();
  
} /* namespace glExtensions */
/**
 * \endinternal
 */

} /* namespace Dee */

#endif // GLBRIDGE_H
