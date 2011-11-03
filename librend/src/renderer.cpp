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
#include <rand.hh>

#include <ray.hh>

#include "renderer.hh"

namespace rend
{
  renderer::renderer()
  {
    iUniverse = NULL;
    iBias = 0.0001;
  }

  renderer::~renderer()
  {
    iUniverse = NULL;
  }

  void renderer::setOutput(output* aOutput)
  {
    iOutput = aOutput;;
  }

  void renderer::setUniverse(uni::universe* aUniverse)
  {
    iUniverse = aUniverse;
  }

  uni::ray renderer::castRay(uni::camera* aCamera,
			     unsigned int aXN, unsigned int  aYN,
			     unsigned int aX, unsigned int aY,
			     unsigned int aXSeg, unsigned int aYSeg,
			     unsigned int aXSegI, unsigned int aYSegI,
			     bool aRandom)
  {
    // printf("x=%d/%d, y=%d/%d\n", aX, aXN, aY, aYN);

    // Init static variables
    vm::vector4<I> eye = aCamera->getLocation(),
      dir = aCamera->getDirection(),
      up = aCamera->getUp(),
      left = dir.cross(up); // Really left?
    I fov = aCamera->getFov(); // What? Why in use
    I np = aCamera->getNearPlane();

    // Normalize direction vectors
    dir.normalize();
    up.normalize(); up *= sin(fov/2);
    left.normalize(); left *= sin(fov/2);

    // Add random variable
    I r1 = 0, r2 = 0, max = 1.0;
    if (aRandom)
      {
	r1 = rand::ran(max); // (I) random() / RAND_MAX;
	r2 = rand::ran(max); // (I) random() / RAND_MAX;
      }

    // 1. component (-> near plane)
    vm::vector4<I> d1 = dir * np;
    d1.reset(); // Again, why is this needed?

    // 2. component (-> y)
    vm::vector4<I> d2 = up * np * aCamera->getAspectRatio();
    d2 *= (I) (aYN - aY + (r1 + aYSegI) / aYSeg)
      / aYN * 2 - 1;

    // 3. component (-> x)
    vm::vector4<I> d3 = left * np;
    d3 *= (I) (aXN - aX + (r2 + aXSegI) / aXSeg)
      / aXN * 2 - 1;
    /* printf("x: "); d3.print();
       printf("y: "); d2.print();*/

    vm::vector4<I> d = d1 + d2 + d3;
    vm::vector4<I> o = eye + d;
    d.normalize();
    /* d.print();
       printf("\n");*/

    return uni::ray(o, d);
  }

  I renderer::visible(vm::vector4<I> aPoint, uni::arealight* aLight,
		      vm::vector4<I>* aLightPoint, I aT)
  {
    std::list<uni::surfaceobject*> objects = iUniverse->objects();
    vm::vector4<I>
      // pl(0.21, 1.0, 0.5), // Above the ball
      pl = aLight->randomPointlight(),
      d = pl, d2, o;
    d -= aPoint;

    d2 = d; // TODO onliner
    d2.normalize();
    d2 *= iBias;
    d2.reset();
    o = aPoint;
    o += d2;

    // trace
    I t = d.length();
    d.normalize();
    std::list<uni::surfaceobject*>::iterator iter = objects.begin();
    while (iter != objects.end())
      {
	uni::ray r;
	r.setOrigin(o);
	r.setDirection(d);
	I t2 = (*iter)->trace(r, false, aT);
	if (t2 > 0 && t2 < t - 2*iBias)
	  {
	    /* pl.print();
	    o.print(); */
	    // printf("t2 = %.2f/%.2f (%s)\n", t2, t, (*iter)->getName());
	    return 0;
	  }

	iter++;
      }

    if (aLightPoint != NULL) (*aLightPoint) = pl;
    return t;

  }

  testrenderer::testrenderer()
  {
  }

  testrenderer::~testrenderer()
  {
  }

  void testrenderer::render(renderingcontext* ctx, uni::camera* aCamera)
  {
    log::debug("testrenderer::render(%s)", aCamera->getName());

    std::list<uni::surfaceobject*> objects = iUniverse->objects();
    std::list<uni::arealight*> lights = iUniverse->arealights();
    I ls = lights.size();
    unsigned int n = 4; // number of samples per axis

    // Print universe
    std::list<uni::surfaceobject*>::iterator iter = objects.begin();
    printf("Camera:\n aspect ratio = %f\n fov = %f\n np = %f\n",
	   aCamera->getAspectRatio(),
	   aCamera->getFov(),
	   aCamera->getNearPlane());
    printf("Objects:\n");
    while (iter != objects.end())
      {
	printf(" [%s]\n", (*iter)->getName());
	iter++;
      }

    unsigned int width = iOutput->width();
    unsigned int height = iOutput->height();
    for (unsigned int y = 0; y < height; y++)
      {
	for (unsigned int x = 0; x < width; x++)
	  {

	    for (unsigned int sampX = 0; sampX < n; sampX++) {
	      for (unsigned int sampY = 0; sampY < n; sampY++) {
		// ray
		uni::ray r;
		r = castRay(aCamera, width, height,
			    x, y, n, n, sampX, sampY, true);

		// trace
		uni::surfaceobject* obj = NULL;
		I t = -1;
		iter = objects.begin();
		int obi = 0, obk = 0;
		while (iter != objects.end())
		  {
		    uni::ray r2(r); // TODO trace(const r)
		    I t2 = (*iter)->trace(r2);
		    if (t > t2 && t2 > 0 || t < 0)
		      {
			t = t2;
			obj = (*iter);
			obk = obi;
		      }
		    iter++;
		    obi++;
		  }

		// p
		vm::vector4<I> p = r.getDirection();
		p *= t;
		p += r.getOrigin();
		p.reset(); // This is needed, but why?

		// sample
		uni::color c = iOutput->color(x, y);
		if (obj != NULL && t > 0)
		  {
		    std::list<uni::arealight*>::iterator liter =
		      lights.begin();

		    while (liter != lights.end())
		      {
			if (visible(p, (*liter)))
			  {
			    c.iRed += 1/(n*n*ls)/(t>1?t:1); // TODO /nlights
			    c.iGreen += 1/(n*n*ls)/(t>1?t:1); // TODO /nlights
			    c.iBlue += 1/(n*n*ls)/(t>1?t:1); // TODO /nlights
			  }
			liter++;
		      }
		  }
		iOutput->plotColor(x, y, c);
	      }
	    }
	  }
      }

    return;
  }
} // rend

