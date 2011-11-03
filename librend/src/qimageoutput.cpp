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

#include <QColor>
#include <QImageWriter>

#include <universe.hh>

#include "qimageoutput.hh"

namespace rend
{

  qimageoutput::qimageoutput( int aWidth, int aHeight, const char* aFilename ) 
    : output(), iFilename( aFilename ), 
      iImage( aWidth, aHeight, QImage::Format_ARGB32 )
  {
  }

  qimageoutput::~qimageoutput()
  {
  }

  void qimageoutput::plotRGB( unsigned int aX, unsigned int aY, 
			      I aR, I aG, I aB )
  {
    QColor qc( aR * 0xff, aG * 0xff, aB * 0xff );
    iImage.setPixel( aX, aY, qc.rgb() );
  }

  void qimageoutput::plotColor( unsigned int aX, unsigned int aY, 
				uni::color& aColor )
  {
    QColor qc( aColor.iRed * 0xff, aColor.iGreen * 0xff, aColor.iBlue * 0xff );
    iImage.setPixel( aX, aY, qc.rgb() );
  }

  uni::color qimageoutput::color( unsigned int aX, unsigned int aY )
  {
    QRgb rgb = iImage.pixel( aX, aY );
    return uni::color( qRed( rgb ), qGreen( rgb ), qBlue( rgb ) );
  }

  unsigned int qimageoutput::width() const
  {
    return iImage.width();
  }

  unsigned int qimageoutput::height() const
  {
    return iImage.height();
  }

  void qimageoutput::flush()
  {
    QImageWriter writer( iFilename );
    writer.write( iImage );
  }

  void qimageoutput::flush( const char* aFilename )
  {
    QImageWriter writer( aFilename );
    writer.write( iImage );
  }

} // rend
