//
// scatteredLinesBrush.h
//
// The header file for Scattered Lines Brush. 
//

#ifndef SCATTEREDLINESBRUSH_H
#define SCATTEREDLINESBRUSH_H

#include "../impBrush.h"

class ScatteredLinesBrush : public ImpBrush
{
public:
	ScatteredLinesBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif