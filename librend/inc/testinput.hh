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

#ifndef _TESTINPUT_HH
#define _TESTINPUT_HH

#include <iostream>

#include "input.hh"

namespace rend
  {
    /**
     * Test input pipe.
     *
     * @author cuugi(a)iki.fi
     */
    class testinput : public input
      {
    public:
        // Constructors
        /**
         * Default constructor.
         */
        testinput();
        virtual ~testinput();

    public:
        // New methods

        /**
         * Returns a universe created by this input.
         */
        uni::universe getUniverse();

        /**
         * Returns a camera.
         */
        uni::camera* getCamera();

    private:
        // Attributes
        uni::camera* iCamera;
      };

  } // rend

#endif // _TESTINPUT_HH
