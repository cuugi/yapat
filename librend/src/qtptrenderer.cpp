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

#include <stdlib.h>

#include <QFuture>
#include <QFutureIterator>
#include <QtConcurrentMap>

#include <log.hh>
#include <metrix.hh>
#include <rand.hh>

#include <ray.hh>
#include <shader.hh>
#include <unibase.hh>

#include "qtptrenderer.hh"

namespace rend
{

  qtptrenderer::qtptrenderer() : QObject(), ptrenderer()
  {
  }

  qtptrenderer::~qtptrenderer()
  {
  }

  uni::color qtptrenderer::trace( const QPair<qtptrenderer*, uni::ray> &aInput )
  {
    // log::debug( "qtptrenderer::trace()" );
    unsigned int depth = 5;
    I shutter = 0.4; // s
    I t = rand::ran(shutter);
    qtptrenderer* renderer = aInput.first;

    return static_cast<ptrenderer*>( renderer )->trace( depth, aInput.second, t ); 
  }

  void qtptrenderer::render( renderingcontext* aCtx, uni::camera* aCamera )
  {

#ifndef QT_NO_CONCURRENT

    printf( "QtConcurrent enabled.\n");

    iUniverse->prepare();

    // Variables, TODO --> ctx
    unsigned int width = iOutput->width();
    unsigned int height = iOutput->height();
    unsigned int n = 3; // number of samples per axis
    unsigned int tenp = height * width / 10;
    unsigned int p = 0;

    for ( unsigned int y = 0; y < height; y++ )
      {
    	for ( unsigned int x = 0; x < width; x++, p++ )
	  {
	    long mid = metrix::start("qtptrenderer");
	    // status
	    if ( p % tenp == 0 )
	      {
		printf( "%d percent ready\n", p / tenp * 10 );
		iOutput->flush();
		// TODO emit a signal
	      }

	    // create a list of rays to trace
	    QList<QPair<qtptrenderer*, uni::ray> > input; // <renderer, ray>
	    for ( unsigned int sampX = 0; sampX < n; sampX++ )
	      for ( unsigned int sampY = 0; sampY < n; sampY++ )
		{
		  input.append( qMakePair( this,
					   castRay( aCamera, width, height,
						    x, y, n, n, sampX, sampY, true) ) );
		}

	    // do tracing in multiple threads
	    // log::debug( "Start tracing." );
	    QFuture<uni::color> samples = 
	      QtConcurrent::mapped( input, &qtptrenderer::trace );

	    // TODO prepare new tracing before combining results, or use mappedReduced

	    // combine results
	    uni::color c(0.0, 0.0, 0.0);
	    samples.waitForFinished();
	    QFutureIterator<uni::color> iter( samples );
	    while ( iter.hasNext() )
	      {
		const uni::color sample = iter.next();
		if (sample.isValid())
		  c += sample;
	      }
	    c /= n*n;
	    if (c.iRed > 1.0) c.iRed = 1.0;
	    if (c.iGreen > 1.0) c.iGreen = 1.0;
	    if (c.iBlue > 1.0) c.iBlue = 1.0;
	    iOutput->plotColor(x, y, c);

	    metrix::stop(mid);
	  }
      }
 
#else // QT_NO_CONCURRENT

    printf( "QtConcurrent not enabled. Not rendering.\n");

#endif // QT_NO_CONCURRENT
  }

} // rend
