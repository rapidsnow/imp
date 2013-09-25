//
// circleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush.
//



#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "circleBrush.h"

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "CircleBrush::BrushMove  document is NULL\n" );
		return;
	}

	int radius = pDoc->getSize(); //How big should the circle be?

	glBegin( GL_POLYGON );
		SetColor( source );
		for(int i = 0; i < 360; i+=5) { //72 Sides should be more than enough to trick our eyes
			glVertex2d( source.x + radius * cos( (i * M_PI)/180 ), source.y + radius * sin( (i * M_PI)/180 ));
		}
		
	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

