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

#include "snookershader.hh"

namespace uni {

  snookershader::snookershader(const char* aName, color aColor) 
    : surfaceshader(aName)
  {
    iColor = aColor;
  }
  
  snookershader::~snookershader()
  {
  }

  void snookershader::prepare()
  {
    // Nop
  }

  color snookershader::shade(color& aLight)
  {
    // Not implemented
    return COLOR_BLACK;
  }

  color snookershader::shade(shadercontext& aCtx)
  {
    return aCtx.Cl * iColor + aCtx.Ca * 0.7;
  }
  
  vm::vector4<I> snookershader::nextRay(vm::vector4<I> aNormal, 
					vm::vector4<I> aI)
  {
    return reflect(aI, aNormal) * 0.7;
  }

} // uni
