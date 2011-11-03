/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * no copyright,
 *   most of this is copied from perlin.h and perlin.c by Ken Perlin
 *
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

#ifndef _NOISETEST_HH
#define _NOISETEST_HH

#include <vmvector.hh>

#include <unibase.hh>
#include <shader.hh>

// Copy-paste from "perlin.h"
// -- clip --
#define B 0x100
#define BM 0xff
#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i,b0,b1,r0,r1)\
        t = vec[i] + N;\
        b0 = ((int)t) & BM;\
        b1 = (b0+1) & BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx,ry) ( rx * q[0] + ry * q[1] )
#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )
// -- clip --

namespace uni
{
  /**
   * A noise test shader.
   *
   * @author cuugi(a)iki.fi
   */
  class noisetest : public surfaceshader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    noisetest(const char* aName);
    virtual ~noisetest();

  public: // from unibase
    void prepare();

  public: // from surfaceshader
    vm::vector4<I> nextRay(vm::vector4<I> aNormal, vm::vector4<I> aI);
    color shade(color& aLight);
    color shade(shadercontext& aCtx);

    inline void print() { }

  public: // New methods

    I noise1(I arg);
    I noise2(I vec[2]);
    I noise3(I vec[3]);
    void normalize2(I v[2]);
    void normalize3(I v[3]);

    I noise(I x, I y, I z, I alpha, I beta, I n);

  private: // Attributes
    int p[B + B + 2];
    I g3[B + B + 2][3];
    I g2[B + B + 2][2];
    I g1[B + B + 2];
    int start;
  };

} // uni

#endif // _NOISETEST_HH

