//
// lineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "lineBrush.h"

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int lineWidth = pDoc->getLineWidth();
	glLineWidth((GLfloat) lineWidth);

	pDoc->setLastPoint( source );
	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}
	int length;
	int angleSelection;
	float angle;
	Point lastPoint;

	//Define the length and figure out how we are determining the brush angle
	length = pDoc->getSize();
	angleSelection = pDoc->getAngleRadio();

	//If the brush angle selection is based off of cursor direction, do this
	if (angleSelection == 2) 
	{
		lastPoint = pDoc->getLastPoint();
		angle = atan(float(lastPoint.y - source.y)/(lastPoint.x - source.x)) + M_PI/2.;
	} 
	else
		angle = pDoc->getBrushAngle() * (M_PI/180.);

	//Create the lines

	glBegin( GL_LINES );
		SetColor( source );
		glVertex2d( source.x, source.y );
		glVertex2d( source.x + cos(angle) * length, source.y + sin(angle) * length);
	glEnd();

	pDoc->setLastPoint(source);
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

