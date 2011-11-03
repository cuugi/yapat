/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2005-2006 cuugi(a)iki.fi
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

#include <rand.hh>

#include "chessshader.hh"

namespace uni {

  chessshader::chessshader(const char* aName) 
    : surfaceshader(aName)
  {
  }
  
  chessshader::~chessshader()
  {
  }

  void chessshader::prepare()
  {
    // Nop
  }

  color chessshader::shade(color& aLight)
  {
    return COLOR_BLACK;
  }

  color chessshader::shade(shadercontext& aCtx)
  {
    bool black = ((int) ((aCtx.P[X] + 1000) * 2)) % 2 == 0;
    if (((int) ((aCtx.P[Z] + 1000) * 2)) % 2 == 0)
      black = !black;

    if (black)
      return aCtx.Ca * 0.3;
    return aCtx.Cl + aCtx.Ca;
  }

  vm::vector4<I> chessshader::nextRay(vm::vector4<I> aNormal, 
				      vm::vector4<I> aI)
  {
    // Normalize for dot
    /* vm::vector4<I> n = aNormal, i = aI;
    n.normalize();
    i.normalize();*/

    // Specular reflection
    if ((I) rand::ran(1) < 0.3)
      {
	return reflect(aI, aNormal);
      }

    // Diffuse reflection
    vm::vector4<I> ret;

    I r1 = 0, r2 = 0, r3 = 0;
    while (!(r1 || r2 || r3) || ret.dot(aNormal) < 0)
      {
	r1 = (I) rand::ran(1) - 0.5;
	r2 = (I) rand::ran(1) - 0.5;
	r3 = (I) rand::ran(1) - 0.5;
	ret = vm::vector4<I>(r1, r2, r3);
	ret.normalize();
      }
    ret *= aI.length();
    ret *= 0.8;
    
    return ret;
  }

} // uni
