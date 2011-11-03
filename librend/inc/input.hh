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

#ifndef _INPUT_HH
#define _INPUT_HH

#include <universe.hh>

namespace rend
  {
    /**
     * Abstract input class for rendering.
     *
     * @author cuugi(a)iki.fi
     */
    class input
      {
    public:
        // Constructors
        /**
         * Default constructor.
         */
        input();
        virtual ~input() = 0;

    public:
        // New methods

        /**
         * Returns a universe created by this input.
         */
        virtual uni::universe getUniverse() = 0;

        /**
         * Returns a camera.
         */
        virtual uni::camera* getCamera() = 0;

      };

  } // rend

#endif // _INPUT_HH
