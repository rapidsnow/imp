//
// circleBrush.h
//
// The header file for Circle Brush. 
//

#ifndef CIRCLEBRUSH_H
#define CIRCLEEBRUSH_H



#include <math.h>
#include "../impBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif