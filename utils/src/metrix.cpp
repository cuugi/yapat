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

#include <stdio.h>
#include <stdarg.h>

#include "metrix.hh"

// Initialize static variables
long metrix::iNextId = 1; 
metdata metrix::iStats = { 0, 0, 1 };

long metrix::start(const char* aKey)
{
  iStats.iStart = clock();
  return iNextId++;
}

void metrix::stop(long aId)
{
  iStats.iTotal += clock() - iStats.iStart;
  iStats.iCounter++;
}

void metrix::print()
{
  printf("Running metrics:\n");
  printf(" Total method calls: %u\n", iStats.iCounter);
  printf(" Total time: %.2f s\n", iStats.iTotal / 1000000.0);
  printf(" Average time per call: %.3f ms\n", 
	 iStats.iTotal / (iStats.iCounter * 1000.0));
}
