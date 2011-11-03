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

#include "glassshader.hh"

namespace uni {

  glassshader::glassshader(const char* aName, I aRatio, I aReflect) 
    : surfaceshader(aName)
  {
    iRatio = aRatio;
    iReflect = aReflect;
  }
  
  glassshader::~glassshader()
  {
  }

  void glassshader::prepare()
  {
    // Nop
  }

  color glassshader::shade(color& aLight)
  {
    return COLOR_BLACK;
  }

  color glassshader::shade(shadercontext& aCtx)
  {
    return aCtx.Ca;
  }

  vm::vector4<I> glassshader::nextRay(vm::vector4<I> aNormal, 
				      vm::vector4<I> aI)
  {
    // Normalize for dot
    /* vm::vector4<I> n = aNormal, i = aI;
    n.normalize();
    i.normalize();*/

    if ((I) rand::ran(1) < iReflect)
      {
	// log::debug("reflect!!");
	return reflect(aI, aNormal);
      }

    // TODO iRatio should be calculated
    if (aNormal.dot(aI) < 0)
      return refract(aI, aNormal, iRatio);
    
    return refract(aI, aNormal, (I) 1/iRatio);
  }

} // uni
