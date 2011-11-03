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

#ifndef _VMVECTOR_HH
#define _VMVECTOR_HH

#include <iostream>
#include <math.h>
#include <stdio.h>

#include <log.hh>

namespace vm {

  template <class t>
  class matrix4x4;

  /**
   * 3d vector with a scalar n.
   *
   */
  template <class t>
  class vector4
  {
  public: // Constructors
    /**
     * Defaults constructor.
     */
    inline vector4()
    {
      iVal[0] = 0;
      iVal[1] = 0;
      iVal[2] = 0;
      iVal[3] = 1.0;
      normalized = false;
    };

    /**
     * Constructor.
     */
    inline vector4(t a0, t a1, t a2, t n = 1.0)
    {
      iVal[0] = a0;
      iVal[1] = a1;
      iVal[2] = a2;
      iVal[3] = n;
      normalized = false;
    }

    /**
     * Copy constructor.
     */
    inline vector4(const vector4& b)
    {
      iVal[0] = b.iVal[0];
      iVal[1] = b.iVal[1];
      iVal[2] = b.iVal[2];
      iVal[3] = b.iVal[3];
      normalized = b.normalized;
    }

    virtual ~vector4()
    {
      // log::debug("vector4::~vector4()");
    }

  public: // New methods
    /**
     * Returns the vector length.
     *
     * @param n use n?
     * @return length
     */
    double length(bool n = true);

    /**
     * Sets the vector length.  Direction is not changed.
     *
     * @param l new length
     */
    void setLength(t l);

    /**
     * Normalize vector.
     *
     * @param reset n? (default = true, false is faster);
     */
    void normalize(bool res = true);

    /**
     * Resets n to 1.0.
     */
    void reset();

    /**
     * Calculates the dot product.
     *
     * @param n use n?
     */
    t dot(const vector4& b, bool n = true);

    /**
     * Calculates the cross product.
     *
     * @param n use n?
     */
    vector4 cross(const vector4& b, bool n = true);

    /**
     * Calculates the angle between vectors.
     *
     * @param b vector b, TODO: -> const
     * @return angle in radians
     */
    double angle(vector4& b);

    /**
     * Print the vector to a stream.
     *
     * TODO: give the stream as a parameter
     */
    inline void print()
    {
      printf("(%.2f, %.2f, %.2f, %.2f)\n",
	     iVal[0], iVal[1], iVal[2], iVal[3]);
    }

  public: // New operators
    vector4 operator+(const vector4& b);
    vector4 operator-(const vector4& b);
    vector4 operator*(const t x);

    void operator+=(const vector4& b);
    void operator-=(const vector4& b);
    void operator*=(const t x);

    bool operator==(const vector4& b);

    vector4 operator*(matrix4x4<t>& m);
    t operator[](int i);
    // void operator<<(std::basic_ostream out);

  private:
    /** Vector parameters. */
    t iVal[4];
    /** Is vector normalized?  Length of iVal[0-2] == 1. */
    bool normalized;
  };

}

/*** Methods ***/
#include "vmmatrix.hh"

namespace vm {

  template <class t>
  double vector4<t>::length(bool n)
  {
    if (n && normalized)
      return iVal[3];

    // = sqrt(x^2 + y^2 + z^2)
    t s = n ? iVal[3] : 1.0;
    return sqrt(iVal[0] * iVal[0] +
		iVal[1] * iVal[1] +
		iVal[2] * iVal[2]) * s;
  }

  template <class t>
  void vector4<t>::setLength(t l)
  {
    if (!normalized) normalize();
    iVal[3] = l;
  }

  template <class t>
  void vector4<t>::normalize(bool res)
  {
    if (normalized) return; // Don't bother
    t x = 1 / length(false);

    if (res) { // n = 1.0
      iVal[0] = iVal[0] * x;
      iVal[1] = iVal[1] * x;
      iVal[2] = iVal[2] * x;
      iVal[3] = 1.0;
      normalized = true;

    } else { // only n is changed
      iVal[3] = iVal[3] / x;
    }
  }

  template <class t>
  void vector4<t>::reset()
  {
    if (iVal[3] == 0) return; // Don't bother

    t s = iVal[3];

    iVal[0] *= s;
    iVal[1] *= s;
    iVal[2] *= s;
    iVal[3] = 1.0;
    normalized = false;
  }

  template <class t>
  t vector4<t>::dot(const vector4& b, bool n)
  {
    // = |a||b|cos(a, b)
    if (n)
      {
	t s = iVal[3] * b.iVal[3];

	return (iVal[0] * b.iVal[0] +
		iVal[1] * b.iVal[1] +
		iVal[2] * b.iVal[2]) * s;
      }
    return iVal[0] * b.iVal[0] +
      iVal[1] * b.iVal[1] +
      iVal[2] * b.iVal[2] +
      iVal[3] * b.iVal[3];
  }

  template <class t>
  vector4<t> vector4<t>::cross(const vector4& b, bool n)
  {
    t s = n ? iVal[3] * b.iVal[3] : 1.0;

    return vector4<t>((iVal[1] * b.iVal[2] - iVal[2] * b.iVal[1]) * s,
		      (iVal[2] * b.iVal[0] - iVal[0] * b.iVal[2]) * s,
		      (iVal[0] * b.iVal[1] - iVal[1] * b.iVal[0]) * s,
		      1.0);
  }

  template <class t>
  double vector4<t>::angle(vector4& b)
  {
    // = a dot b / |a||b|
    return acos(dot(b) / (length() * b.length()));
  }

  template <class t>
  vector4<t> vector4<t>::operator+(const vector4& b)
  {
    t s = iVal[3] / b.iVal[3];
    return vector4<t>(iVal[0] + b.iVal[0] / s,
		      iVal[1] + b.iVal[1] / s,
		      iVal[2] + b.iVal[2] / s,
		      iVal[3]);
  }

  template <class t>
  vector4<t> vector4<t>::operator-(const vector4& b)
  {
    t s = iVal[3] / b.iVal[3];
    return vector4<t>(iVal[0] - b.iVal[0] / s,
		      iVal[1] - b.iVal[1] / s,
		      iVal[2] - b.iVal[2] / s,
		      iVal[3]);
  }

  template <class t>
  vector4<t> vector4<t>::operator*(const t x)
  {
    return vector4(iVal[0], iVal[1], iVal[2], iVal[3] * x);
  }

  template <class t>
  void vector4<t>::operator+=(const vector4& b)
  {
    t s = iVal[3] / b.iVal[3];
    iVal[0] += b.iVal[0] / s;
    iVal[1] += b.iVal[1] / s;
    iVal[2] += b.iVal[2] / s;
    normalized = false;
  }

  template <class t>
  void vector4<t>::operator-=(const vector4& b)
  {
    t s = iVal[3] / b.iVal[3];
    iVal[0] -= b.iVal[0] / s;
    iVal[1] -= b.iVal[1] / s;
    iVal[2] -= b.iVal[2] / s;
    normalized = false;
  }

  template <class t>
  void vector4<t>::operator*=(const t x)
  {
    iVal[3] *= x;
  }

  template <class t>
  bool vector4<t>::operator==(const vector4& b)
  {
    return
      iVal[0] == b.iVal[0] &&
      iVal[1] == b.iVal[1] &&
      iVal[2] == b.iVal[2] &&
      iVal[3] == b.iVal[3];
  }

  template <class t>
  vector4<t> vector4<t>::operator*(matrix4x4<t>& m)
  {
    // TODO: Optimize
    reset();
    return vector4<t>(dot(m.getColumn(0), false),
		      dot(m.getColumn(1), false),
		      dot(m.getColumn(2), false),
		      dot(m.getColumn(3), false));
  }

  template <class t>
  t vector4<t>::operator[](int i)
  {
    return iVal[i];
  }

}

#endif // _VMVECTOR_HH
