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
#include "sphere.hh"
#include "box.hh"

namespace uni {

  sphere::sphere(const char* aName, I aR, vm::vector4<I> aV,
		 I aZMin, I aZMax, I aSweepAngle) : surfaceobject(aName)
  {
    // log::debug("sphere::sphere()");

    iR = aR;
    iV = aV;
    iZMin = aZMin;
    iZMax = aZMax;
    iSweepAngle = aSweepAngle;
  }

  sphere::~sphere()
  {
    // log::debug("sphere::~sphere()");
  }

  box sphere::getBoundingBox(I t)
  {
    // TODO: Apply displacement shader
    box ret("bb", vm::vector4<I>(-iR, -iR, -iR),
	    vm::vector4<I>(iR, iR, iR));
    ret.translate(iLocation);
    ret.translate(iV * t);
    return ret;
  }

  I sphere::trace(ray& aRay, bool aShadow, I t)
  {
    // TODO discplacementshader, iZMin, iZMax, iSweepAngle
    // TODO direction vector should be normalized for optimization,
    //      then a = 1

    vm::vector4<I>
      ro = aRay.getOrigin(),
      rd = aRay.getDirection(),
      loc = iTransLocation + iV * t;
    register I x1 = ro[X],
      y1 = ro[Y],
      z1 = ro[Z];
    register I i = rd[X],
      j = rd[Y],
      k = rd[Z];
    register I a = i*i + j*j + k*k,
      b = 2 * ((x1 - loc[X])*i +
	       (y1 - loc[Y])*j +
	       (z1 - loc[Z])*k),
      c = (x1 - loc[X])*(x1 - loc[X]) +
      (y1 - loc[Y])*(y1 - loc[Y]) +
      (z1 - loc[Z])*(z1 - loc[Z]) - iR*iR;

    register I dis = b*b - 4*a*c;
    if (dis < 0)
      return -1;  // The ray does not hit the sphere

    I s = sqrt(dis);
    I t1 = (-b + s) / (2*a),
      t2 = (-b - s) / (2*a);

    if (t1 < 0 && t2 < 0)
      return t1 > t2 ? t1 : t2;
    if ((t2 > t1 || t2 < 0) && t1 > 0)
      return t1;
    return t2;
  }

  vm::vector4<I> sphere::getNormal(vm::vector4<I>& aPoint, I t)
  {
    vm::vector4<I> ret = aPoint;
    ret -= iLocation + iV * t;
    ret.normalize();
    return ret;
  }

  void sphere::prepare()
  {

    iTransLocation = iTransformation * iLocation;
  }

} // uni
