//
// scatteredPointsBrush.h
//
// The header file for Scattered Points Brush. 
//

#ifndef SCATTEREDPOINTSBRUSH_H
#define SCATTEREDPOINTSBRUSH_H

#include "../impBrush.h"

class ScatteredPointsBrush : public ImpBrush
{
public:
	ScatteredPointsBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif