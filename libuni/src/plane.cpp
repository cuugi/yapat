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
#include "plane.hh"
#include "box.hh"

namespace uni {

  plane::plane(const char* aName)
    : surfaceobject(aName), iNormal(0.0, 1.0, 0.0, 1.0)
  {
    // log::debug("plane::plane()");
  }

  plane::plane(const char* aName,
	       const vm::vector4<I>& aNormal)
    : surfaceobject(aName), iNormal(aNormal)
  {
    // log::debug("plane::plane()");
  }

  plane::~plane()
  {
    // log::debug("plane::~plane()");
  }

  box plane::getBoundingBox(I t)
  {
    // TODO transform
    box ret("bb",
	    vm::vector4<I>((iNormal[1] || iNormal[2]) ? -INFINITY : 0.0,
			   (iNormal[0] || iNormal[2]) ? -INFINITY : 0.0,
			   (iNormal[0] || iNormal[1]) ? -INFINITY : 0.0),
	    vm::vector4<I>((iNormal[1] || iNormal[2]) ? INFINITY : 0.0,
			   (iNormal[0] || iNormal[2]) ? INFINITY : 0.0,
			   (iNormal[0] || iNormal[1]) ? INFINITY : 0.0)
	    );
    ret.translate(iLocation);
    return ret;
  }

  I plane::trace(ray& aRay, bool aShadow, I t)
  {
    // TODO discplacementshader

     // TODO does not work, something wrong with the _d_?
    register I a = iTransNormal[X], b = iTransNormal[Y],
      c = iTransNormal[Z], d = iTransDist;

    vm::vector4<I> rd = aRay.getDirection();
    register I i = rd[X],
      j = rd[Y],
      k = rd[Z];

    register I div = a*i + b*j + c*k;
    if (div >= 0)
      return -1; // Ray does not hit the plane

    vm::vector4<I> ro = aRay.getOrigin();
    register I x1 = ro[X],
      y1 = ro[Y],
      z1 = ro[Z];
    // printf("a=%.2f b=%.2f c=%.2f d=%.2f x1=%.2f y1=%.2f z1=%.2f -> %.2f\n",
    //        a, b, c, d, x1, y1, z1, -(a*x1 + b*y1 + c*z1 + d) / div);
    return -(a*x1 + b*y1 + c*z1 + d) / div;
  }

  vm::vector4<I> plane::getNormal(vm::vector4<I>& aPoint, I t)
  {
    return iTransformation * iNormal;
  }

  void plane::prepare()
  {
    // log::debug("plane::prepare()");
    iLocation = vm::vector4<I>(0, iLocation[Y], 0); // Ignore all but Y .. uh, extending classes will be broken

    iTransNormal = iTransformation * iNormal;
    iTransLocation = iTransformation * iLocation;
    iTransDist = iTransLocation.length();
  }

} // uni
