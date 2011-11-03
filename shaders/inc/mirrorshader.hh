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

#ifndef _MIRRORSHADER_HH
#define _MIRRORSHADER_HH

#include <vmvector.hh>

#include <unibase.hh>
#include <shader.hh>

namespace uni
{

  /**
   * A mirror shader.
   *
   * @author cuugi(a)iki.fi
   */
  class mirrorshader : public surfaceshader
  {
  public: // Constructors
    /**
     * Default constructor.
     *
     * @param aName shader name
     * @param aColor mirror color
     * @param aRate reflection rate (0.0 - 1.0)
     * @param aGlossy surface glossiness (0.0 - 1.0)
     */
    mirrorshader( const char* aName, const color& aColor,
    		I aRate = 1.0, I aGlossy = 0.0 );
    virtual ~mirrorshader();

  public: // from unibase
    void prepare();

  public: // from surfaceshader
    vm::vector4<I> nextRay(vm::vector4<I> aNormal, vm::vector4<I> aI);
    color shade(color& aLight);
    color shade(shadercontext& aCtx);

    inline void print() { }

  private: // Attributes
    color iColor;
    I iRate;
    I iGlossy;
  };

} // uni

#endif // _MIRRORSHADER_HH
