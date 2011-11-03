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

#ifndef _ENVMAP_HH
#define _ENVMAP_HH

#include <log.hh>

#include <vmvector.hh>

#include "shader.hh"
#include "unibase.hh"

namespace uni
{

  /**
   * Abstract environment map class.
   *
   * @author cuugi(a)iki.fi
   */
  class envmap : public unibase
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    envmap();
    virtual ~envmap() = 0;

  public: // New methods
    /**
     * Returns environment map color for the given point.
     *
     * @param aRay a ray towards the environment
     */
    virtual color shade(ray aRay) = 0;
  };

  /**
   * Test envmap impl.
   */
  class testenvmap : public envmap
  {
  public: // Constructors
    testenvmap();
    ~testenvmap();

  public: // from unibase
    void prepare();

  public: // New methods
    color shade(ray aRay);

  private: // Attributes
    vm::vector4<I> iDir;
  };

} // uni

#endif // _ENVMAP_HH
