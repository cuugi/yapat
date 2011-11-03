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

#ifndef _LIGHTRECT_HH
#define _LIGHTRECT_HH

#include "light.hh"
#include "plane.hh"

namespace uni
{
  /**
   * Light rect.
   *
   * @author cuugi(a)iki.fi
   */
  class lightrect : public plane, public arealight
  {
  public: // Constructors
    /**
     * Constructor.
     *
     * @param aR radius
     */
    lightrect(const char* aName, I aR = 1.0);
    virtual ~lightrect();

  public: // from unibase
    void prepare();

  public: // from object
    I trace(ray& aRay, bool aShadow = false);

  public: // from arealight
    vm::vector4<I> randomPointlight();
    I traceLight(ray& aRay);

  private: // Attributes
    I iR;

  };

} // uni

#endif // _LIGHTRECT_HH
