/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2009 cuugi(a)iki.fi
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

#ifndef _NULLOUTPUT_HH
#define _NULLOUTPUT_HH

#include <output.hh>

namespace rend
{
  /**
   * Test output class for rendering.  Everything will be discarded.
   *
   * \author cuugi(a)iki.fi
   */

	class nulloutput : public output
	{
	public: // Constructors
		/**
		 * Default constructor.
		 */
		nulloutput();
		virtual ~nulloutput();

	public: // from output
    void plotRGB(unsigned int aX, unsigned int aY, I aR, I aG, I aB);
    void plotColor(unsigned int aX, unsigned int aY, uni::color& aColor);
    uni::color color(unsigned int aX, unsigned int aY);
    unsigned int width() const;
    unsigned int height() const;
    void flush();
    void flush(const char* aFilename);

	};

} // rend

#endif // _NULLOUTPUT_HH
