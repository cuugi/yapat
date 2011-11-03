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

#ifndef _SHADER_HH
#define _SHADER_HH

#include <vmvector.hh>

#include "unibase.hh"
#include "ray.hh"

namespace uni
{
  class shadercontext
  {
  public:

    /** Surface position in world coordinates. (RenderMan) */
    vm::vector4<I> P;

    /** Surface shading normal. (RenderMan) */
    vm::vector4<I> N;

    /** Surface geometric normal. (RenderMan) */
    vm::vector4<I> Ng;

    /** Incoming light ray direction.  Not normalized. (RenderMan) */
    vm::vector4<I> L;

    /** Incoming light ray color. (RenderMan) */
    color Cl;

    /** Incoming ambient light ray direction.  Not normalized. */
    vm::vector4<I> A;

    /** Incoming ambient light ray color. */
    color Ca;

    /** Eye position. (RenderMan) */
    vm::vector4<I> E;
  };

  /**
   * Base class for shaders.
   *
   * @author cuugi(a)iki.fi
   */
  class shader : public unibase
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    shader(const char* aName);
    virtual ~shader() = 0;

  public: // New methods
    const char* getName()
    {
      return iName;
    }

  protected:
    /** The shader name */
    char* iName; // TODO: Move to unibase
  };

  /**
   * Base class for light shaders.
   *
   * @author cuugi(a)iki.fi
   */
  class lightshader : public shader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    lightshader(const char* aName);
    virtual ~lightshader() = 0;

  public: // from unibase
    virtual void prepare() = 0;

  public: // New methods
    /**
     * Shade.  Does not do shadow checks.
     */
    virtual color shade(vm::vector4<I> aPoint, vm::vector4<I> aLightPoint) = 0;

    /**
     * Returns light shader color.
     */
    virtual color getLightColor() = 0;
  };

  /**
   * Distance based colored light.
   *
   * @author cuugi(a)iki.fi
   */
  class distancelightshader : public lightshader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    distancelightshader(const char* aName, const color& aColor, bool aLinear = false);
    ~distancelightshader();

  public: // from unibase
    void prepare();

  public: // from lightshader
    color shade(vm::vector4<I> aPoint, vm::vector4<I> aLightPoint);
    color getLightColor();

  private:
    color iColor;
    bool iLinear;
  };

  /**
   * Base class for surface shaders.
   *
   * @author cuugi(a)iki.fi
   */
  class surfaceshader : public shader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    surfaceshader(const char* aName);
    virtual ~surfaceshader() = 0;

  public: // from unibase
    virtual void prepare() = 0;

  public: // New methods
    /**
     * Returns refraction / reflection ray.
     *
     * @param aI incoming ray
     * @return outgoing ray (length = 0.0 - 1.0)
     */
    virtual vm::vector4<I> nextRay(vm::vector4<I> aN, vm::vector4<I> aI) = 0;

    /**
     * Shade.
     */
    virtual color shade(color& aLight) = 0;

    /**
     * Shade.
     */
    virtual color shade(shadercontext& aCtx) = 0;

    virtual void print() = 0;

  public: // Geometric shader functions defined by RenderMan
    /**
     * Returns reflection vector.
     */
    vm::vector4<I> reflect(vm::vector4<I> aI, vm::vector4<I> aN);

    /**
     * Returns refraction vector.
     */
    vm::vector4<I> refract(vm::vector4<I> aI, vm::vector4<I> aN, I aEta);
  };

  /**
   * An ideal (Lambertian) diffuse surface shader.
   *
   * @author cuugi(a)iki.fi
   */
  class basicshader : public surfaceshader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    basicshader(const char* aName, const color& aColor, I aKd = 0.5);
    ~basicshader();

  public: // from unibase
    void prepare();

  public: // from surfaceshader
    vm::vector4<I> nextRay(vm::vector4<I> aNormal, vm::vector4<I> aI);
    color shade(color& aLight);
    color shade(shadercontext& aCtx);
    inline void print()
    {
      iColor.print();
    }

  private: // Attributes
    color iColor;
    I iKd;
  };

  /**
   * Ignores all incoming light.
   *
   * @author cuugi(a)iki.fi
   */
  class colorshader : public surfaceshader
  {
  public: // Constructors
    /**
     * Default constructor.
     */
    colorshader(const char* aName, const color& aColor);
    ~colorshader();

  public: // from unibase
    void prepare();

  public: // from surfaceshader
    vm::vector4<I> nextRay(vm::vector4<I> aNormal, vm::vector4<I> aI);
    color shade(color& aLight);
    color shade(shadercontext& aCtx);
    inline void print()
    {
      iColor.print();
    }

  private: // Attributes
    color iColor;
  };

} // uni

#endif // _SHADER_HH
