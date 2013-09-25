// 
// impressionistDoc.cpp
//
// It basically maintains the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//


#include <FL/fl_ask.H>

#include <algorithm>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "impBrush.h"

// Include individual brush headers here.
#include "brushes/pointBrush.h"
#include "brushes/circleBrush.h"
#include "brushes/lineBrush.h"
#include "brushes/scatteredLinesBrush.h"
#include "brushes/scatteredPointsBrush.h"
#include "brushes/scatteredCirclesBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucPreviewBackup = NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_POINTS]	
		= new PointBrush( this, "Points" );
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointsBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLinesBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCirclesBrush( this, "Scattered Circles" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the line width of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}

//---------------------------------------------------------
// Returns the brush angle.
//---------------------------------------------------------
int ImpressionistDoc::getBrushAngle()
{
	return m_pUI->getBrushAngle();
}

//---------------------------------------------------------
// Sets the brush angle.
//---------------------------------------------------------
void ImpressionistDoc::setBrushAngle(int angle)
{
	m_pUI->setBrushAngle(angle);
}

//---------------------------------------------------------
// Returns the alpha value.
//---------------------------------------------------------
int ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

//---------------------------------------------------------
// Returns the Scatter Radius for ScatteredPointsBrush.
//---------------------------------------------------------
int ImpressionistDoc::getScatterRadius()
{
	return m_pUI->getScatterRadius();
}

//---------------------------------------------------------
// Called by the UI when the user changes the angle 
// determination radio button.
//---------------------------------------------------------
void ImpressionistDoc::setAngleRadio(int choice)
{
	m_pUI->setAngleRadio(choice);
}

//---------------------------------------------------------
// Returns the angle determination radio button value.
//---------------------------------------------------------
int ImpressionistDoc::getAngleRadio()
{
	return m_pUI->getAngleRadio();
}


//--------------------------------------
// Kernel Routines
//--------------------------------------

//---------------------------------------------------------
// Called by the UI when the user changes the kernel size.
//---------------------------------------------------------
void ImpressionistDoc::setKernelSizeX(int size)
{
	m_pUI->setKernelSizeX(size);
}

//---------------------------------------------------------
// Returns the size of the kernel in X.
//---------------------------------------------------------
int ImpressionistDoc::getKernelSizeX()
{
	return m_pUI->getKernelSizeX();
}

//---------------------------------------------------------
// Called by the UI when the user changes the kernel size.
//---------------------------------------------------------
void ImpressionistDoc::setKernelSizeY(int size)
{
	m_pUI->setKernelSizeY(size);
}

//---------------------------------------------------------
// Returns the size of the kernel in Y.
//---------------------------------------------------------
int ImpressionistDoc::getKernelSizeY()
{
	return m_pUI->getKernelSizeY();
}

//---------------------------------------------------------
// Called by the UI when the user any value in 
// the float input grid.
//---------------------------------------------------------
void ImpressionistDoc::setTmpKnlValue(float value)
{
	m_nTmpKnlValue = value;
}

//---------------------------------------------------------
// Returns the value in the most recently
// changed float input grid slot.
//---------------------------------------------------------
float ImpressionistDoc::getTmpKnlValue()
{
	return m_pUI->getTmpKnlValue();
}

//------------------------------------------------------------------
// Set and return the right click start point for angle calculations
//------------------------------------------------------------------

void ImpressionistDoc::setRightClickStart(Point start) 
{
	m_pRightClickStart=start;
}

Point ImpressionistDoc::getRightClickStart() 
{
	return m_pRightClickStart;
}


//------------------------------------------------------------------
// Set and return the last point for angle calculations
//------------------------------------------------------------------

void ImpressionistDoc::setLastPoint(Point last) 
{
	m_pLastPoint=last;
}

Point ImpressionistDoc::getLastPoint() 
{
	return m_pLastPoint;
}


//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	delete [] m_ucBitmap;
	delete [] m_ucPainting;
	delete [] m_ucPreviewBackup;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting		= new unsigned char [width*height*4];
	m_ucPreviewBackup	= new unsigned char [width*height*4];
	memset(m_ucPainting, 0, width*height*4);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*4];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*4);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

// Apply the filter specified by filter_kernel to the 
// each pixel in the source buffer and place the resulting
// pixel in the destination buffer.  

// This is called from the UI when the
// "preview" or "apply" button is pressed in the filter dialog.



/*
 *	INPUT: 
 *		sourceBuffer:		the original image buffer, 
 *		srcBufferWidth:		the width of the image buffer
 *		srcBufferHeight:	the height of the image buffer
 *							the buffer is arranged such that 
 *							origImg[3*(row*srcBufferWidth+column)+0], 
 *							origImg[3*(row*srcBufferWidth+column)+1], 
 *							origImg[3*(row*srcBufferWidth+column)+2]
 *							are R, G, B values for pixel at (column, row).
 *		destBuffer:			the image buffer to put the resulting
 *							image in.  It is always the same size
 *							as the source buffer.
 *
 *      filterKernel:		the 2D filter kernel,
 *		knlWidth:			the width of the kernel
 *		knlHeight:			the height of the kernel
 *
 *		divisor, offset:	each pixel after filtering should be
 *							divided by divisor and then added by offset
 */
void ImpressionistDoc::applyFilter( const unsigned char* sourceBuffer,
		int srcBufferWidth, int srcBufferHeight,
		unsigned char* destBuffer,
		const float *filterKernel, 
		int knlWidth, int knlHeight, 
		double divisor, double offset )
{
	float redSum;
	float greenSum;
	float blueSum;

	int knlIndex; //The index calculations in the inner loops get messy
	int srcIndex;

	divisor = 0;

	//Sum up the filter kernel values so that we can average it out at the end
	for (int i = 0; i < knlHeight; i++) {
		for (int j = 0; j < knlWidth; j++) {
			divisor += filterKernel[i*knlWidth+j];
		}
	}

	//Iterate over all of the pixels in the source buffer
	for (int row = 0; row < srcBufferHeight; row++) {
		for (int column = 0; column < srcBufferWidth; column++) {
			//Reset the R,G,B sums
			redSum = 0;
			greenSum = 0;
			blueSum = 0;

			//Iterate over all of the filter kernel positions
			for (int knlRow = 0; knlRow < knlHeight; knlRow++) {
				for (int knlColumn = 0; knlColumn < knlWidth; knlColumn++) {

					//Set the index values for our current pixel
					knlIndex = knlRow * knlWidth + knlColumn;
					srcIndex = 3 * ((row + knlRow - knlWidth/2 + 1) * srcBufferWidth
						+ (column + knlColumn - knlColumn/2 + 1));

					if (srcIndex < 0 || srcIndex > 3*srcBufferWidth*srcBufferHeight) {
						srcIndex = 3 * (row * srcBufferWidth + column);
					}
					
					//TODO: Fix edge problems.
					// Right now when the filter kernel is not entirely over the 
					// sourcebuffer, we are just letting it be the original pixel
					//
					// We need to account for this somehow by modifying srcIndex.
					// We can also leave out the pixels entirely with an if statement.

					//Increment the R,G,B sums
					redSum   += sourceBuffer[srcIndex+0] * filterKernel[knlIndex];
					greenSum += sourceBuffer[srcIndex+1] * filterKernel[knlIndex];
					blueSum  += sourceBuffer[srcIndex+2] * filterKernel[knlIndex];
				}
			}

			//Average the filter kernel values
			destBuffer[3*(row*srcBufferWidth+column)+0] = redSum/divisor;
 			destBuffer[3*(row*srcBufferWidth+column)+1] = greenSum/divisor;
 			destBuffer[3*(row*srcBufferWidth+column)+2] = blueSum/divisor;
		}
	}


}


//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}



