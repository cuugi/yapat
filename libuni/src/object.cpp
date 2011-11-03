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
#include <string.h>

#include "object.hh"
#include "shader.hh"
#include "box.hh"

namespace uni {

  object::object(const char* aName)
    : unibase()
  {
    log::debug("object::object(%s)", aName);

    iName = strdup(aName);
  }

  object::~object()
  {
    log::debug("object::~object(%s)", iName);

    delete iName;
  }

  void object::translate(vm::vector4<I> aVec)
  {
    iLocation += aVec;
  }

  void object::rotate(I angle, vm::vector4<I> aVec)
  {
    I a = (1 - cos(angle));
    I b = sin(angle);
    vm::matrix4x4<I> r(1 + a*(aVec[X]*aVec[X] - 1),
		       a*aVec[X]*aVec[Y] - aVec[Z]*b,
		       a*aVec[X]*aVec[Z] + aVec[Y]*b, 0,

		       a*aVec[X]*aVec[Y] + aVec[Z]*b,
		       1 + a*(aVec[Y]*aVec[Y] - 1),
		       a*aVec[Y]*aVec[Z] - aVec[X]*b, 0,

		       a*aVec[X]*aVec[Z] - aVec[Y]*b,
		       a*aVec[Y]*aVec[Z] + aVec[X]*b,
		       1 + a*(aVec[Z]*aVec[Z] - 1), 0,

		       0, 0, 0, 1);
    iTransformation *= r;
  }

  void object::printRenderman()
  {
    // cout << "Translate " << iLocation;
  }
}
