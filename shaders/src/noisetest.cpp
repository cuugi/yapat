/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2006 cuugi(a)iki.fi - not really, 
 *   most of this is copied from perlin.h and perlin.c by Ken Perlin
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

#include <stdlib.h>

#include <rand.hh>

#include "noisetest.hh"

namespace uni {

  noisetest::noisetest(const char* aName) 
    : surfaceshader(aName)
  {
    start = 1;
  }
  
  noisetest::~noisetest()
  {
  }

  void noisetest::prepare()
  {
    int i, j, k;
    
    for (i = 0 ; i < B ; i++) {
      p[i] = i;
      g1[i] = (double)((rand::ran(1) % (B + B)) - B) / B;
      
      for (j = 0 ; j < 2 ; j++)
        g2[i][j] = (double)((rand::ran(1) % (B + B)) - B) / B;
      normalize2(g2[i]);
      
      for (j = 0 ; j < 3 ; j++)
        g3[i][j] = (double)((rand::ran(1) % (B + B)) - B) / B;
      normalize3(g3[i]);
    }
    
    while (--i) {
      k = p[i];
      p[i] = p[j = rand::ran(1) % B];
      p[j] = k;
    }
    
    for (i = 0 ; i < B + 2 ; i++) {
      p[B + i] = p[i];
      g1[B + i] = g1[i];
      for (j = 0 ; j < 2 ; j++)
	g2[B + i][j] = g2[i][j];
      for (j = 0 ; j < 3 ; j++)
	g3[B + i][j] = g3[i][j];
    }
  }
  
  color noisetest::shade(color& aLight)
  {
    return aLight;
  }
  
  color noisetest::shade(shadercontext& aCtx)
  {
    // TODO should be "surface position in locale coordinates", not "world"
    color c = aCtx.Cl;
    I n = noise(aCtx.P[X], aCtx.P[Y], aCtx.P[Z], 1.5, 1, 2);
    // printf("noise(%.2f, %.2f, %.2f): %.2f\n", aCtx.P[X], aCtx.P[Y], aCtx.P[Z], n);
    return c * n + aCtx.Ca;
  }
  
  vm::vector4<I> noisetest::nextRay(vm::vector4<I> aNormal, 
				    vm::vector4<I> aI)
  {
    // Specular reflection
    return reflect(aI, aNormal) * 0.7;
  }

  I noisetest::noise1(I arg)
  {
    int bx0, bx1;
    I rx0, rx1, sx, t, u, v, vec[1];
    
    vec[0] = arg;
    
    setup(0,bx0,bx1,rx0,rx1);
    
    sx = s_curve(rx0);
    u = rx0 * g1[ p[ bx0 ] ];
    v = rx1 * g1[ p[ bx1 ] ];
    
    return(lerp(sx, u, v));
  }
  
  I noisetest::noise2(I vec[2])
  {
    int bx0, bx1, by0, by1, b00, b10, b01, b11;
    I rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
    int i, j;
    
    setup(0, bx0,bx1, rx0,rx1);
    setup(1, by0,by1, ry0,ry1);
    
    i = p[ bx0 ];
    j = p[ bx1 ];
    
    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];
    
    sx = s_curve(rx0);
    sy = s_curve(ry0);
    
    q = g2[ b00 ] ; u = at2(rx0,ry0);
    q = g2[ b10 ] ; v = at2(rx1,ry0);
    a = lerp(sx, u, v);
    
    q = g2[ b01 ] ; u = at2(rx0,ry1);
    q = g2[ b11 ] ; v = at2(rx1,ry1);
    b = lerp(sx, u, v);
    
    return lerp(sy, a, b);
  }
  
  I noisetest::noise3(I vec[3])
  {
    int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
    I rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
    int i, j;
    
    setup(0, bx0,bx1, rx0,rx1);
    setup(1, by0,by1, ry0,ry1);
    setup(2, bz0,bz1, rz0,rz1);
    
    i = p[ bx0 ];
    j = p[ bx1 ];
    
    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];
    
    t  = s_curve(rx0);
    sy = s_curve(ry0);
    sz = s_curve(rz0);
    
    q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
    q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
    a = lerp(t, u, v);
    
    q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
    q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
    b = lerp(t, u, v);
    
    c = lerp(sy, a, b);
    
    q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
    q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
    a = lerp(t, u, v);
    
    q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
    q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
    b = lerp(t, u, v);
    
    d = lerp(sy, a, b);
    
    return lerp(sz, c, d);
  }
  
  void noisetest::normalize2(I v[2])
  {
    I s;
    
    s = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] = v[0] / s;
    v[1] = v[1] / s;
  }
  
  void noisetest::normalize3(I v[3])
  {
    I s;
    
    s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] = v[0] / s;
    v[1] = v[1] / s;
    v[2] = v[2] / s;
  }
  
  I noisetest::noise(I x, I y, I z, I alpha, I beta, I n)
  {
    int i;
    I val,sum = 0;
    I p[3],scale = 1;
    
    p[0] = x;
    p[1] = y;
    p[2] = z;
    for (i=0;i<n;i++) {
      val = noise3(p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
      p[2] *= beta;
    }
    return(sum);
  }
} // uni
