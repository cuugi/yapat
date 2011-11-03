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

#ifndef _SPHERE_HH
#define _SPHERE_HH

#include <log.hh>
#include <vmvector.hh>

#include "surfaceobject.hh"

namespace uni
{

  class box;

  /**
   * Sphere.
   *
   * @author cuugi(a)iki.fi
   */
  class sphere : public surfaceobject
  {
  public: // Constructors
    /**
     * Constructor.
     *
     * @param aR radius
     * @param aV velocity vector
     */
    sphere(const char* aName, I aR = 1.0,
    		vm::vector4<I> aV = VECT_ZERO,
    		I aZMin = -1.0, I aZMax = 1.0,
    		I aSweepAngle = 2 * M_PI);
    virtual ~sphere();

  public: // from object
    box getBoundingBox(I t = 0.0);
    I trace(ray& aRay, bool aShadow = false, I t = 0.0);
    void prepare();

  public: // from surfaceobject
    vm::vector4<I> getNormal(vm::vector4<I>& aPoint, I t = 0.0);

  protected:
    I iR;
    vm::vector4<I> iV;
    I iZMin;
    I iZMax;
    I iSweepAngle;

    // Cached values
    vm::vector4<I> iTransLocation;
  };
} // uni

#endif // _SPHERE_HH
