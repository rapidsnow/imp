//
// impBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "impBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   const char*			name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
const char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];
	
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
	color[3] = (GLubyte)pDoc->getAlpha(); //Set the alpha channel to whatever the slider says

	glColor4ubv( color );

}

//-------------------------------------------------------
// Use right click and drag to set the angle of the brush
//-------------------------------------------------------

void	ImpBrush::AngleDragBegin(const Point source) 
{
	ImpressionistDoc* pDoc = GetDocument();

	if(pDoc->getAngleRadio() != 1)
		return;

	pDoc->setRightClickStart(source);

}
void	ImpBrush::AngleDragMid(const Point source)
{
}
void	ImpBrush::AngleDragEnd(const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	if(pDoc->getAngleRadio() != 1)
		return;

	Point start = pDoc->getRightClickStart();

	int angle = int( atan( float( (source.y - start.y) )/(source.x - start.x) ) * (180./M_PI));

	pDoc->setBrushAngle(angle);
}