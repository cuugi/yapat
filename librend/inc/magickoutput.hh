/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2006-2009 cuugi(a)iki.fi
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

#ifndef _MAGICKOUTPUT_HH
#define _MAGICKOUTPUT_HH

#include <string>

#include <Magick++.h>

#include "output.hh"

namespace rend
{
  /**
   * Output wrapper class for Magick++.
   *
   * @author cuugi(a)iki.fi
   */
  class magickoutput : public output
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    magickoutput(const char* aSize, const char* aBackground, const char* aFilename);
    virtual ~magickoutput();

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
    void plotRGB(unsigned int aX, unsigned int aY, I aR, I aG, I aB);

    void plotColor(unsigned int aX, unsigned int aY, uni::color& aColor);

    /**
     * Returns a color of a pixel.
     *
     */
    uni::color color(unsigned int aX, unsigned int aY);

    /**
     * Returns output the image width.
     *
     * @return width
     */
    unsigned int getWidth();

    /**
     * Returns output the image height.
     *
     * @return height
     */
    unsigned int getHeight();

    /**
     * Flushes plotted pixels to a file / screen / something.
     */
    void flush();

    /**
     * Flushes plotted pixels to a given file.
     */
    void flush(const char* aFilename);

  private: // Attributes
    std::string iFilename;
    Magick::Image iImage;
  };

} // rend

#endif // _OUTPUT_HH
