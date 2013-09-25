//
// scatteredCirclesBrush.cpp
//
// The implementation of Scattered Circles Brush. It is a kind of ImpBrush.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "scatteredCirclesBrush.h"

extern float frand();

void ScatteredCirclesBrush::MakeCircle (const Point source, const int radius) {
	int const precision = 5;
	
	glBegin( GL_POLYGON );
		SetColor( source );
		for(int i = 0; i < 360; i+=precision) {
			glVertex2d( source.x + radius * cos( (i * M_PI)/180 ), source.y + radius * sin( (i * M_PI)/180 ));
		}
	glEnd();
}

ScatteredCirclesBrush::ScatteredCirclesBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredCirclesBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCirclesBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	float sep = 4; //The 4 seems like a good factor for circle separation... Two times the diameter

	if ( pDoc == NULL ) {
		printf( "ScatteredCirclesBrush::BrushMove  document is NULL\n" );
		return;
	}
	int radius = pDoc->getSize();
	for(int i = 0; i < 20; i++) {
		MakeCircle(Point(source.x + (frand() - 0.5) * radius * sep, source.y + (frand() - 0.5) * radius * sep), radius);
	}
}

void ScatteredCirclesBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

