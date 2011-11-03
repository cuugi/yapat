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

#include <universe.hh>

#include "magickoutput.hh"

namespace rend
{

  magickoutput::magickoutput(const char* aSize, const char* aBackground,
			     const char* aFilename) : output(),
    iFilename(aFilename), iImage(aSize, aBackground)
  {
  }

  magickoutput::~magickoutput()
  {
  }

  void magickoutput::plotRGB(unsigned int aX, unsigned int aY,
			     I aR, I aG, I aB)
  {
    Magick::ColorRGB mc(aR, aG, aB);
    iImage.pixelColor(aX, aY, mc);
  }

  void magickoutput::plotColor(unsigned int aX, unsigned int aY, uni::color& aColor)
  {
    Magick::ColorRGB mc(aColor.iRed, aColor.iGreen, aColor.iBlue);
    iImage.pixelColor(aX, aY, mc);
  }

  uni::color magickoutput::color(unsigned int aX, unsigned int aY)
  {
    Magick::ColorRGB c = iImage.pixelColor(aX, aY);
    return uni::color(c.red(), c.green(), c.blue());
  }

  unsigned int magickoutput::getWidth()
  {
    Magick::Geometry size = iImage.size();
    return size.width();
  }

  unsigned int magickoutput::getHeight()
  {
    Magick::Geometry size = iImage.size();
    return size.height();
  }

  void magickoutput::flush()
  {
    iImage.write(iFilename);
  }


  void magickoutput::flush(const char* aFilename)
  {
    iImage.write(aFilename);
  }
}
