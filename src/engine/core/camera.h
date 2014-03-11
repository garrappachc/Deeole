/*
 * camera.h
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

#ifndef CAMERA_H
#define CAMERA_H

#include "core/deeglobal.h"

#include "core/point.h"
#include "core/modelviewmatrix.h"
#include "core/projectionmatrix.h"
#include "core/vector.h"

namespace Dee {
  
  class Scene;

/**
 * \ingroup Core
 * @{
 * 
 * The Camera class represents the viewpoint of the scene.
 * 
 * This class is used to set up proper matrices before the render process
 * of the current frame gets started. The Camera class implements the simplest
 * "TPP" view - 2-dimensional, without any perspective. One may subclass it
 * to have more complex views.
 * 
 * \sa FreeCamera and SphericalCamera.
 */
class __DeeExport__ Camera {
  
  friend class Scene;
  
public:
  
  /**
   * The default consructor.
   * 
   * The position of camera is (0, 0, 0) and the _lookAt_ vector is (0, 0, -1).
   * \sa move(), position() and lookAt().
   */
  Camera(
    Point3d eye = Point3d(0.0f, 0.0f, 0.0f),
    Vector3d lookAt = Vector3d(0.0f, 0.0f, 1.0f),
    Vector3d up = Vector3d(0.0f, 1.0f, 0.0f)
  );
  
  /**
   * The destructor.
   */
  virtual ~Camera();
  
  /**
   * Moves the camera to the given point.
   * 
   * \param eye The new _eye_ value.
   * \sa eye() and move().
   */
  void setEye(Point3d eye);
  
  /**
   * Moves the camera by the given vector.
   * 
   * This method differs from setEye(), however. Not only does it move the
   * camera respecting its current position, but it also can be implemented
   * differently for other types of camera. For example, calling move() method
   * on an instance of SphericalCamera will calculate the new _lookAt_ vector,
   * keeping its position still.
   * 
   * For this class, this method moves the _eye_ point by the given _vector_.
   * 
   * \param vector The movement vector.
   * \sa rotate() and SphericalCamera.
   */
  virtual void move(const Vector3d& vector);
  
  /**
   * Sets the _lookAt_ vector.
   * 
   * \param lookAt The new _lookAt_ value.
   * \sa lookAt() and rotate().
   */
  void setLookAt(Vector3d lookAt);
  
  /**
   * Modifies the _lookAt_ vector by adding this vector.
   * 
   * This method may behave differently for other camera types.
   * Foe example, calling rotate() on an instance of SphericalCamera will
   * modify both _lookAt_ and _eye_ attributes.
   * 
   * \param vector The rotation vector.
   * \sa move().
   */
  virtual void rotate(const Vector3d& vector);
  
  /**
   * Sets the _up_ vector.
   * 
   * \param up The new _up_ vector.
   * \sa up().
   */
  void setUp(Vector3d up);
  
  /**
   * Gives access to the position of the camera.
   * 
   * The _eye_ point describes the exact location of the camera.
   * 
   * \return The _eye_ point.
   * \sa setEye() and move().
   */
  inline const Point3d& eye() const {
    return __eye;
  }
  
  /**
   * Gives access to the position of the camera.
   * 
   * The _eye_ point describes the exact location of the camera.
   * 
   * \return The _eye_ point.
   * \sa setEye() and move().
   */
  inline Point3d& eye() {
    return __eye;
  }
  
  /**
   * Gives access to the _lookAt_ vector of the camera.
   * 
   * The _lookAt_ attribute describes the direction of the view of the
   * camera.
   * 
   * \return The _lookAt_ vector.
   * \sa setLookAt() and rotate().
   */
  inline const Vector3d& lookAt() const {
    return __lookAt;
  }
  
  /**
   * Gives access to the _lookAt_ vector of the camera.
   * 
   * The _lookAt_ attribute describes the direction of the view of the
   * camera.
   * 
   * \return The _lookAt_ vector.
   * \sa setLookAt() and rotate().
   */
  inline Vector3d& lookAt() {
    return __lookAt;
  }
  
  /**
   * Gives access to the _up_ vector.
   * 
   * The _up_ vector describes the angle between the camera and the ground.
   * The (0, 1, 0) vector is the right angle.
   * 
   * \return The _up_ vector.
   * \sa setUp().
   */
  inline const Vector3d& up() const {
    return __up;
  }
  
  /**
   * The _zNear_ parameter specifies the distance from the viewer to the near
   * clipping plane.
   * 
   * \return The camera's _zNear_ value.
   * \sa zFar().
   */
  inline float zNear() const {
    return __zNear;
  }
  
  /**
   * The _zFar_ parameter specifies the distance from the viewer to the far
   * clipping plane.
   * 
   * \return The camera's _zFar_ value.
   * \sa zNear().
   */
  inline float zFar() const {
    return __zFar;
  }
  
  /**
   * Provides direct access to the camera's current projection matrix.
   * 
   * \return The camera's projection matrix.
   * \sa modelViewMatrix().
   */
  inline const ProjectionMatrix& projectionMatrix() const {
    return __projectionMatrix;
  }
  
  /**
   * Provides direct access to the camera's current projection matrix.
   * 
   * \return The camera's projection matrix.
   * \sa modelViewMatrix().
   */
  inline ProjectionMatrix& projectionMatrix() {
    return __projectionMatrix;
  }
  
  /**
   * Provides direct access to the camera's current model-view matrix.
   * 
   * \return The camera's model-view matrix.
   * \sa projectionMatrix().
   */
  inline const ModelViewMatrix& modelViewMatrix() const {
    return __modelViewMatrix;
  }
  
  /**
   * Provides direct access to the camera's current model-view matrix.
   * 
   * \return The camera's model-view matrix.
   * \sa projectionMatrix().
   */
  inline ModelViewMatrix& modelViewMatrix() {
    return __modelViewMatrix;
  }
  
protected:
  
  /**
   * Prepares the _projection_ matrix.
   */
  virtual void setProjection();
  
  /**
   * Prepares the _modelview_ matrix.
   */
  virtual void setView();
  
private:
  
  Point3d  __eye;    /**< Camera position */
  Vector3d __lookAt; /**< LookAt vector */
  Vector3d __up;     /**< Up vector */
  
  ProjectionMatrix __projectionMatrix;
  ModelViewMatrix  __modelViewMatrix;
  
  float __zNear; /**< Specifies the distance from the viewer to the near
                       clipping plane (always positive). */
  float __zFar;  /**< Specifies the distance from the viewer to the far
                       clipping plane (always positive). */
  
}; /** @} */

} /* namespace Dee */

#endif // CAMERA_H
