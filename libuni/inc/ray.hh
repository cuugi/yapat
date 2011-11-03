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

#ifndef _RAY_HH
#define _RAY_HH

#include <log.hh>
#include <vmvector.hh>

#include "shader.hh"
#include "unibase.hh"

namespace uni
{
  /**
   * A ray (of light).
   *
   * @author cuugi(a)iki.fi
   */
  class ray : public unibase
  {
  public: // Constructors
    /**
     * Defaults constructor.
     */
    inline ray() {};

    /**
     * Constructor.
     */
    inline ray(const vm::vector4<I>& aOrigin,
    		const vm::vector4<I>& aDirection,
    		const color& aColor = COLOR_WHITE)
    {
      iOrigin = aOrigin;
      iDirection = aDirection;
      iColor = aColor;
    }

    /**
     * Copy constructor.
     */
    inline ray(const ray& aRay)
    {
      iOrigin = aRay.iOrigin;
      iDirection = aRay.iDirection;
      iColor = aRay.iColor;
    }

    inline ~ray() {};

  public: // from unibase
    inline void prepare()
    {
      // Nop
    }

  public: // New methods
    /**
     * Returns the ray origin.
     */
    inline vm::vector4<I> getOrigin()
    {
      return iOrigin;
    }

    /**
     * Sets the ray origin.
     */
    inline void setOrigin(const vm::vector4<I>& aOrigin)
    {
      iOrigin = aOrigin;
    }

    /**
     * Returns the ray direction.
     */
    inline vm::vector4<I> getDirection()
    {
      return iDirection;
    }

    /**
     * Sets the ray direction.
     */
    inline void setDirection(const vm::vector4<I>& aDirection)
    {
      iDirection = aDirection;
    }

    /**
     * Returns the ray color.
     */
    inline color getColor()
    {
      return iColor;
    }

    /**
     * Sets the ray color.
     */
    inline void setDirection(const color aColor)
    {
      iColor = aColor;
    }

    /**
     * Normalize direction vector.
     */
    inline void normalize()
    {
      iDirection.normalize();
    }

    inline void print()
    {
      iOrigin.print();
      iDirection.print();
    }

  private:
    /** The ray origin. */
    vm::vector4<I> iOrigin;

    /** The ray direction. */
    vm::vector4<I> iDirection;

    /** The ray color. */
    color iColor;

  };

} // uni


#endif // _RAY_HH
