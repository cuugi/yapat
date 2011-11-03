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

#include "mirrorshader.hh"

namespace uni {

  mirrorshader::mirrorshader(const char* aName, const color& aColor, 
			     I aRate, I aGlossy) 
    : surfaceshader(aName), iColor(aColor)
  {
    iRate = aRate;
    iGlossy = aGlossy;
  }
  
  mirrorshader::~mirrorshader()
  {
  }
  
  void mirrorshader::prepare()
  {
    // Nop
  }

  color mirrorshader::shade(color& aLight)
  {
    return iColor * (1.0 - iRate);
  }
  
  color mirrorshader::shade(shadercontext& aCtx)
  {
    return iColor * (1.0 - iRate) + aCtx.Ca;
  }


  vm::vector4<I> mirrorshader::nextRay(vm::vector4<I> aNormal, 
				       vm::vector4<I> aI)
  {
    vm::vector4<I> ret = reflect(aI * iRate, aNormal);
    if (iGlossy)
      {
	I l = ret.length();
	ret += vm::vector4<I>((I) rand::ran(1) * iGlossy * iRate,
			      (I) rand::ran(1) * iGlossy * iRate,
			      (I) rand::ran(1) * iGlossy * iRate);
	ret.setLength(l);
      }
    return ret;
  }

} // uni
