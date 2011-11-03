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

#ifndef _RENDERER_HH
#define _RENDERER_HH

#include <math.h>

#include <log.hh>

#include <universe.hh>

#include "output.hh"

namespace rend
{
  class renderingcontext;

  /**
   * Abstract renderer base class.
   *
   * @author cuugi(a)iki.fi
   */
  class renderer
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    renderer();
    virtual ~renderer() = 0;

  public: // New methods
    /**
     * Sets rendering output.
     */
    void setOutput(output* aOutput);

    /**
     * Sets rendering universe.
     */
    void setUniverse(uni::universe* aUniverse);

    /**
     * Render.
     */
    virtual void render(renderingcontext* ctx, uni::camera* aCamera) = 0;

    /**
     * Creates a ray for the given image coordinates.
     *
     * @param aX image x-position
     * @param aY image y-position
     * @param aXSeg number of x-segments in a pixel
     * @param aYSeg number of y-segments in a pixel
     * @param aXSegI x-segment index
     * @param aYSegI y-segment index
     * @param aRandom use stochastic sampling?
     */
    uni::ray castRay(uni::camera* aCamera,
		     unsigned int aXN, unsigned int aYN,
		     unsigned intaX, unsigned int aY,
		     unsigned int aXSeg = 1, unsigned int aYSeg = 1,
		     unsigned int aXSegI = 0, unsigned int aYSegI = 0,
		     bool aRandom = true);

    /**
     * Check visibility between a point and an area light.
     *
     * @return distance, or -1 if no visibility
     */
    I visible(vm::vector4<I> aPoint, uni::arealight* aLight,
	      vm::vector4<I>* aLightPoint = NULL, I aT = 0.0);

  protected: // Attributes
    /** A reference to an output image. */
    output* iOutput;

    /** A reference to the universe. */
    uni::universe* iUniverse;

    /** Bias. */
    I iBias;
  };

  /** Rendering context. */
  class renderingcontext
  {
  public: // Constructors
  };

  /** Test renderer impl. */
  class testrenderer : public renderer
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    testrenderer();
    ~testrenderer();

  public: // from renderer
    void render(renderingcontext* ctx, uni::camera* aCamera);
  };

} // rend

#endif // _RENDERER_HH
