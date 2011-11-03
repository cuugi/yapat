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

#include "lightrect.hh"

namespace uni {

  lightrect::lightrect(const char* aName, I aR) :
    plane(aName, vm::vector4<I>(0.0, -1.0, 0.0)), arealight()
  {
    // TODO plane normal!
    iR = aR;
  }

  lightrect::~lightrect()
  {
  }

  void lightrect::prepare()
  {
    vm::vector4<I> tmp = iLocation;
    plane::prepare();
    iLocation = tmp; // TODO No-no-no-no-noooo!
  }

  I lightrect::trace(ray& aRay, bool aShadow)
  {
    // TODO use the matrix && iTransLocations!
    if (aShadow) return -1;
    I r = plane::trace(aRay, aShadow);

    if (r < 0) return r;

    vm::vector4<I> p = aRay.getDirection(); // TODO optimize
    p.normalize();
    p *= r / aRay.getDirection().length();
    p.reset();
    p += aRay.getOrigin();
    /* printf("dl = %.2f, r = %.2f, y1 = %.2f, y2 = %.2f\n",
       aRay.getDirection().length(), r, p[Y], iTransLocation[Y]); */

    if (p[X] < iLocation[X] - iR || p[X] > iLocation[X] + iR ||
	p[Z] < iLocation[Z] - iR || p[Z] > iLocation[Z] + iR)
      return -1;
    // p.print();

    return r;
  }

  vm::vector4<I> lightrect::randomPointlight()
  {
    // TODO use the matrix!
    I x = 0, z = 0;
    x = rand::ran(iR) - (iR / 2.00);
    z = rand::ran(iR) - (iR / 2.00);

    vm::vector4<I>
      r(x, 0, z);
    // r = iTransformation * r;
    r += iLocation;
    return r;
  }

  I lightrect::traceLight(ray& aRay)
  {
    return trace(aRay, false);
  }

} // uni
