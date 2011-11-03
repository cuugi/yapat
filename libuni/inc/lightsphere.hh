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

#ifndef _LIGHTSPHERE_HH
#define _LIGHTSPHERE_HH

#include "light.hh"
#include "sphere.hh"

namespace uni
{
  /**
   * Light sphere.
   *
   * @author cuugi(a)iki.fi
   */
  class lightsphere : public sphere, public arealight
  {
  public: // Constructors
    /**
     * Constructor.
     *
     * @param aR radius
     */
    lightsphere(const char* aName, I aR = 1.0);
    virtual ~lightsphere();

  public: // from unibase
    void prepare();

  public: // from object
    I trace(ray& aRay, bool aShadow = false);

  public: // from arealight
    vm::vector4<I> randomPointlight();
    I traceLight(ray& aRay);

  };

} // uni

#endif // _LIGHTSPHERE_HH
