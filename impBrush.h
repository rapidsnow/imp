#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>
#include <math.h>

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES = 1,
	BRUSH_CIRCLES = 2,
	BRUSH_SCATTERED_POINTS = 3,
	BRUSH_SCATTERED_LINES = 4,
	BRUSH_SCATTERED_CIRCLES = 5,
	NUM_BRUSH_TYPE = 6 // Make sure this stays at the end!
};


class ImpressionistDoc; // Pre-declaring class

class Point 
{
public:
	Point() {};
	Point(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};

class ImpBrush 
{
protected:
	ImpBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const Point source, const Point target ) = 0;
	virtual void BrushMove( const Point source, const Point target ) = 0;
	virtual void BrushEnd( const Point source, const Point target ) = 0;

	// according to the source image and the position, determine the draw color
	void SetColor( const Point source );

	// according to the source point at the beginning and end of the right click drag, set the angle
	void AngleDragBegin(const Point source);
	void AngleDragMid(const Point source);
	void AngleDragEnd(const Point source);

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	const char* BrushName( void );
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	const char*			m_pBrushName;
};

#endif

