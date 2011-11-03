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

#ifndef _SURFACEOBJECT_HH
#define _SURFACEOBJECT_HH

#include <iostream>
#include <strings.h>

#include <log.hh>
#include <vmvector.hh>

#include "object.hh"
#include "ray.hh"
#include "shader.hh"

namespace uni
{
  /**
   * Base class for surfaceobjects.
   *
   * @author cuugi(a)iki.fi
   */
  class surfaceobject : public object
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    surfaceobject(const char* aName);
    virtual ~surfaceobject();

  public: // From unibase

  public: // From object

  public: // New Methods
    /**
     * Returns the surface shader.
     *
     * TODO param: facet
     */
    inline surfaceshader* getSurfaceShader()
    {
      return iSurface;
    }

    /**
     * Sets the surface shader.  Ownership is not transferred.
     */
    inline void setSurfaceShader(surfaceshader* aSurface)
    {
      iSurface = aSurface;
    }

    /**
     * Returns the surface normal at the given point.
     *
     * @param aPoint in universal coordinates
     */
    virtual vm::vector4<I> getNormal(vm::vector4<I>& aPoint, I t = 0.0) = 0;

  protected:
    // Shaders.  None of the shaders are owned by the surfaceobject.
    surfaceshader* iSurface;
    // DisplacementShader iDisplacement;
    // VolumeShader iVolume;
  };

} // uni

#endif // _SURFACEOBJECT_H
