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

#ifndef _OUTPUT_HH
#define _OUTPUT_HH

#include <universe.hh>

namespace rend
{
  /**
   * An abstract output class for rendering.
   *
   * \author cuugi(a)iki.fi
   */
  class output
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    output();
    virtual ~output() = 0;

  public: // New methods

    /**
     * Sets a color of a pixel.
     *
     * @param aX x coordinate
     * @param aY y coordinate
     * @param aR red value (0.0 - 1.0)
     * @param aG green value (0.0 - 1.0)
     * @param aB blue value (0.0 - 1.0)
     */
    virtual void plotRGB( unsigned int aX, unsigned int aY,
			 I aR, I aG, I aB ) = 0;

    virtual void plotColor( unsigned int aX, unsigned int aY,
    		uni::color& aColor ) = 0;

    /**
     * Returns a color of a pixel.
     *
     */
    virtual uni::color color( unsigned int aX, unsigned int aY ) = 0;

    /**
     * Returns output the image width.
     *
     * @return width
     */
    virtual unsigned int width() const = 0;

    /**
     * Returns output the image height.
     *
     * @return height
     */
    virtual unsigned int height() const = 0;

    /**
     * Flushes plotted pixels to a file / screen / something.
     */
    virtual void flush() = 0;

    /**
     * Flushes plotted pixels to a given file.
     */
    virtual void flush( const char* aFilename ) = 0;
  };

} // rend

#endif // _OUTPUT_HH
