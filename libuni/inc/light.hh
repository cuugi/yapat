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

#ifndef _LIGHT_HH
#define _LIGHT_HH

#include "shader.hh"
#include "surfaceobject.hh"
#include "unibase.hh"

namespace uni
{
  /**
   * Light.
   *
   * @author cuugi(a)iki.fi
   */
  class light : public unibase
  {
  public: // Constructors
    /**
     * Constructor.
     */
    light();
    virtual ~light() = 0;

  public: // New Methods
    /**
     * Returns the light shader.
     */
    inline lightshader* getLightShader()
    {
      return iLight;
    }

    /**
     * Sets the light shader.  Ownership is not transferred.
     */
    inline void setLightShader(lightshader* aLight)
    {
      iLight = aLight;
    }

  private: // Attributes
    lightshader* iLight;
  };

  /**
   * Area (or volume?) light.
   *
   * @author cuugi(a)iki.fi
   */
  class arealight : public light
  {
  public: // Constructors
    /**
     * Constructor.
     */
    arealight();
    virtual ~arealight() = 0;

  public: // New methods
    /**
     * Returns a random point light on the area light surface.
     *
     * TODO change to return pointlight
     */
    virtual vm::vector4<I> randomPointlight() = 0;

    /**
     * Trace a ray.
     *
     * @param aRay
     * @param distance
     */
    virtual I traceLight(ray& aRay) = 0;

  };

} // uni

#endif // _LIGHT_HH
