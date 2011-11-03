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

#include "universe.hh"

namespace uni {

  universe::universe() : iObjects(), iCameras(), iShaders(), iArealights()
  {
    iEnvMap = NULL;
  }

  universe::universe(envmap* aEnvMap) : iObjects(), iCameras(), iShaders(), iArealights()
  {
    iEnvMap = aEnvMap;
  }

  universe::~universe()
  {
    // Empty data structures
    while (iObjects.size()) {
      delete iObjects.back();
      iObjects.pop_back();
    }
    while (iCameras.size()) {
      delete iCameras.back();
      iCameras.pop_back();
    }
    while (iShaders.size()) {
      delete iShaders.back();
      iShaders.pop_back();
    }
    while (iArealights.size()) {
      delete iArealights.back();
      iArealights.pop_back();
    }

    // ...
    delete iEnvMap;
  }

  int universe::attach(surfaceobject* aObject)
  {
    log::debug("universe::attach(%s)", aObject->getName());

    iObjects.push_back(aObject);
    return iObjects.size();
  }

  int universe::attach(camera* aCamera)
  {
    log::debug("universe::attach(%s)", aCamera->getName());

    iCameras.push_back(aCamera);
    return iCameras.size();
  }

  int universe::attach(shader* aShader)
  {
    log::debug("universe::attach(%s)", aShader->getName());

    // Add shader to name-shader map
    if (iNameShader.find(aShader->getName()) != iNameShader.end()) {
      log::debug("Warning: Shader %s already exists.", aShader->getName());

    } else {
      iNameShader.insert(std::make_pair(aShader->getName(), aShader));
    }

    iShaders.push_back(aShader);
    return iShaders.size();
  }

  int universe::attach(arealight* aArealight)
  {
    log::debug("universe::attach(arealight)");

    iArealights.push_back(aArealight);
    return iArealights.size();
  }

  shader* universe::getShader(const char* aName)
  {
    // std::iterator<std::pair<const char*, shader*> > ret = iNameShader.find(aName);
    return NULL; // TODO: ret != iNameShader.end() ? ret : NULL;
  }

  std::list<surfaceobject*> universe::objects()
  {
    return iObjects;
  }

  std::list<arealight*> universe::arealights()
  {
    return iArealights;
  }

  void universe::prepare()
  {
    printf("universe::prepare(): ");
    std::list<uni::shader*>::iterator siter = iShaders.begin();
    while (siter != iShaders.end())
      {
	(*siter)->prepare();
	siter++;
	printf(".");
      }

    printf(" ");
    std::list<uni::surfaceobject*>::iterator oiter = iObjects.begin();
    while (oiter != iObjects.end())
      {
	(*oiter)->prepare();
	oiter++;
	printf(".");
      }

    printf(" ");
    std::list<uni::arealight*>::iterator liter = iArealights.begin();
    while (liter != iArealights.end())
      {
	(*liter)->prepare();
	liter++;
	printf(".");
      }
    printf("\n");
  }
} // uni
