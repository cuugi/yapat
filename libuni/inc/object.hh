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

#ifndef _OBJECT_HH
#define _OBJECT_HH

#include <iostream>

#include <log.hh>
#include <vmmatrix.hh>
#include <vmvector.hh>

#include "ray.hh"
#include "unibase.hh"

#ifndef INFINITY
#define INFINITY 10000 // TODO: No-no-no-no-no!
#endif

namespace uni
{

  class box;
  class surfaceshader;

  /**
   * Base class for universe objects.
   *
   * @author cuugi(a)iki.fi
   */
  class object : public unibase
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    object(const char* aName);
    virtual ~object() = 0;

  public: // From unibase
    // TODO: Give a stream to print in
    void printRenderman();

  public: // New Methods
    /**
     * Returns unibase object type.
     *
     */
    unitype getType()
    {
      return UT_OBJECT;
    }

    /**
     * Translates.
     */
    void translate(vm::vector4<I> aVec);

    /**
     * Rotates.
     *
     * @param angle angle in radians
     */
    void rotate(I angle, vm::vector4<I> aVec);

    /**
     * Returns the name.
     */
    inline const char* getName()
    {
      return iName;
    }

    /**
     * Returns a bounding box for the object.
     *
     * @param t time
     */
    virtual box getBoundingBox(I t = 0.0) = 0;

    /**
     * Trace a ray.
     *
     * @param aRay a ray to trace
     * @param aShadow is a shadow ray? (this parameter can be used to
     *        ignore the object in shadow ray checks by making it
     *	      invisible)
     * @param t time
     * @return distance (relative to the length of ray) to the closest
     *         surface, can only be negative if positive values are not
     *         available (when the nearest surface is behind the ray)
     */
    virtual I trace(ray& aRay, bool aShadow = false, I t = 0.0) = 0;

  protected:
    /** The object name */
    char* iName; // TODO: Move to unibase

    /** The object location */
    vm::vector4<I> iLocation;

    /** The object transformation */
    vm::matrix4x4<I> iTransformation;

    // TODO: In surfaceobject?
    // Shaders.  None of the shaders are owned by the object.
    // DisplacementShader iDisplacement;
    // VolumeShader iVolume;
  };

} // uni


#endif // _OBJECT_H
