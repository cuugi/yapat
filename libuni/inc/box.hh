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

#ifndef _BOX_HH
#define _BOX_HH

#include <log.hh>
#include <vmvector.hh>

#include "object.hh"

namespace uni
{

  /**
   * A box.
   *
   * @author cuugi(a)iki.fi
   */
  class box : public object
  {
  public: // Constructors
    /**
     * Constructor.
     */
    box(const char* aName,
    		const vm::vector4<I> aCorner1,
    		const vm::vector4<I> aCorner2);
    virtual ~box();

  public: // from object
    box getBoundingBox(I t = 0.0);
    I trace(ray& aRay, bool aShadow = false, I t = 0.0);
    void prepare();

  private: // Attributes
    vm::vector4<I> iCorner[2];
  };

} // uni

#endif // _BOX_HH
