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

#include <rand.hh>

#include "shader.hh"

namespace uni {

  shader::shader(const char* aName) : unibase()
  {
    iName = strdup(aName);
  }

  shader::~shader()
  {
    delete iName;
  }

  lightshader::lightshader(const char* aName)
    : shader(aName)
  {
  }

  lightshader::~lightshader()
  {
  }

  distancelightshader::distancelightshader(const char* aName,
					   const color& aColor, bool aLinear)
    : lightshader(aName)
  {
    iColor = aColor;
    iLinear = aLinear;
  }

  distancelightshader::~distancelightshader()
  {
  }

  void distancelightshader::prepare()
  {
    // Nop
  }

  color distancelightshader::shade(vm::vector4<I> aPoint, vm::vector4<I> aLightPoint)
  {
    // light *= 1/(dist>1.00 ? dist : 1.00);
    I dist = (aPoint - aLightPoint).length();
    if (iLinear)
      return iColor * (1 / (dist > 1.00 ? dist : 1.00));
    else
      return iColor * (1 / (dist > 1.00 ? dist * dist : 1.00));
  }

  color distancelightshader::getLightColor()
  {
    // Always white
    return iColor; // COLOR_WHITE;
  }

  surfaceshader::surfaceshader(const char* aName)
    : shader(aName)
  {
  }

  surfaceshader::~surfaceshader()
  {
  }

  vm::vector4<I> surfaceshader::reflect(vm::vector4<I> aI, vm::vector4<I> aN)
  {
    I il = aI.length();
    // printf("\nin (%.2f): ", il); aI.print();
    // printf("n: "); aN.print();

    // calculate angles
    aI.normalize(); aI *= -1; aI.reset();
    aN.normalize();
    I dot = aI.dot(aN); // , in = dot;
    // I out = in = acos(in); // angle in

    // refrection vector
    vm::vector4<I> ret = aN * 2 * dot - aI;
    ret *= il;
    ret.reset();
    // printf("out (%.2f): ", ret.length()); ret.print();
    return ret;
  }


  vm::vector4<I> surfaceshader::refract(vm::vector4<I> aI, vm::vector4<I> aN,
					I aEta)
  {
    I il = aI.length();
    // printf("\nin (%.2f): ", il); aI.print();

    // calculate angles
    aI.normalize();
    aN.normalize();
    I dot = aI.dot(aN), in = dot;
    if (in < 0)
      {
	in = -in; // cos(angle in)
      }
    else
      {
	aN *= -1;
      }
    in = acos(in); // angle in
    I out = (I) 1/aEta * sin(in);
    out = asin(out); // angle out

    // refraction vector
    vm::vector4<I> m = (aN * cos(in) + aI) * (1 / sin(in));
    vm::vector4<I> ret = m * sin(out) - aN * cos(out);
    ret *= il;
    ret.reset();
    // printf("out (%.2f): ", ret.length()); ret.print();
    return ret;
  }

  basicshader::basicshader(const char* aName, const color& aColor, I aKd)
    : surfaceshader(aName), iColor(aColor)
  {
    iKd = aKd;
  }

  basicshader::~basicshader()
  {
  }

  void basicshader::prepare()
  {
    // Nop
  }

  color basicshader::shade(color& aLight)
  {
    return iColor * aLight;
  }

  color basicshader::shade(shadercontext& aCtx)
  {
    return iColor * (aCtx.Cl + aCtx.Ca);
  }

  vm::vector4<I> basicshader::nextRay(vm::vector4<I> aNormal, vm::vector4<I> aI)
  {
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
    ret *= iKd;

    return ret;
  }

  colorshader::colorshader(const char* aName, const color& aColor)
    : surfaceshader(aName), iColor(aColor)
  {
  }

  colorshader::~colorshader()
  {
  }

  void colorshader::prepare()
  {
  }

  color colorshader::shade(color& aLight)
  {
    return iColor; // Ignore aLight
  }

  color colorshader::shade(shadercontext& aCtx)
  {
    return iColor;
  }


  vm::vector4<I> colorshader::nextRay(vm::vector4<I> aNormal,
				      vm::vector4<I> aI)
  {
    vm::vector4<I> ret; // zero vector
    return ret;
  }

} // uni
