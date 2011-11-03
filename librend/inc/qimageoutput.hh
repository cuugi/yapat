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

#ifndef _QIMAGEOUTPUT_HH
#define _QIMAGEOUTPUT_HH

#include <QImage>
#include <QString>

#include "output.hh"

namespace rend
{
  /**
   * Output wrapper class for Qt QImageWriter.
   *
   * \author cuugi(a)iki.fi
   */
  class qimageoutput : public output
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    qimageoutput( int aWidth, int aHeight, const char* aFilename );
    virtual ~qimageoutput();

  public: // from output

    void plotRGB( unsigned int aX, unsigned int aY, I aR, I aG, I aB );
    void plotColor( unsigned int aX, unsigned int aY, uni::color& aColor );
    uni::color color( unsigned int aX, unsigned int aY );
    unsigned int width() const;
    unsigned int height() const;
    void flush();
    void flush( const char* aFilename );

  private: // Attributes
    QString iFilename;
    QImage iImage;
  };

} // rend

#endif // _QIMAGEOUTPUT_HH
