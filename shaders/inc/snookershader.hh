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

#ifndef _SNOOKERSHADER_HH
#define _SNOOKERSHADER_HH

#include <vmvector.hh>

#include <unibase.hh>
#include <shader.hh>

namespace uni
{
  /**
   * A snooker ball shader.
   *
   * @author cuugi(a)iki.fi
   */
  class snookershader : public surfaceshader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    snookershader(const char* aName, color aColor = COLOR_WHITE);
    virtual ~snookershader();

  public: // from unibase
    void prepare();

  public: // from surfaceshader
    vm::vector4<I> nextRay(vm::vector4<I> aNormal, vm::vector4<I> aI);
    color shade(color& aLight);
    color shade(shadercontext& aCtx);

    inline void print() { }

  private: // Attributes
    color iColor;
  };

} // uni

#endif // _SNOOKERSHADER_HH
