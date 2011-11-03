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
#include "envmap.hh"

namespace uni {

  envmap::envmap() : unibase()
  {
  }

  envmap::~envmap()
  {
  }

  testenvmap::testenvmap() : envmap()
  {
    iDir = vm::vector4<I>(0.7, 0.8, -0.2);
  }

  testenvmap::~testenvmap()
  {
  }

  void testenvmap::prepare()
  {
    // Nop
  }

  color testenvmap::shade(ray aRay)
  {
    vm::vector4<I> d = aRay.getDirection();
    I dot = d.dot(iDir * d.length());
    if (dot < 0.8) return color(0.0, 0.0, 0.0);
    return color(1.0, 1.0, 1.0) * d.length() * (1.00 - dot);
  }

} // uni

