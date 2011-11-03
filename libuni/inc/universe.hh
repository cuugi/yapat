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

#ifndef _UNIVERSE_HH
#define _UNIVERSE_HH

#include <list>
#include <map>

#include <log.hh>

#include "camera.hh"
#include "envmap.hh"
#include "light.hh"
#include "surfaceobject.hh"
#include "shader.hh"
#include "unibase.hh"

namespace uni
{

  /**
   * The universe uniobject container.
   *
   * @author cuugi(a)iki.fi
   */
  class universe
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    universe();

    /**
     * Constructor with environment map.
     */
    universe(envmap* aEnvMap);
    virtual ~universe();

  public: // New methods
    /**
     * Attaches an object to the universe.  The ownership of the
     * object is transferred to the universe.
     *
     * TODO support for other objects as well
     *
     * @return number of objects in the universe
     */
    int attach(surfaceobject* aObject);

    /**
     * Attachs a camera to the universe.  The ownership of the camera
     * is transferred to the universe.
     *
     * @return number of cameras in the universe
     */
    int attach(camera* aCamera);

    /**
     * Attaches a shader to the universe.  The ownership of the shader
     * is transferred to the universe.
     *
     * @return number of shaders in the universe
     */
    int attach(shader* aShader);

    /**
     * Attaches a area light source to the universe.  The ownership of
     * the shader is transferred to the universe.
     *
     * @return number of shaders in the universe
     */
    int attach(arealight* aArealight);

    /**
     * Returns a shader by name
     *
     * @return shader, or NULL if not found
     */
    shader* getShader(const char* aName);

    /**
     * Returns the environment map.
     */
    inline envmap* getEnvironmentMap()
    {
      return iEnvMap;
    }

    /**
     * Returns objects.
     */
    std::list<surfaceobject*> objects();

    /**
     * Returns area lights.
     */
    std::list<arealight*> arealights();

    /**
     * Prepares objects and lights for rendering.
     */
    void prepare();

  private: // Data structures
    std::list<surfaceobject*> iObjects;
    std::list<camera*> iCameras;
    std::list<shader*> iShaders;
    std::list<arealight*> iArealights;

    std::map<const char*, shader*> iNameShader;

  private: // Other objects
    envmap* iEnvMap;
  };

} // uni

#endif // _UNIVERSE_HH
