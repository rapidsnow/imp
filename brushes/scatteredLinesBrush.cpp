//
// scatteredLinesBrush.cpp
//
// The implementation of Scattered Lines Brush. It is a kind of ImpBrush.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "scatteredLinesBrush.h"
#include <math.h>

extern float frand();

ScatteredLinesBrush::ScatteredLinesBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredLinesBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int lineWidth = pDoc->getLineWidth();
	glLineWidth((GLfloat) lineWidth);

	BrushMove( source, target );
}

void ScatteredLinesBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredLinesBrush::BrushMove  document is NULL\n" );
		return;
	}

	float tempRand;
	int x1, y1;
	int x2, y2;

	int length = pDoc->getSize();
	int radius = pDoc->getScatterRadius();

	glBegin( GL_LINES );
		SetColor( source );
		for(int i = 0; i < 5; i++) {
			//Choose two random vertices within 0.5 * scatter radius of source
			x1 = source.x + (frand() - 0.5) * radius;
			y1 = source.y + (frand() - 0.5) * radius;

			//Create a unit vector in some random angle then multiply it by length and add to x1, y1
			tempRand = frand() * 2 * M_PI;
			x2 = cos(tempRand) * length + x1;
			y2 = sin(tempRand) * length + y1;

			//Random line in a random direction
			glVertex2d( x1, y1 );
			glVertex2d( x2, y2 );
		}
		
	glEnd();
}

void ScatteredLinesBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

