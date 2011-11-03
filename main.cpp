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
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <QApplication>
#include <QTextStream>

#include <log.hh>
#include <metrix.hh>

#include <ptrenderer.hh>
#include <qtptrenderer.hh>
#include <testinput.hh>
// #include <magickoutput.hh>
#include <nulloutput.hh>
#include <qimageoutput.hh>

#include "version.h"

using namespace std;
using namespace vm;
using namespace uni;
using namespace rend;

// #define TEST_UNI
// #define TEST_REND

struct yapatConfig {
  enum renderer {
    PathTracer,
    QtPathTracer
  } iRenderer;
  enum inputPipe {
    TestInput
  } iInputPipe;
  enum outputPipe {
    Magick,
    Null,
    QImage
  } iOutputPipe;
  const char* iOutputFilename;
  const char* iTempFilename;
  const char* iGeometry;
};

const char* RENDERERS[] = { "PathTracer", "QtPathTracer" };

const char* INPUT_PIPES[] = { "TestInput" };

const char* OUTPUT_PIPES[] = { "Magick", "Null", "QImage" };

int main(int ac, char** argv) {
  QApplication application(ac, argv);
  QTextStream textOutput(stdout);

  yapatConfig config;
  config.iRenderer = yapatConfig::QtPathTracer;
  config.iInputPipe = yapatConfig::TestInput;
  config.iOutputPipe = yapatConfig::QImage;
  config.iOutputFilename = "test.png";
  config.iTempFilename = "tmp.png";
  config.iGeometry = "640x480";

  textOutput << "yapat version " << VERSION << " (build " << "b" << endl;
  textOutput << "Copyright (c) 2005-2009 cuugi(a)iki.fi" << endl << endl;
  textOutput.flush();

  // If no options is given, print usage
  if (ac < 2) {
    cout << "Usage: " << argv[0] << " [options]\n\n";
    cout << "\t-re RENDERER\tselected rendering engine, default is "
        << RENDERERS[config.iRenderer] << "\n";
    cout << "\t-i PIPE\tinput pipe, default is "
        << INPUT_PIPES[config.iInputPipe] << "\n";
    cout << "\t-o PIPE\toutput pipe, default is "
        << OUTPUT_PIPES[config.iOutputPipe] << "\n";
    cout << "\t-of FILENAME\toutput filename, default is "
        << config.iOutputFilename << "\n";
    cout << "\t-size GEOMETRY\tsize of the output image, default is "
        << config.iGeometry << "\n";
    cout << "\n";

    return 0;
  }

  // Parse arguments
  int i = 1; // argument index
  while (i < ac) {
    string arg = argv[i++];
    if (!arg.compare("-re") && i < ac) {
      config.iRenderer = (yapatConfig::renderer) atoi(argv[i++]);
    } else if (!arg.compare("-i") && i < ac) {
      config.iInputPipe = (yapatConfig::inputPipe) atoi(argv[i++]);
    } else if (!arg.compare("-o") && i < ac) {
      config.iOutputPipe = (yapatConfig::outputPipe) atoi(argv[i++]);
    } else if (!arg.compare("-of") && i < ac) {
      config.iOutputFilename = argv[i++];
    } else if (!arg.compare("-size") && i < ac) {
      config.iGeometry = argv[i++];
    }
  }

  // Initialize input
  log::debug("Input pipe: %s(%d)", INPUT_PIPES[config.iInputPipe],
      config.iInputPipe);
  input* in = NULL;
  switch (config.iInputPipe) {
  case yapatConfig::TestInput:
    in = new testinput();
    break;

  default:
    return -1; // Broken pipe
  }

  // Initialize output
  log::debug("Output pipe: %s(%d)", OUTPUT_PIPES[config.iOutputPipe],
      config.iOutputPipe);
  log::debug("Output filename: %s", config.iOutputFilename);
  log::debug("Geometry: %s", config.iGeometry);
  output* out = NULL;
  switch (config.iOutputPipe) {
  case yapatConfig::Magick:
    // out = new magickoutput(config.iGeometry, "black", config.iTempFilename);
    break;

  case yapatConfig::Null:
    out = new nulloutput();
    break;

  case yapatConfig::QImage:
    // TODO config.iGeometry
    out = new qimageoutput(640, 480, config.iTempFilename);
    break;

  default:
    return -1; // Broken pipe
  }

  // Initialize renderer
  log::debug("Renderer: %s(%d)", RENDERERS[config.iRenderer], config.iRenderer);
  renderer* rndr = NULL;
  switch (config.iRenderer) {
  case yapatConfig::PathTracer:
    rndr = new ptrenderer();
    break;

  case yapatConfig::QtPathTracer:
    rndr = new qtptrenderer();
    break;

  default:
    return -2;
  }

  // Parse input, and start rendering
  universe u = in->getUniverse();
  rndr->setUniverse(&u);
  rndr->setOutput(out);
  rndr->render(NULL, in->getCamera());
  out->flush(config.iOutputFilename);

  // Clean up
  delete rndr;
  delete in;
  delete out;

  metrix::print();
  return application.exec();
}
