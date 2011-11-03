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
#include <string.h>

#include "camera.hh"

namespace uni {

  camera::camera(const char* aName, vm::vector4<I> aDirection, vm::vector4<I> aUp)
    : unibase(), iLocation(), iDirection(aDirection),
      iUp(aUp) // 0.0, 1.0, 0.0, 1.0)
  {
    log::debug("camera::camera()");
    // TODO iUp

    iName = strdup(aName);
    //     iAspectRatio = 9.00 / 16.00; // 9:16
    iAspectRatio = 3.00 / 4.00;
    iFov = M_PI / 2;
    iNearPlane = 0.1;
    iFarPlane = -1; // Should be ignored
  }

  camera::~camera()
  {
    log::debug("camera::~camera()");

    delete iName;
  }

  int camera::translate(vm::vector4<I> aVec)
  {
    iLocation += aVec;

    return 0;
  }

  const char* camera::getName()
  {
    return iName;
  }

  vm::vector4<I> camera::getLocation()
  {
    return iLocation;
  }

  vm::vector4<I> camera::getDirection()
  {
    return iDirection;
  }

  vm::vector4<I> camera::getUp()
  {
    return iUp;
  }

  I camera::getAspectRatio()
  {
    return iAspectRatio;
  }

  I camera::getFov()
  {
    return iFov;
  }

  I camera::getNearPlane()
  {
    return iNearPlane;
  }

} // uni
