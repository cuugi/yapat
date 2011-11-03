/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2005-2009 cuugi(a)iki.fi
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _CAMERA_HH
#define _CAMERA_HH

#include <iostream>
#include <math.h>

#include <log.hh>
#include <vmvector.hh>

#include "unibase.hh"

namespace uni
{

  enum unicamtype {
    UCT_ORTHOGRAPHIC = 1,
    UCT_PERSPECTIVE
  };

  /**
   * Simple camera.
   *
   * @author cuugi(a)iki.fi
   */
  class camera : public unibase
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    camera(const char* aName,
    		vm::vector4<I> aDirection = vm::vector4<I>(0.0, 0.0, 1.0, 1.0),
    		vm::vector4<I> aUp = vm::vector4<I>(0.0, 1.0, 0.0, 1.0));
    virtual ~camera();

  public: // from unibase
    inline void prepare()
    {
      // Nop
    }

  public: // New Methods
    /**
     * Returns unibase camera type.
     *
     */
    inline unitype getType()
    {
      return UT_CAMERA;
    }

    /**
     * Translate.
     */
    int translate(vm::vector4<I> aVec);

    /**
     * Returns the camera name.
     */
    const char* getName();

    /**
     * Returns the camera location vector.
     */
    vm::vector4<I> getLocation();

    /**
     * Returns the camera direction vector.
     */
    vm::vector4<I> getDirection();

    /**
     * Returns the camera up vector.
     */
    vm::vector4<I> getUp();

    /**
     * Returns the camera aspect ratio.
     */
    I getAspectRatio();

    /**
     * Returns the camera field of view. (in radians)
     */
    I getFov();

    /**
     * Returns the camera near clipping plane.
     */
    I getNearPlane();

  protected:
    char* iName;

    vm::vector4<I> iLocation;
    vm::vector4<I> iDirection;
    vm::vector4<I> iUp;

    /** Camera specific aspect ratio. (in decimals) */
    I iAspectRatio;

    /** Field of view. (in radians) */
    I iFov;

    /** Near clipping plane. */
    I iNearPlane;

    /** Far clipping plane. */
    I iFarPlane;
  };

} // uni

#endif // _CAMERA_H
