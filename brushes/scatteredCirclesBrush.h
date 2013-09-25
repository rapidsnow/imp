//
// scatteredCirclesBrush.h
//
// The header file for Scattered Circles Brush. 
//

#ifndef SCATTEREDCIRCLESBRUSH_H
#define SCATTEREDCIRCLESBRUSH_H

#include "../impBrush.h"
#include <math.h>

class ScatteredCirclesBrush : public ImpBrush
{
public:
	ScatteredCirclesBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void MakeCircle( const Point source, const int radius );
	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif