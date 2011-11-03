/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2005-2006 cuugi(a)iki.fi
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

#include "log.hh"

int log::debug(const char* msg, ...)
{
  va_list ap;
  char m[MAX_DEBUG];
  va_start(ap, msg);
  if (vsprintf(m, msg, ap) > MAX_DEBUG)
    {
      throw MAX_DEBUG;
    }
  va_end(ap);
  printf("<D> %s\n", m); // , ap);

  return 0;
}

