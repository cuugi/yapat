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

#ifndef _VMMATRIX_HH
#define _VMMATRIX_HH

#include <stdio.h>

#include <log.hh>

namespace vm {

#define X 0
#define Y 1
#define Z 2

  // defined in <vmvector.hh>
  template <class t>
  class vector4;

  /**
   * 4x4 matrix.
   *
   * @author cuugi(a)iki.fi
   */
  template <class t>
  class matrix4x4
  {
  public: // Constructors
    /**
     * Default constructor.  Creates an identity matrix.
     */
    inline matrix4x4()
    {
      log::debug("matrix4x4::matrix4x4()");

      iVal[1][0] = iVal[2][0] = iVal[3][0] = 0;
      iVal[0][1] = iVal[2][1] = iVal[3][1] = 0;
      iVal[0][2] = iVal[1][2] = iVal[3][2] = 0;
      iVal[0][3] = iVal[1][3] = iVal[2][3] = 0;
      iVal[0][0] = iVal[1][1] = iVal[2][2] = iVal[3][3] = 1;
    }

    /**
     * Constructor.
     */
    inline matrix4x4(t i00, t i10, t i20, t i30,
	      t i01, t i11, t i21, t i31,
	      t i02, t i12, t i22, t i32,
	      t i03, t i13, t i23, t i33)
    {
      iVal[0][0] = i00; iVal[1][0] = i10; iVal[2][0] = i20; iVal[3][0] = i30;
      iVal[0][1] = i01; iVal[1][1] = i11; iVal[2][1] = i21; iVal[3][1] = i31;
      iVal[0][2] = i02; iVal[1][2] = i12; iVal[2][2] = i22; iVal[3][2] = i32;
      iVal[0][3] = i03; iVal[1][3] = i13; iVal[2][3] = i23; iVal[3][3] = i33;
    }

    virtual ~matrix4x4()
    {
      // log::debug("matrix4x4::~matrix4x4()");
    }

  public: // New methods
    /**
     * Returns a row as a vector.
     *
     * @param i row index (0-3)
     */
    vector4<t> getRow(int i);

    /**
     * Returns a column as a vector.
     *
     * @param i column index (0-3)
     */
    vector4<t> getColumn(int i);

    /**
     * Print the matrix to a stream.
     *
     * TODO: give the stream as a parameter
     */
    inline void print()
    {
      printf("(%.2f, %.2f, %.2f, %.2f)\n(%.2f, %.2f, %.2f, %.2f)\n(%.2f, %.2f, %.2f, %.2f)\n(%.2f, %.2f, %.2f, %.2f)\n",
	     iVal[0][0], iVal[1][0], iVal[2][0], iVal[3][0],
	     iVal[0][1], iVal[1][1], iVal[2][1], iVal[3][1],
	     iVal[0][2], iVal[1][2], iVal[2][2], iVal[3][2],
	     iVal[0][3], iVal[1][3], iVal[2][3], iVal[3][3]);
    }

  public: // New operators
    void operator+=(const matrix4x4& b);

    /**
     * Matrix multiplication: this x b
     */
    void operator*=(const matrix4x4& b);

    vector4<t> operator*(vector4<t>& b);

  private:
    /** Matrix parameters. */
    t iVal[4][4]; // x, y
  };

} // vm

/*** Methods ***/
namespace vm {

  template <class t>
  vector4<t> matrix4x4<t>::getRow(int i)
  {
    return vector4<t>(iVal[0][i], iVal[1][i],
		      iVal[2][i], iVal[3][i]);
  }

  template <class t>
  vector4<t> matrix4x4<t>::getColumn(int i)
  {
    return vector4<t>(iVal[i][0], iVal[i][1],
		      iVal[i][2], iVal[i][3]);
  }

  template <class t>
  void matrix4x4<t>::operator+=(const matrix4x4& b)
  {
    for (int x = 0; x < 4; x++)
      for (int y = 0; y < 4; y++)
	iVal[x][y] += b.iVal[x][y];
  }

  template <class t>
  void matrix4x4<t>::operator*=(const matrix4x4& b)
  {
    // TODO: Optimize
    matrix4x4<t> tmp(0, 0, 0, 0,
		     0, 0, 0, 0,
		     0, 0, 0, 0,
		     0, 0, 0, 0);

    for (int y = 0; y < 4; y++)
      for (int x = 0; x < 4; x++)
	for (int i = 0; i < 4; i++)
	  tmp.iVal[x][y] +=
	    iVal[i][y] * b.iVal[x][i];

    *this = tmp;
  }

  template <class t>
  vector4<t> matrix4x4<t>::operator*(vector4<t>& v)
  {
    // TODO: Optimize
    v.reset();
    return vector4<t>(v.dot(getRow(0), false),
		      v.dot(getRow(1), false),
		      v.dot(getRow(2), false),
		      v.dot(getRow(3), false));
  }

} // vm


#endif // _VMMATRIX_HH
