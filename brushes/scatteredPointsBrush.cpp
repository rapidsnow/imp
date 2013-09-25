//
// scatteredPointsBrush.cpp
//
// The implementation of Scattered Points Brush. It is a kind of ImpBrush.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "scatteredPointsBrush.h"
#include <math.h>

extern float frand();

ScatteredPointsBrush::ScatteredPointsBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredPointsBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredPointsBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredPointsBrush::BrushMove document is NULL\n" );
		return;
	}

	float randAngle;

	int scatterRadius = pDoc->getScatterRadius(); //Set up a given radius size for your points
	int n_Points = M_PI * pow(scatterRadius, 2.) * 50; //50 points per unit area?

	glBegin( GL_POINTS );
		SetColor( source );
		for (int i = 0; i < n_Points; i ++)
			randAngle = frand() * 2 * M_PI;
			glVertex2d( source.x + scatterRadius * cos( randAngle ), source.y + scatterRadius * sin( randAngle ) );
	glEnd();
}

void ScatteredPointsBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

