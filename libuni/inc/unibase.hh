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

#ifndef _UNIBASE_HH
#define _UNIBASE_HH

#include <log.hh>

#include "unicontext.hh"

namespace uni
{

#ifndef I
#define I double
#endif // I

  enum unitype {
    UT_LIGHT = 1,
    UT_OBJECT,
    UT_CAMERA,
    UT_UNKNOWN = 999
  };

  struct color {
    color(I aRed = 1.0, I aGreen = 1.0, I aBlue = 1.0)
    {
      iRed = aRed;
      iGreen = aGreen;
      iBlue = aBlue;
    }

    inline color operator+(const color& b) const
    {
      return color(b.iRed + iRed, b.iGreen + iGreen, b.iBlue + iBlue);
    }

    inline color operator*(const color& b) const
    {
      return color(b.iRed * iRed, b.iGreen * iGreen, b.iBlue * iBlue);
    }

    inline color operator*(const I n) const
    {
      return color(iRed * n, iGreen * n, iBlue * n);
    }

    inline void operator+=(const color& b)
    {
      iRed += b.iRed;
      iGreen += b.iGreen;
      iBlue += b.iBlue;
    }

    inline void operator*=(const I n)
    {
      iRed *= n;
      iGreen *= n;
      iBlue *= n;
    }

    inline void operator/=(const I n)
    {
      iRed /= n;
      iGreen /= n;
      iBlue /= n;
    }

    inline bool isValid() const
    {
      // TODO do inf and nan checks
      return
	iRed >= 0 && iRed <= 10000 &&
	iGreen >= 0 && iGreen <= 10000 &&
	iBlue >= 0 && iBlue <= 10000;
    }

    inline void print() const
    {
      printf("(%.2f, %.2f, %.2f)\n", iRed, iGreen, iBlue);
    }

    I iRed; // Value 0.0 - 1.0
    I iGreen;
    I iBlue;
  };

  const color COLOR_WHITE(1.0, 1.0, 1.0);
  const color COLOR_BLACK(0.0, 0.0, 0.0);
  const vm::vector4<I> VECT_ZERO(0.0, 0.0, 0.0);

  /**
   * Base class for all objects attached to a universe.
   *
   * @author cuugi(a)iki.fi
   */
  class unibase
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    unibase() { iContext = NULL; }
    virtual ~unibase() { };

  public: // New Methods
    /**
     * Returns unibase object type.
     */
    unitype getType();

    /**
     * Sets the universe context object.
     */
    void setContext(unicontext* aContext) { iContext = aContext; }

    /**
     * This is called before rendering.  The object should do
     * optimization - for instance calculate constants that otherwise
     * would be calculated in every <code>trace()</code> call.
     */
    virtual void prepare() = 0;

  private: // Attributes
    unicontext* iContext;
  };

}

#endif // _UNIBASE_H
