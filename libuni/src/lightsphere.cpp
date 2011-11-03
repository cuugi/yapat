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
#include <stdlib.h>

#include <log.hh>
#include <rand.hh>
#include <vmvector.hh>

#include "lightsphere.hh"

namespace uni {

  lightsphere::lightsphere(const char* aName, I aR) :
    sphere(aName, aR), arealight()
  {
    // Nop?
  }

  lightsphere::~lightsphere()
  {
  }

  void lightsphere::prepare()
  {
    // log::debug("lightsphere::prepare()");
    // iTransLocation.print();
    sphere::prepare();
    // iTransLocation.print();
  }

  I lightsphere::trace(ray& aRay, bool aShadow)
  {
    if (aShadow) return -1;
    return sphere::trace(aRay, aShadow);
  }

  vm::vector4<I> lightsphere::randomPointlight()
  {
    I r1 = 0, r2 = 0, r3 = 0;
    while (!(r1 || r2 || r3))
      {
        r1 = (I) rand::ran(1) / RAND_MAX - 0.5;
        r2 = (I) rand::ran(1) / RAND_MAX - 0.5;
        r3 = (I) rand::ran(1) / RAND_MAX - 0.5;
      }

    vm::vector4<I>
      r(r1, r2, r3);
    r.normalize();
    r *= iR;
    r += iLocation;
    return r;
  }

  I lightsphere::traceLight(ray& aRay)
  {
    return trace(aRay, false);
  }

} // uni
