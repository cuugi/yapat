/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2006 cuugi(a)iki.fi
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

#ifndef _METRIX_HH
#define _METRIX_HH

#include <time.h>

struct metdata {
  clock_t iStart; // TODO: store in map with keys (aKey + id)
  clock_t iTotal;
  long iCounter;
};

/**
 * Collects and prints metrics from code.
 *
 */
class metrix
{
public:
  /**
   * Starts counting.
   *
   * @return id, give this to stop()
   */
  static long start(const char* aKey);

  /**
   * Stops counting.
   *
   */
  static void stop(long aId);

  /**
   * Prints metrics.
   * 
   */
  static void print();

private: // Attributes
  static long iNextId;
  static struct metdata iStats;
};

#endif // _METRIX_HH
