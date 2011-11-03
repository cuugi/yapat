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

#include <stdlib.h>

#include <log.hh>
#include <metrix.hh>
#include <rand.hh>

#include <ray.hh>
#include <shader.hh>
#include <unibase.hh>

#include "ptrenderer.hh"

namespace rend
{

  ptrenderer::ptrenderer()
  {
  }

  ptrenderer::~ptrenderer()
  {
  }

  void ptrenderer::render(renderingcontext* ctx, uni::camera* aCamera)
  {
    iUniverse->prepare();

    // Variables, TODO --> ctx
    unsigned int width = iOutput->width();
    unsigned int height = iOutput->height();
    unsigned int n = 3; // number of samples per axis
    unsigned int depth = 5;
    I shutter = 0.4; // s
    unsigned int tenp = height * width * n * n / 10;
    unsigned int p = 0;

    for (unsigned int y = 0; y < height; y++)
      {
      for (unsigned int x = 0; x < width; x++)
	{
	  long mid = metrix::start("ptrenderer");
	  uni::color c(0.0, 0.0, 0.0);
	  for (unsigned int sampX = 0; sampX < n; sampX++)
	    for (unsigned int sampY = 0; sampY < n; sampY++, p++)
	      {

		// status
		if (p % tenp == 0)
		  {
		    printf("%d percent ready\n", p/tenp*10);
		    iOutput->flush();
		  }

		// create a sample ray
		uni::ray r;
		r = castRay(aCamera, width, height,
			    x, y, n, n, sampX, sampY, true);

		// path trace
		I t = rand::ran(shutter); // TODO + t0
		uni::color sample =
		  trace(depth, r, t); // TODO configure depth

		if (sample.isValid())
		  c += sample;

	      }

	  c /= n*n;
	  if (c.iRed > 1.0) c.iRed = 1.0;
	  if (c.iGreen > 1.0) c.iGreen = 1.0;
	  if (c.iBlue > 1.0) c.iBlue = 1.0;
	  iOutput->plotColor(x, y, c);

	  metrix::stop(mid);
	}
      }
  }

  const uni::color ptrenderer::trace(unsigned int aMaxDepth, uni::ray aRay, I aT,
			       uni::object* aSrc)
  {
    uni::color c(0, 0, 0);
    std::list<uni::surfaceobject*> objects = iUniverse->objects();
    std::list<uni::arealight*> lights = iUniverse->arealights();
    // I numlights = lights.size();
    vm::vector4<I> zero;
    I t = -1;

    // trace arealights, TODO aT
    uni::arealight* alight = NULL;
    std::list<uni::arealight*>::iterator liter = lights.begin();
    while (liter != lights.end())
      {
	uni::ray r2(aRay);
	r2.normalize();
	I t2 = (*liter)->traceLight(r2);
	if ( ( t > t2 && t2 > iBias ) || t < iBias )
	  {
	    t = t2;
	    alight = (*liter);
	  }
	liter++;
      }

    // trace objects
    uni::surfaceobject* obj = NULL;
    std::list<uni::surfaceobject*>::iterator oiter = objects.begin();
    while (oiter != objects.end())
      {
	if (*oiter == aSrc)
	  {
	  oiter++;
	  continue;
	  }
	uni::ray r2(aRay);
	r2.normalize();
	I t2 = (*oiter)->trace(r2, true, aT);
	if ( ( t > t2 && t2 > iBias ) || t < iBias )
	  {
	    t = t2;
	    obj = (*oiter);
	  }
	oiter++;
      }

    // yes arealight
    if (obj == NULL && alight != NULL)
      {
	// point of intersection
	vm::vector4<I> lp = aRay.getDirection();
	lp.normalize();
	lp *= t;
	lp += aRay.getOrigin();
	lp.reset(); // This is needed, but why?

	// TODO use surface shaders, THIS IS NOT GOOD!
	uni::lightshader* ls = alight->getLightShader();
	return ls->getLightColor(); // ls->shade(lp, aRay.getOrigin());
      }

    // no object
    if (obj == NULL || t < iBias)
      {
	// TODO not good, environment maps should be added in a shader
	uni::envmap* em = iUniverse->getEnvironmentMap();
	if (em != NULL)
	  return c + em->shade(aRay);
	return c;
      }

    // point of intersection
    vm::vector4<I> p = aRay.getDirection();
    p.normalize();
    p *= t;
    p += aRay.getOrigin();
    p.reset(); // This is needed, but why?
    shaderctx.P = p;

    // normal of obj at intersection
    vm::vector4<I> n = obj->getNormal(p, aT);
    shaderctx.N = shaderctx.Ng = n; // TODO: What about dispacement shaders?

    // cast shadow rays
    uni::surfaceshader* ss = obj->getSurfaceShader();
    liter = lights.begin();
    shaderctx.A = zero;
    shaderctx.Ca = uni::COLOR_BLACK;
    while (liter != lights.end())
      {
	vm::vector4<I> pl; // TODO light point
	I dist = visible(p, (*liter), &pl, aT);
	if (dist > 0)
	  {
	    // calculate pixel color  TODO use surfaceshaders with lightshaders
	    uni::color light =
	      (*liter)->getLightShader()->shade(p, pl);
	    shaderctx.L = p - pl;
	    shaderctx.Cl = light;
	    c += ss->shade(shaderctx) * aRay.getDirection().length();
	  }
	liter++;
      }

    // cast next ray
    if (aMaxDepth - 1 > 0)
      {
	vm::vector4<I>
	  dir = ss->nextRay(n, aRay.getDirection()),
	  d2 = dir;
	d2.normalize();
	p += d2 * iBias;
	// p.reset();
        // dir.reset();
	uni::ray next(p, dir, uni::COLOR_WHITE);

	// trace reflected
	shaderctx.Ca = trace(aMaxDepth - 1, next, aT);
	shaderctx.A = zero - dir;
	shaderctx.P = p;
	shaderctx.N = shaderctx.Ng = n;
	shaderctx.L = zero;
	shaderctx.Cl = uni::COLOR_BLACK;
	c += ss->shade(shaderctx) * next.getDirection().length();
      }

    /* printf("(%d)", aMaxDepth); c.print();
    if (aMaxDepth == 2) printf("\n"); */
    return c;
  }

} // rend
