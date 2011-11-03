/*
 * ============================================================================
 * GNU Lesser General Public License
 * ============================================================================
 *
 * yapat - global illumination rendering engine
 * copyright (c) 2006-2009 cuugi(a)iki.fi
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

#include <camera.hh>
#include <envmap.hh>
#include <lightrect.hh>
#include <lightsphere.hh>
#include <plane.hh>
#include <sphere.hh>
#include <universe.hh>

#include <chessshader.hh>
#include <glassshader.hh>
#include <mirrorshader.hh>
#include <noisetest.hh>
#include <snookershader.hh>

#include "testinput.hh"

using namespace uni;
using namespace vm;

namespace rend
  {

    testinput::testinput() :
      input()
      {
        iCamera = new camera("camera",
            vector4<I>(-2.0, 0.0, 10.0));
      }

    testinput::~testinput()
      {
      }

    uni::universe testinput::getUniverse()
      {
        universe u;
        u.attach(iCamera);

        sphere* o1 = new sphere("stone", 5.0); // , vm::vector4<I>(-1.0, 0.0, 3.0));
        sphere* o2 = new sphere("red1", 3.5); // , vm::vector4<I>(8.0, 0.0, -4.0));
        sphere* o3 = new sphere("red2", 5.0, vm::vector4<I>(-13.5, 0.0, -15.));
        sphere* o4 = new sphere("blue", 5.0);
        sphere* o5 = new sphere("black", 2.0);
        plane* p1 = new plane("floor");
        plane* p2 = new plane("back");
        plane* p3 = new plane("leftwall");
        plane* p4 = new plane("rightwall");
        plane* p5 = new plane("roof");
        // vector4<I>(0.0, -1.0, 1.0), vector4<I>(0.0, 1.0, 1.0));
        lightsphere* l1 = new lightsphere("light1", 2.5);
        lightsphere* l2 = new lightsphere("light2", 3.5);
        lightrect* l3 = new lightrect("light3", 3.0);
        lightrect* l4 = new lightrect("light4", 3.0);
        lightrect* l5 = new lightrect("light5", 3.0);

        // Create shaders
        glassshader* glass = new glassshader("glass", 1.5, 0.1); // Glass
        mirrorshader* mirror =new mirrorshader("mirror", color(1.0, 1.0, 1.0), 0.99); // , 0.3);
        chessshader* chess = new chessshader("chess");
        basicshader* white = new basicshader("white", color(1.0, 1.0, 1.0), 0.9);
        basicshader* red = new basicshader("red", color(0.9, 0.0, 0.0));
        basicshader* green = new basicshader("green", color(0.0, 0.3, 0.0));
        basicshader* blue = new basicshader("blue", color(0.3, 0.3, 0.7), 0.9);

        snookershader* sbwhite = new snookershader("swhite");
        snookershader* sbred = new snookershader("sred", color(0.9, 0.0, 0.0));
        snookershader* sbblue = new snookershader("sblue", color(0.0, 0.0, 0.9));
        snookershader* sbblack = new snookershader("sblack", color(0.0, 0.0, 0.0));

        distancelightshader* dlred =new distancelightshader("distred", color(0.9, 0.9, 0.9), true);
        distancelightshader* dlgreen =new distancelightshader("distgreen", color(1.9, 1.9, 1.9), true);
        distancelightshader* dlblue =new distancelightshader("distblue", color(0.9, 0.9, 1.0), true);

        // Set shaders
        o1->setSurfaceShader(white); // mirror);
        o2->setSurfaceShader(white); // glass);
        o3->setSurfaceShader(sbred);
        o4->setSurfaceShader(sbblue);
        o5->setSurfaceShader(white);

        p1->setSurfaceShader(white); // chess);
        p2->setSurfaceShader(white);
        p3->setSurfaceShader(blue);
        p4->setSurfaceShader(white);
        p5->setSurfaceShader(white);

        l1->setLightShader(dlred);
        l2->setLightShader(dlgreen);
        l3->setLightShader(dlred);
        l4->setLightShader(dlgreen);
        l5->setLightShader(dlblue);

        // Relocate
        o1->translate(vector4<I>(-4.0, 0.0, 15.0));
        o2->translate(vector4<I>(6.0, -1.5, -8.0));
        o3->translate(vector4<I>(-4.0, 0.0, -13.0));
        o4->translate(vector4<I>(-5.0, 0.0, 10.0));
        o5->translate(vector4<I>(-4.0, -3.0, -2.0));

        p1->translate(vector4<I>(0.0, -5.0, 0.0));
        p2->rotate(-M_PI/2, vector4<I>(1.0, 0.0, 0.0));
        p2->translate(vector4<I>(0.0, -30.0, 0.0));
        p3->rotate(-M_PI/2, vector4<I>(0.0, 0.0, 1.0));
        p3->translate(vector4<I>(0.0, -13.5, 0.0));
        p4->rotate(M_PI/2, vector4<I>(0.0, 0.0, 1.0));
        p4->translate(vector4<I>(0.0, -13.5, 0.0));
        p5->rotate(M_PI, vector4<I>(0.0, 0.0, 1.0));
        p5->translate(vector4<I>(0.0, -13.5, 0.0));

        iCamera->translate(vector4<I>(2.0, 4.0, -35.0));
        // c1->translate(vector4<I>(0.0, 3.0, -3.0));
        l1->translate(vector4<I>(-5.0, 6.0, -40.0));
        l2->translate(vector4<I>(25.0, 38.0, -25.0));
        l3->translate(vector4<I>(6.0, 13.45, 6.0));
        l4->translate(vector4<I>(0.0, 13.45, 0.0));
        l5->translate(vector4<I>(-6.0, 13.45, -6.0));

        // Attach
        // u.attach(white);
        // u.attach(red);
        // u.attach(green);
        u.attach(p1);
        u.attach(p2);
        u.attach(p3);
        u.attach(p4);
        u.attach(p5);
        u.attach(o1);
        u.attach(o2);
        // u.attach(o3);
        // u.attach(o4);
        u.attach(o5);

        // u.attach((arealight*) l1);
        // u.attach((arealight*) l2);
        // u.attach((arealight*) l3);
        u.attach((arealight*) l4);
        // u.attach((arealight*) l5);

        return u;
      }

      uni::camera* testinput::getCamera()
        {
          return iCamera;
        }
  } // rend
