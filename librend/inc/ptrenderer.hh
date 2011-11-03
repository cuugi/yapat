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

#ifndef _PTRENDERER_HH
#define _PTRENDERER_HH

#include <shader.hh>

#include "renderer.hh"

namespace rend
{
  /**
   * Monte Carlo ray tracer (path tracer).  A global illumination
   * rendering engine with all fancy features.
   *
   * @author cuugi(a)iki.fi
   */
  class ptrenderer : public renderer
  {
  public: // Constructors
    ptrenderer();
    virtual ~ptrenderer();

  public: // from renderer
    void render(renderingcontext* ctx, uni::camera* aCamera);

  public: // New (public) methods
    const uni::color trace(unsigned int aMaxDepth, uni::ray aRay, I t = 0.0,
		     uni::object* aSrc = NULL);

  protected: // Attributes
    uni::shadercontext shaderctx;
  };

} // rend

#endif // _PTRENDERER_HH
